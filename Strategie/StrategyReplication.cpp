#include "StrategyReplication.h"

double StrategyReplication::delta(const Option& option) {
    return BlackScholes::delta(option);
}

double StrategyReplication::cash(const Option& option, double S_current) {
    double deltaOpt = delta(option);
    double C0 = BlackScholes::prix(option);
    return C0 - deltaOpt * S_current;
}

double StrategyReplication::valeurPortefeuille(const Option& option, double S_current) {
    double deltaOpt = delta(option);
    double B = cash(option, S_current);
    return deltaOpt * S_current + B;
}
