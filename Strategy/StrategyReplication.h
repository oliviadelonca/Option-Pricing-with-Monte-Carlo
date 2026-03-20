#pragma once
#include "Option.h"
#include "BlackScholes.h"

class StrategyReplication {
public:
    static double delta(const Option& option);
    static double cash(const Option& option, double S_current);
    static double PortfolioValue(const Option& option, double S_current);
};
