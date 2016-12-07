// NN2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NeuralNetwork.h"
#include <vector>
#include "Layer.h"
#include "neuron.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <algorithm>
int _tmain(int argc, _TCHAR* argv[])
{

    std::ifstream fin("C:\\Users\\user\\Documents\\Visual Studio 2013\\Projects\\NN2\\NN2\\input.txt", std::ios::in);
    std::ofstream fout("C:\\Users\\user\\Documents\\Visual Studio 2013\\Projects\\NN2\\NN2\\output.txt", std::ios::out);
    float value;
    std::vector <float> values;
    while (fin >> value) {
        values.push_back(value);
    }
    std::vector<int> number_of_neurons;
    number_of_neurons.push_back(1);
    number_of_neurons.push_back(10);
    number_of_neurons.push_back(1);
    int i = 0;
    NeuralNetwork neural_network(number_of_neurons);
    std::vector<float>image;
    std::vector<float>output;
    while (neural_network.EndOfLearning() == false){
        if (i == values.size()) i = 0;
        image.push_back(values[i]);
        i++;
        output.push_back(sin(values[i]));
        neural_network.Learning(image, output);
        std::cout << neural_network.Activation_for_last_layer[0] << std::endl;
        image.clear();
        output.clear();
    }
	return 0;
}

