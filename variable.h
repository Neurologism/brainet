#ifndef VARIABLE_INCLUDE_GUARD
#define VARIABLE_INCLUDE_GUARD

#include "dependencies.h"
#include "operation/operation.h"
#include "tensor.h"

class OPERATION;

/**
 * @brief VARIABLE class is a wrapper class for OPERATION class. It is used to create a graph of operations.
*/
class VARIABLE
{
    std::vector<VARIABLE *> __children, __parents;
    OPERATION * __op;
    TENSOR<double> __data; // each variable can store a batch of the data 
    static int __counter = 0;
    int __id;

public:
    VARIABLE(OPERATION * op, std::vector<VARIABLE *> parents, std::vector<VARIABLE *> children) : __op(op), __parents(parents), __children(children){__id = __counter++;};
    ~VARIABLE();
    OPERATION * get_operation();
    std::vector<VARIABLE *> & get_consumers();
    std::vector<VARIABLE *> & get_inputs();
    TENSOR<double> * get_data();
    int get_id();
    void set_data(TENSOR<double> & data);
};

VARIABLE::~VARIABLE()
{
    for (VARIABLE * parent : __parents)
    {
        free(parent);
    }
    for (VARIABLE * child : __children)
    {
        free(child);
    }
}

/**
 * @brief returns the operation object
*/
OPERATION * VARIABLE::get_operation()
{
    if (__op == nullptr)
    {
        throw std::invalid_argument("This operation is a pseudo-variable and has no operation.");
    }
    return __op;
}

/**
 * @brief returns the children of the variable
*/
std::vector<VARIABLE *> & VARIABLE::get_consumers()
{
    return __children;
}

/**
 * @brief returns the parents of the variable
*/
std::vector<VARIABLE *> & VARIABLE::get_inputs()
{
    return __parents;
}

/**
 * @brief returns the data of the operation
*/
TENSOR<double> * VARIABLE::get_data()
{
    return &__data;
}

/**
 * @brief sets the data of the variable
*/
void VARIABLE::set_data(TENSOR<double> & data)
{
    __data = data;
}

/**
 * @brief returns the id of the variable
*/
int VARIABLE::get_id()
{
    return __id;
}

#endif