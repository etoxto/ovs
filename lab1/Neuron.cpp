/*//
// Created by etoxto on 9/30/24.
//

#include "Neuron.h"
#include <cmath>
#include <cstdlib>

Neuron::Neuron(int inputs) {
    for (int i = 0; i < inputs; ++i) {
        weights.push_back((double)rand() / RAND_MAX);
    }
    bias = (double)rand() / RAND_MAX;
}

double Neuron::activate(const std::vector<double>& inputs) {
    double sum = bias;
    for (size_t i = 0; i < inputs.size(); ++i) {
        sum += inputs[i] * weights[i];
    }
    output = sigmoid(sum);
    return output;
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double sigmoidDerivative(double x) {
    return x * (1.0 - x);
}*/