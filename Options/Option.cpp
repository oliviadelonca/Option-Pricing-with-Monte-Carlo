#include "Options/Option.h"

Option::Option(double S_, double K_, double T_, double r_, double sigma_, bool isCall_) {
    S = S_;
    K = K_;
    T = T_;
    r = r_;
    sigma = sigma_;
    isCall = isCall_;
}

Option::Option(const Option& other) {
    S = other.S;
    K = other.K;
    T = other.T;
    r = other.r;
    sigma = other.sigma;
    isCall = other.isCall;
}

Option& Option::operator=(const Option& other) {
    if (this != &other) {
        S = other.S;
        K = other.K;
        T = other.T;
        r = other.r;
        sigma = other.sigma;
        isCall = other.isCall;
    }
    return *this;
}

Option::~Option() {}
