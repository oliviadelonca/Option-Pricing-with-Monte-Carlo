#include "AmericanOption.h"
#include "MonteCarlo.h"

AmericanOption::AmericanOption(double S_, double K_, double T_, double r_, double sigma_, bool isCall_)
    : Option(S_, K_, T_, r_, sigma_, isCall_) {}

AmericanOption::AmericanOption(const AmericanOption& other)
    : Option(other) {}

AmericanOption& AmericanOption::operator=(const AmericanOption& other) {
    if (this != &other) {
        Option::operator=(other);
    }
    return *this;
}

AmericanOption::~AmericanOption() {}

double AmericanOption::prix() {
    return MonteCarlo::prix(*this);
}

double AmericanOption::delta() {
    return MonteCarlo::delta(*this);
}
