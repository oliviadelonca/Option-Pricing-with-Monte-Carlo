#pragma once
#include "Option.h"

class MonteCarlo {
public:
    static double prix(const Option& option, int nSimulations = 20000, int nSteps = 50);
    static double delta(const Option& option, int nSimulations = 20000);
};
