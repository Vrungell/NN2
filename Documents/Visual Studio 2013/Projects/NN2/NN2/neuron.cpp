#include "stdafx.h"
#include "neuron.h"
#include <algorithm>

neuron::neuron(int number)
{
    number_of_neurons_previous = number;
    weights.resize(number);
    for (int i = 0; i < number; i++)
    {
        int x = rand();
        int y = rand();
        weights[i] = (float)std::min(x, y) / std::max(x, y);
    }
}

std::vector<float> &neuron::GetWeights(){
    return weights;
}

void neuron::SetWeight(int number, float value){
    weights[number] = weights[number] + value;
}

float neuron::GetBias(){
    return bias;
}

void neuron::SetBias(float value){
    bias = value;
}

float neuron::CountingNET(std::vector<float>input_values){
    float sum = 0;
    if (number_of_neurons_previous != 0)
        for (int i = 0; i < input_values.size(); i++)
            sum = sum + weights[i] * input_values[i];
        return sum;
}

float neuron::CountingActivation(std::vector<float>input_values){
    return (1 / (1 + exp(alpha*this->CountingNET(input_values))));
}

neuron::~neuron()
{}
