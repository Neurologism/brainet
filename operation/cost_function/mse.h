#ifndef MSE_INCLUDE_GUARD
#define MSE_INCLUDE_GUARD

#include"..\operation.h"

class MSE : public OPERATION
{
public:
    void f(std::vector<std::shared_ptr<VARIABLE>>& inputs) override;
    std::shared_ptr<TENSOR<double>> bprop(std::vector<std::shared_ptr<VARIABLE>>& inputs, std::shared_ptr<VARIABLE> & focus, std::shared_ptr<TENSOR<double>> & gradient) override;
};



void MSE::f(std::vector<std::shared_ptr<VARIABLE>>& inputs)
{
    if(inputs.size() != 2)
    {
        throw std::runtime_error("MSE operation requires 2 inputs");
    }
    if(inputs[0]->get_data()->shape() != inputs[1]->get_data()->shape())
    {
        throw std::runtime_error("MSE operation requires inputs to have the same shape");
    }
    double sum = 0;
    for(int i = 0; i < inputs[0]->get_data()->size(); i++)
    {
        sum += pow(inputs[0]->get_data()->at({i}) - inputs[1]->get_data()->at({i}), 2);
    }
    sum /= inputs[0]->get_data()->size() * 2;
    this->get_variable()->get_data() = std::make_shared<TENSOR<double>>(TENSOR<double>({1},sum));
}


std::shared_ptr<TENSOR<double>> MSE::bprop(std::vector<std::shared_ptr<VARIABLE>>& inputs, std::shared_ptr<VARIABLE> & focus, std::shared_ptr<TENSOR<double>> & gradient)
{
    if(inputs.size() != 2)
    {
        throw std::runtime_error("MSE operation requires 2 inputs");
    }
    if(inputs[0]->get_data()->shape() != inputs[1]->get_data()->shape())
    {
        throw std::runtime_error("MSE operation requires inputs to have the same shape");
    }
    std::shared_ptr<TENSOR<double>> _gradient = std::make_shared<TENSOR<double>>(TENSOR<double>(inputs[0]->get_data()->shape()));
    for(int i = 0; i < inputs[0]->get_data()->size(); i++)
    {
        _gradient->data()[i] = (inputs[0]->get_data()->at({i}) - inputs[1]->get_data()->at({i})) / inputs[0]->get_data()->size() * gradient->data()[i];
    }

    return _gradient;
}

#endif // MSE_INCLUDE_GUARD