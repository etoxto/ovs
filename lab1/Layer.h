/*
//
// Created by etoxto on 9/30/24.
//

#ifndef LAYER_H
#define LAYER_H

#include "Neuron.h"
#include <vector>

class Layer {
public:
    std::vector<Neuron> neurons;

    Layer(int numNeurons, int inputsPerNeuron);
    std::vector<double> activate(const std::vector<double>& inputs);
};



#endif //LAYER_H
*/
