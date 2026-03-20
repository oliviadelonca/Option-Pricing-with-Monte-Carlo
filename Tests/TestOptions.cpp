#include <iostream>
#include <cmath>
#include "EuropeanOption.h"
#include "AmericanOption.h"
#include "BlackScholes.h"
#include "MonteCarlo.h"

// Function to compare two values with a tolerance of 0.0001
bool approxEqual(double a, double b, double tol = 1e-4) {
    return std::fabs(a - b) < tol;
}

int main() {
    // Test parameters
    double S = 100.0;
    double K = 100.0;
    double T = 1.0;
    double r = 0.05;
    double sigma = 0.2;
    int nSimulations = 100000;

    // Black-Scholes reference values for comparison
    double refCallPrice = 10.4506;
    double refCallDelta = 0.6368;
    double refPutPrice  = 5.5735;
    double refPutDelta  = -0.3632;

    // Creating the options
    EuropeanOption callOption(S, K, T, r, sigma, true);
    EuropeanOption putOption(S, K, T, r, sigma, false);
    AmericanOption callAm(S, K, T, r, sigma, true);
    AmericanOption putAm(S, K, T, r, sigma, false);

    // Pricers
    BlackScholes bs;
    MonteCarlo mc;

    std::cout << "Tests Black-Scholes" << std::endl;

    double callPriceBS = bs.prix(callOption);
    double callDeltaBS = bs.delta(callOption);
    double putPriceBS  = bs.prix(putOption);
    double putDeltaBS  = bs.delta(putOption);

    std::cout << "Call Price: " << (approxEqual(callPriceBS, refCallPrice) ? "OK" : "FAIL") 
              << " (" << callPriceBS << ")" << std::endl;
    std::cout << "Call Delta: " << (approxEqual(callDeltaBS, refCallDelta) ? "OK" : "FAIL") 
              << " (" << callDeltaBS << ")" << std::endl;
    std::cout << "Put Price: " << (approxEqual(putPriceBS, refPutPrice) ? "OK" : "FAIL") 
              << " (" << putPriceBS << ")" << std::endl;
    std::cout << "Put Delta: " << (approxEqual(putDeltaBS, refPutDelta) ? "OK" : "FAIL") 
              << " (" << putDeltaBS << ")" << std::endl;

    std::cout << "\n Tests Monte-Carlo" << std::endl;

    // Monte Carlo prices
    double callPriceMC = mc.prix(callOption, nSimulations);
    double putPriceMC  = mc.prix(putOption, nSimulations);

    // Monte Carlo delta 
    double callDeltaMC = mc.delta(callOption, nSimulations);
    double putDeltaMC  = mc.delta(putOption, nSimulations);

    std::cout << "Call Européen MC: Prix=" << callPriceMC << ", Delta=" << callDeltaMC << std::endl;
    std::cout << "Put Européen MC:  Prix=" << putPriceMC  << ", Delta=" << putDeltaMC  << std::endl;

    // Monte Carlo pricing for American options
    double callAmPriceMC = mc.prix(callAm, nSimulations);
    double putAmPriceMC  = mc.prix(putAm, nSimulations);

    std::cout << "\n Tests Monte-Carlo American Options " << std::endl;
    std::cout << "American Call MC: Price~" << callAmPriceMC << std::endl;
    std::cout << "American Put MC:  Price~" << putAmPriceMC << std::endl;

    return 0;
}
