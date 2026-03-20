#include "EuropeanOption.h"
#include "BlackScholes.h"

EuropeanOption::EuropeanOption(double S_, double K_, double T_, double r_, double sigma_, bool isCall_)
    : Option(S_, K_, T_, r_, sigma_, isCall_) {}

EuropeanOption::EuropeanOption(const EuropeanOption& other)
    : Option(other) {}

EuropeanOption& EuropeanOption::operator=(const EuropeanOption& other) {
    if (this != &other) {
        Option::operator=(other);
    }
    return *this;
}

EuropeanOption::~EuropeanOption() {}

double EuropeanOption::prix() {
    return BlackScholes::prix(*this);
}

double EuropeanOption::delta() {
    return BlackScholes::delta(*this);
}
