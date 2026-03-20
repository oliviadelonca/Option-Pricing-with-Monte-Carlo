#pragma once
#include <iostream>

class Option {
protected:
    double S;      // Price of the underlying asset
    double K;      // Strike
    double T;      // Maturity
    double r;      // Risk free rate
    double sigma;  // Volatility
    bool isCall;   // true = Call, false = Put

public:
    Option(double S_, double K_, double T_, double r_, double sigma_, bool isCall_);    
    Option(const Option& other);
    Option& operator=(const Option& other);
    virtual ~Option();

    // Getters
    double getS() const { return S; }
    double getK() const { return K; }
    double getT() const { return T; }
    double getR() const { return r; }
    double getSigma() const { return sigma; }
    bool getIsCall() const { return isCall; }

    virtual double prix() = 0;
    virtual double delta() = 0;
};
