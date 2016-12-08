#include "stdafx.h"
#include "Layer.h"
#include<vector>

Layer::Layer(int numberofneurons, int number_of_weights)
{
   this->number_of_neurons = numberofneurons;
    for (int i = 0; i < numberofneurons; i++){
        neuron neuron_for_adding(number_of_weights);
        neurons.push_back(neuron_for_adding);
    }
}

int Layer::GetNumberOfNeurons(){
    return this->number_of_neurons;
}

std::vector<neuron> &Layer::GetNeurons(){
    return this->neurons;
}

Layer::~Layer()
{
}
