#pragma once
#include "Option.h"

class AmericanOption : public Option {
public:
    AmericanOption(double S_, double K_, double T_, double r_, double sigma_, bool isCall_); 
    AmericanOption(const AmericanOption& other); 
    AmericanOption& operator=(const AmericanOption& other); 
    virtual ~AmericanOption();

    virtual double prix() override;
    virtual double delta() override;
};
