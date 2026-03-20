#pragma once

class Payoff {
public:
    virtual double operator()(double ST) const = 0;
    virtual ~Payoff() {}
};

class CallPayoff : public Payoff {
private:
    double K;

public:
    CallPayoff(double strike);
    double operator()(double ST) const override;
};

class PutPayoff : public Payoff {
private:
    double K;

public:
    PutPayoff(double strike);
    double operator()(double ST) const override;
};
