#pragma once
#include "Option.h"

class EuropeanOption : public Option {
public:
    EuropeanOption(double S_, double K_, double T_, double r_, double sigma_, bool isCall_); 
    EuropeanOption(const EuropeanOption& other); 
    EuropeanOption& operator=(const EuropeanOption& other); 
    virtual ~EuropeanOption(); 

    virtual double prix() override;
    virtual double delta() override;
};
