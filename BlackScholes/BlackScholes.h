#pragma once
#include "Option.h"

class BlackScholes {
public:
    static double prix(const Option& option);
    static double delta(const Option& option);
};
