#pragma once
#include <vector>
#include "Layer.h"
class NeuralNetwork
{
private:
    int number_of_layers;
    float learning_rate = 0.01;
    float alpha = 0.1;
    float epsilon = 0.001;
    std::vector<float> input_value;
    std::vector<float> output_value;
    std::vector<Layer> layers;
public:
    std::vector<float> errors_for_last_layer;
    std::vector<float> errors_for_hidden_layer;//временное хранилище для ошибок и весов
    std::vector<float> dw_for_last_layer;
    std::vector<float>dw_for_hidden_layer;
    std::vector<float>NET_for_last_layer;
    std::vector<float>NET_for_hidden_layer;
    std::vector<float>Activation_for_last_layer;
    std::vector<float>Activation_for_hidden_layer;
    std::vector<float>NET_for_first_layer;
    std::vector<float>Activation_for_first_layer;
    std::vector<float>SumOfLastErrors();
    void SetInputValue(std::vector<float>image);
    void SetOutputValue(std::vector<float>image);
    void CountingLayersActivation();
    void Learning(std::vector<float>image, std::vector<float>output);
    std::vector<Layer> GetLayers();
    void BackPropagation();
    void CountingDw();
    void CountingError();
    void ChangingWeights();
    bool EndOfLearning();
    void Clear();
    NeuralNetwork(std::vector<int>number_of_neurons);
    ~NeuralNetwork();
};

