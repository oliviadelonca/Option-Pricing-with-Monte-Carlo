#pragma once
#include "Option.h"

class AmericanOption : public Option {
public:
    AmericanOption(double S_, double K_, double T_, double r_, double sigma_, bool isCall_); // Constructeur principal
    AmericanOption(const AmericanOption& other); // Constructeur par copie
    AmericanOption& operator=(const AmericanOption& other); // Opérateur d'assignation
    virtual ~AmericanOption(); // Destructeur

    virtual double prix() override;
    virtual double delta() override;
};
