#ifndef ACTIVATION_FUNCTION_INCLUDE_GUARD
#define ACTIVATION_FUNCTION_INCLUDE_GUARD

#include <vector>
#include <stdexcept>
#include"..\operation.h"

class ACTIVATION_FUNCTION : public OPERATION
{
public:
    ACTIVATION_FUNCTION(VARIABLE * variable) : OPERATION(variable){};
    void f(std::vector<VARIABLE *>& inputs) override;
    void bprop(std::vector<VARIABLE *>& inputs, VARIABLE * focus, std::vector<VARIABLE *> outputs) override;

    virtual double activation_function(double x) = 0;
    virtual double activation_function_derivative(double x) = 0;
};

void ACTIVATION_FUNCTION::f(std::vector<VARIABLE *>& inputs)
{
    if (inputs.size() != 1)
    {
        throw std::invalid_argument("ACTIVATION_FUNCTION::f: Invalid number of input variables.");
    }
    
    std::vector<int> _shape = inputs.front()->get_shape(); // shape stays the same 
    std::vector<double> _data;

    for (double data : inputs.front()->get_data()) // apply activation function to all elements
    {
        _data.push_back(activation_function(data));
    }

    __variable->set_data(_data);
    __variable->set_shape(_shape);
}

void ACTIVATION_FUNCTION::bprop(std::vector<VARIABLE *>& inputs, VARIABLE * focus, std::vector<VARIABLE *> outputs)
{
    if (inputs.size() != 1)
    {
        throw std::invalid_argument("ACTIVATION_FUNCTION::bprop: Invalid number of input variables.");
    }

    // load derivative of activation into data 
    std::vector<double> _data;

    for (double data : inputs.front()->get_data()) // apply activation function derivative to all elements
    {
        _data.push_back(activation_function_derivative(data));
    }

    for (int i = 0; i < _data.size(); i++)
    {
        double gradient = 0;
        for (VARIABLE * output : outputs)
        {
            gradient += output->get_data()[i];
        }
        _data[i] *= gradient;
    }

    __variable->set_data(_data);
}


#endif // ACTIVATION_FUNCTION_INCLUDE_GUARD