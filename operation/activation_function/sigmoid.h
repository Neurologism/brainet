#ifndef SIGMOID_INCLUDE_GUARD
#define SIGMOID_INCLUDE_GUARD

#include "activation_function.h"

/**
 * @brief Sigmoid function class, representing the sigmoid function f(x) = 1 / (1 + exp(-x)).
*/
class Sigmoid : public ACTIVATION_FUNCTION
{   
    double activation_function(double input)override;
    double activation_function_derivative(double input)override;
public:
    Sigmoid() = default;
    ~Sigmoid() = default;
};

double Sigmoid::activation_function(double input)
{
    return 1 / (1 + exp(-input));
}

double Sigmoid::activation_function_derivative(double input)
{
    return activation_function(input) * (1 - activation_function(input));
}

#endif // SIGMOID_INCLUDE_GUARD