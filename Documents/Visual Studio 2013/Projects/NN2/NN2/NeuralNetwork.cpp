#include "stdafx.h"
#include "NeuralNetwork.h"
#include <vector>
#include "Layer.h"
#include "neuron.h"
#include <cmath>

NeuralNetwork::NeuralNetwork(std::vector<int>number_of_neurons)
{
    this->number_of_layers = number_of_neurons.size();
    Layer layer_for_adding(number_of_neurons[0], 0);
    for (int i = 1; i < number_of_layers; i++) {
        Layer layer_for_adding(number_of_neurons[i], number_of_neurons[i-1]);
        layers.push_back(layer_for_adding);
    }

}

std::vector<Layer> NeuralNetwork::GetLayers(){
    return layers;
}

void NeuralNetwork::CountingLayersActivation(){
    NET_for_last_layer.resize(layers[2].GetNumberOfNeurons());//почему все это нельзя хранить в слоях и очищать после каждой итерации?
    NET_for_hidden_layer.resize(layers[1].GetNumberOfNeurons());
    Activation_for_last_layer.resize(layers[2].GetNumberOfNeurons());//почему все это нельзя хранить в слоях и очищать после каждой итерации?
    Activation_for_hidden_layer.resize(layers[1].GetNumberOfNeurons());
    for (int i = 0; i < layers[1].GetNumberOfNeurons(); i++){
        NET_for_hidden_layer[i] = layers[1].GetNeurons()[i].CountingNET(input_value);
        Activation_for_hidden_layer[i] = layers[1].GetNeurons()[i].CountingActivation(input_value);
    }
    for (int i = 0; i < layers[2].GetNumberOfNeurons(); i++){
        NET_for_last_layer[i] = layers[2].GetNeurons()[i].CountingNET(Activation_for_hidden_layer);
        Activation_for_last_layer[i] = layers[2].GetNeurons()[i].CountingActivation(Activation_for_hidden_layer);
    }
}

std::vector<float>&NeuralNetwork::SumOfLastErrors(){
    std::vector<float>sum_of_last_errors;
    sum_of_last_errors.resize(layers[1].GetNumberOfNeurons());

    for (int j = 0; j <layers[1].GetNumberOfNeurons(); j++){
        for (int i = 0; i < layers[2].GetNumberOfNeurons(); i++)
            sum_of_last_errors[j] = sum_of_last_errors[j] + layers[2].GetNeurons()[i].GetWeights()[j] *
            errors_for_last_layer[i];
    }
    return sum_of_last_errors;
}

void NeuralNetwork::BackPropagation(){//а со смещением что делать?
    errors_for_last_layer.resize(layers[2].GetNumberOfNeurons());
    errors_for_hidden_layer.resize(layers[1].GetNumberOfNeurons());
    dw_for_last_layer.resize(layers[2].GetNumberOfNeurons());
    dw_for_hidden_layer.resize(layers[1].GetNumberOfNeurons());

    for (int i = 0; i < layers[2].GetNumberOfNeurons(); i++) {//неправильно. не от инпутов, а от значений функций активации
        errors_for_last_layer[i] = (output_value[i] - Activation_for_last_layer[i])*
            (Activation_for_last_layer[i])*(1 - Activation_for_last_layer[i]);

        dw_for_last_layer[i] = learning_rate*errors_for_last_layer[i] * NET_for_last_layer[i];
    }

    for (int i = 0; i < layers[1].GetNumberOfNeurons(); i++){
        errors_for_hidden_layer[i] = Activation_for_hidden_layer[i] * (1 - Activation_for_hidden_layer[i])*
            SumOfLastErrors()[i];

        dw_for_hidden_layer[i] = learning_rate* errors_for_hidden_layer[i] * input_value[i];
    }
}

void NeuralNetwork::ChangingWeights(){
    for (int i = 0; i < layers[2].GetNumberOfNeurons(); i++) {
        for (int j = 0; j < layers[1].GetNumberOfNeurons(); j++)
            layers[2].GetNeurons()[i].SetWeight(j, alpha*dw_for_last_layer[i]); //???
    }
    for (int i = 0; i < layers[1].GetNumberOfNeurons(); i++) {
        for (int j = 0; j < layers[0].GetNumberOfNeurons(); j++)
            layers[2].GetNeurons()[i].SetWeight(j, alpha*dw_for_last_layer[i]); //???
    }
}

bool NeuralNetwork::EndOfLearning(){
    float sum = 0;
    if (errors_for_last_layer.size() != 0){
        for (int i = 0; i < layers[2].GetNumberOfNeurons(); i++)
            sum = sum + errors_for_last_layer[i] * errors_for_last_layer[i];
        if (sqrt(sum) < epsilon) return true;
    }
    return false;
}

void NeuralNetwork::SetInputValue(std::vector<float>image){
    input_value = image;
}

void NeuralNetwork::SetOutputValue(std::vector<float>image){
    output_value = image;
}


void NeuralNetwork::Learning(std::vector<float>image, std::vector<float>output){
        SetInputValue(image);
        SetOutputValue(output);
        CountingLayersActivation();
        BackPropagation();
        ChangingWeights();
}

NeuralNetwork::~NeuralNetwork(){}
