/*
//
// Created by etoxto on 9/30/24.
//

#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Layer.h"
#include <vector>


class NeuralNetwork {
public:
    std::vector<Layer> layers;
    double learningRate;

    NeuralNetwork(const std::vector<int>& layersStructure, double lr = 0.1);
    std::vector<double> feedForward(const std::vector<double>& inputs);
    void backpropagation(const std::vector<double>& inputs, const std::vector<double>& expectedOutputs);
    void train(const std::vector<std::vector<double>>& trainingInputs, const std::vector<std::vector<double>>& trainingOutputs, int epochs);
};



#endif //NEURALNETWORK_H
*/
