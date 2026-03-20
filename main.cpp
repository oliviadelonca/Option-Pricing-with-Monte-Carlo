#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>

#include "EuropeanOption.h"
#include "AmericanOption.h"
#include "StrategyReplication.h"

int main() {
    // Market parameters
    double S = 100.0;      // Spot
    double K = 100.0;      // Strike price
    double T = 1.0;        // Maturity (1 year)
    double r = 0.05;       // Risk-free rate (5%)
    double sigma = 0.2;    // Volatility (20%)

    std::cout << "============================================" << std::endl;
    std::cout << "        PRICING & REPLICATION STRATEGY      " << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << std::fixed << std::setprecision(4); // Displays numbers with 4 decimal places.

    // Creating the options portfolio
    std::vector<Option*> portfolio; // portfolio is a vector of pointers to options.

    // European Call (Black-Scholes pricing)
    portfolio.push_back(new EuropeanOption(S, K, T, r, sigma, true));

    // American Put (Monte Carlo pricing)
    portfolio.push_back(new AmericanOption(S, K, T, r, sigma, false));

    // Computation loop
    for (size_t i = 0; i < portfolio.size(); ++i) {
        Option* opt = portfolio[i];
        
        std::string typeOpt = opt->getIsCall() ? "Call" : "Put";
        std::string modele = (i == 0) ? "Black-Scholes (European)" : "Monte-Carlo (American)";

        std::cout << "\n--- OPTION " << (i + 1) << " : " << modele << " ---" << std::endl;
        std::cout << "Type : " << typeOpt << " | S=" << S << " | K=" << K << std::endl;

        // Price computation 
        double prix = opt->prix();
        std::cout << ">> ESTIMATED PRICE : " << prix << " EUR" << std::endl;

        // Strategy computation
        double delta = StrategyReplication::delta(*opt);
        double valportfolio = StrategyReplication::PortfolioValue(*opt, S);

        std::cout << ">> REPLICATION STRATEGY :" << std::endl;
        std::cout << "   - Delta (Quantity to hold) : " << delta << std::endl;
        std::cout << "   - Total Portfolio Value : " << valportfolio << " EUR" << std::endl;

        if (delta > 0) 
            std::cout << "   -> Action : BUY " << std::abs(delta) << " shares." << std::endl;
        else 
            std::cout << "   -> Action : SELL " << std::abs(delta) << " shares." << std::endl;
            
        std::cout << "--------------------------------------------" << std::endl;
    }

     // Memory cleanup
    for (Option* opt : portfolio) {
        delete opt;
    }
    portfolio.clear();

    return 0;
}
