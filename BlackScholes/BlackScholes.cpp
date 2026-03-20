#include "BlackScholes.h"
#include <cmath>

constexpr double PI = 3.14159265358979323846;

double f(double t) {
    return std::exp(-0.5 * t * t) / std::sqrt(2 * PI);
}

// Cumulative distribution function of the standard normal distribution via numerical integration
// By default, the integration interval is divided into 100,000 subintervals
double N(double z, int n = 100000) {
    double xmin = -10.0; // approximation of -∞, since the normal density is extremely small before -10
    double xmax = z;
    double dx = (xmax - xmin) / n;
    double sum = 0.0;

    for (int i = 0; i < n; ++i) {
        double x = xmin + i * dx;
        sum += f(x) * dx; 
    }

    return sum;
}

double BlackScholes::prix(const Option& option) {
    double S = option.getS();
    double K = option.getK();
    double T = option.getT();
    double r = option.getR();
    double sigma = option.getSigma();
    bool call = option.getIsCall();

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (call)
        return S * N(d1) - K * std::exp(-r * T) * N(d2);
    else
        return K * std::exp(-r * T) * N(-d2) - S * N(-d1);
}

double BlackScholes::delta(const Option& option) {
    double S = option.getS();
    double K = option.getK();
    double T = option.getT();
    double r = option.getR();
    double sigma = option.getSigma();
    bool call = option.getIsCall();

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

    if (call)
        return N(d1);
    else
        return N(d1) - 1.0;
}
