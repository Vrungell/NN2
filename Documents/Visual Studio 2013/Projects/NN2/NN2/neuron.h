#pragma once
#include <vector>
class neuron
{
private:
    int number_of_neurons_previous;
    float alpha = 0;
    std::vector<float>weights;
    float bias = 1;
public:
    float CountingActivation(std::vector<float>input_values);
    float CountingNET(std::vector<float>input_values);
    std::vector<float> &GetWeights();
    void SetWeight(int number, float value);
    float GetBias();
    void SetBias(float value);
    neuron(int number);
    ~neuron();
};

