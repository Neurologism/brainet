#ifndef MODEL_INCLUDE_GUARD
#define MODEL_INCLUDE_GUARD

#include "dependencies.h"
#include "graph.h"
#include "cluster/cluster.h"
#include "operation/activation_function/activation_function.h"

class MODEL
{
    std::shared_ptr<GRAPH> __graph;
    std::vector<std::shared_ptr<VARIABLE>> __to_be_differentiated;
public:
    MODEL(){CLUSTER::set_graph(__graph);};
    void load();
    void sequential(std::vector<CLUSTER_VARIANT> layers, bool add_backprop = true);
    void train(int epochs, double learning_rate);
};

void MODEL::load()
{
    CLUSTER::set_graph(__graph);
}

void MODEL::sequential(std::vector<CLUSTER_VARIANT> layers, bool add_backprop)
{
    std::vector<std::shared_ptr<CLUSTER>> clusters;
    for (CLUSTER_VARIANT& layer : layers) {
        clusters.push_back(std::visit([](auto&& arg) -> std::shared_ptr<CLUSTER> {
            return std::make_shared<CLUSTER>(arg);
        }, layer));
    }
    
    for(int i = 0; i < layers.size() - 1; i++)
    {
        clusters[i]->add_output(clusters[i+1]->input());
        clusters[i+1]->add_input(clusters[i]->output(),clusters[i]->size());
    }

    if(add_backprop)(*__to_be_differentiated).push_back(clusters.back()->output());
}

void MODEL::train(int epochs, double learning_rate)
{
    (*__graph).forward();
    std::set<std::shared_ptr<VARIABLE>> s;
    for(VARIABLE & var : (*__graph).get_variables())
    {
        if(var.get_operation() == nullptr)
        {
            s.insert(std::make_shared<VARIABLE>(var));
        }
    }
    (*__graph).backprop(s, *__to_be_differentiated);
}

#endif // MODEL_INCLUDE_GUARD