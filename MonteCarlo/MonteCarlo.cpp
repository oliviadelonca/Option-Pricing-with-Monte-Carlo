#include "MonteCarlo/MonteCarlo.h"
#include "Options/AmericanOption.h"  
#include <random>
#include <cmath>
#include <algorithm>
#include <vector>
#include <numeric>

double MonteCarlo::prix(const Option& option,
                                  int nSimulations,
                                  int nSteps) {
    double S0 = option.getS();
    double K = option.getK();
    double T = option.getT();
    double r = option.getR();
    double sigma = option.getSigma();
    bool call = option.getIsCall();

    double dt = T / nSteps;
    double discount = std::exp(-r * dt);

    // Random number generator with fixed seed for reproducibility
    std::mt19937 gen(42);
    std::normal_distribution<> N(0.0, 1.0);

    // Array to store the paths
    std::vector<std::vector<double>> paths(nSimulations,
                                           std::vector<double>(nSteps + 1));
    
    // The underlying asset price follows a geometric Brownian motion.
    for (int i = 0; i < nSimulations; ++i) {
        paths[i][0] = S0;
        for (int t = 1; t <= nSteps; ++t) {
            double Z = N(gen);
            paths[i][t] = paths[i][t - 1] *
                std::exp((r - 0.5 * sigma * sigma) * dt
                         + sigma * std::sqrt(dt) * Z);
        }
    }

    // Cashflows at maturity 
    std::vector<double> cashflows(nSimulations); 
    for (int i = 0; i < nSimulations; ++i) {
        double ST = paths[i][nSteps];
        if (call) {
            cashflows[i] = std::max(ST - K, 0.0);
        } else {
            cashflows[i] = std::max(K - ST, 0.0);
        }
    }

    // Longstaff-Schwartz method (Least Squares Monte Carlo)
    for (int t = nSteps - 1; t >= 1; --t) {
        std::vector<double> X; // Vector that will contain the underlying asset prices at time t for simulations where the intrinsic value is positive
        std::vector<double> Y; // Vector of discounted future cashflows
        std::vector<int> indices; // To keep track of which cashflow corresponds to which simulation

        for (int i = 0; i < nSimulations; ++i) {
            double St = paths[i][t];
            double intrinsic = call ? std::max(St - K, 0.0) : std::max(K - St, 0.0);
    
            if (intrinsic > 0.0) {
                X.push_back(St); // Add the underlying asset price to vector X
                Y.push_back(cashflows[i] * discount); // Add the discounted payoff (cashflows[i] * discount) to vector Y
                indices.push_back(i); // Store the simulation index
            }
        }


        // Regression to compute the continuation value of the option at each time step t.
        // If the number of simulations with positive intrinsic value is sufficient (at least 2), we perform a regression on the underlying asset prices (X) and discounted cashflows (Y).
        // This regression estimates a continuation function (a0 + a1 * St), which is used to compare the intrinsic value of the option with the continuation value.
        // If the intrinsic value is greater than the continuation value, the option is exercised immediately.
        // Otherwise, we continue the simulation by applying a discount factor.
        
        // I chose linear regression because the relationship between the underlying price and the continuation value is often approximately linear.
        // I could also have used a quadratic regression to capture nonlinear behavior and solve the resulting 3x3 system using Gaussian elimination.
        if (X.size() >= 2) {
            int n = X.size();
            double Xbar = std::accumulate(X.begin(), X.end(), 0.0) / n;
            double Ybar = std::accumulate(Y.begin(), Y.end(), 0.0) / n;
    
            double num = 0.0, den = 0.0;
            for (int i = 0; i < n; ++i) {
                num += (X[i] - Xbar) * (Y[i] - Ybar);
                den += (X[i] - Xbar) * (X[i] - Xbar);
            }
            double a1 = (den != 0.0) ? num / den : 0.0;
            double a0 = Ybar - a1 * Xbar;
    
            for (size_t k = 0; k < X.size(); ++k) {
                int idx = indices[k];
                double St = X[k];
                double intrinsic = call ? std::max(St - K, 0.0) : std::max(K - St, 0.0);
                double continuation = a0 + a1 * St;

                if (intrinsic > continuation) {
                    cashflows[idx] = intrinsic; // immediate exercise
                } else {
                    cashflows[idx] *= discount; // continuation
                }
            }
        }

        if (X.size() < 2) {
             for (double& cf : cashflows) cf *= discount;
        }
    }
    
    double price = std::accumulate(cashflows.begin(), cashflows.end(), 0.0) / nSimulations;
    return price * discount; 
}

double MonteCarlo::delta(const Option& option, int nSimulations) {
    double h = 0.01;
    
    // We use AmericanOption instead of Option because we cannot instantiate the abstract class "Option".
    // We create temporary objects with the new prices S+h and S-h
    
    AmericanOption optUp(option.getS() + h, 
                         option.getK(), 
                         option.getT(), 
                         option.getR(), 
                         option.getSigma(), 
                         option.getIsCall());

    AmericanOption optDown(option.getS() - h, 
                          option.getK(), 
                          option.getT(), 
                          option.getR(), 
                          option.getSigma(), 
                          option.getIsCall());

    // Compute the price difference
    double priceUp = prix(optUp, nSimulations);
    double priceDown = prix(optDown, nSimulations);

    return (priceUp - priceDown) / (2 * h);
}
