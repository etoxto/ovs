/*
//
// Created by etoxto on 9/30/24.
//

#include "NeuralNetwork.h"
#include <iostream>

NeuralNetwork::NeuralNetwork(const std::vector<int>& layersStructure, double lr) {
    learningRate = lr;
    for (size_t i = 1; i < layersStructure.size(); ++i) {
        layers.emplace_back(Layer(layersStructure[i], layersStructure[i - 1]));
    }
}

std::vector<double> NeuralNetwork::feedForward(const std::vector<double>& inputs) {
    std::vector<double> currentInputs = inputs;
    for (auto& layer : layers) {
        currentInputs = layer.activate(currentInputs);
    }
    return currentInputs;
}

void NeuralNetwork::backpropagation(const std::vector<double>& inputs, const std::vector<double>& expectedOutputs) {
    std::vector<std::vector<double>> activations;
    std::vector<double> currentInputs = inputs;
    activations.push_back(currentInputs);

    for (auto& layer : layers) {
        currentInputs = layer.activate(currentInputs);
        activations.push_back(currentInputs);
    }

    std::vector<double> errors;
    std::vector<double> deltas;
    for (size_t i = 0; i < layers.back().neurons.size(); ++i) {
        double error = expectedOutputs[i] - activations.back()[i];
        errors.push_back(error);
        deltas.push_back(error * sigmoidDerivative(activations.back()[i]));
    }

    for (int l = layers.size() - 2; l >= 0; --l) {
        std::vector<double> nextDeltas(layers[l].neurons.size());

        for (size_t i = 0; i < layers[l].neurons.size(); ++i) {
            double deltaSum = 0.0;
            for (size_t j = 0; j < layers[l + 1].neurons.size(); ++j) {
                deltaSum += deltas[j] * layers[l + 1].neurons[j].weights[i];
            }
            nextDeltas[i] = deltaSum * sigmoidDerivative(activations[l + 1][i]);
        }
        deltas = nextDeltas;

        for (size_t i = 0; i < layers[l].neurons.size(); ++i) {
            for (size_t j = 0; j < activations[l].size(); ++j) {
                layers[l].neurons[i].weights[j] += learningRate * deltas[i] * activations[l][j];
            }
            layers[l].neurons[i].bias += learningRate * deltas[i];
        }
    }

    Layer& outputLayer = layers.back();
    for (size_t i = 0; i < outputLayer.neurons.size(); ++i) {
        for (size_t j = 0; j < activations[activations.size() - 2].size(); ++j) {
            outputLayer.neurons[i].weights[j] += learningRate * deltas[i] * activations[activations.size() - 2][j];
        }
        outputLayer.neurons[i].bias += learningRate * deltas[i];
    }
}

void NeuralNetwork::train(const std::vector<std::vector<double>>& trainingInputs, const std::vector<std::vector<double>>& trainingOutputs, int epochs) {
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < trainingInputs.size(); ++i) {
            backpropagation(trainingInputs[i], trainingOutputs[i]);
        }
        std::cout << "Epoch " << epoch + 1 << " completed." << std::endl;
    }
}
*/

