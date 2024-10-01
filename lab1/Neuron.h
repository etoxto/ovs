/*
//
// Created by etoxto on 9/30/24.
//

#ifndef NEURON_H
#define NEURON_H
#include <vector>


class Neuron {
public:
    double output;
    std::vector<double> weights;
    double bias;

    Neuron(int inputs);
    double activate(const std::vector<double>& inputs);
};

double sigmoid(double x);
double sigmoidDerivative(double x);

#endif //NEURON_H
*/
