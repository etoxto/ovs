/*//
// Created by etoxto on 9/30/24.
//

#include "Layer.h"

Layer::Layer(int numNeurons, int inputsPerNeuron) {
    for (int i = 0; i < numNeurons; ++i) {
        neurons.emplace_back(inputsPerNeuron);
    }
}

std::vector<double> Layer::activate(const std::vector<double>& inputs) {
    std::vector<double> outputs;
    for (auto& neuron : neurons) {
        outputs.push_back(neuron.activate(inputs));
    }
    return outputs;
}*/