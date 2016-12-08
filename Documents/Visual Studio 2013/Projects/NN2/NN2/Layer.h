#pragma once
#include <vector>
#include "neuron.h"
class Layer
{
private:
    std::vector<neuron> neurons;
    int number_of_neurons;
public:
    Layer(int number_of_neurons, int number_of_weights);
    int GetNumberOfNeurons();
    std::vector<neuron> &GetNeurons();
    ~Layer();
};

