#ifndef NEURAL_NET_H
#define NEURAL_NET_H

#include <vector>
#include <cmath>
#include <string>
#include "matrix.h"

class NeuralNetwork {
    private:
        std::vector<int> topology;

        std::vector<Matrix> weights;
        std::vector<Matrix> biases;

        float learning_rate;

        std::vector<Matrix> pre_activations; //Z = (A * W) + b
        std::vector<Matrix> activations; // A = activation(Z)

    public:

        NeuralNetwork(const std::vector<int>& topology, float learning_rate = 0.0001f);

        static float relu(float x);
        static float relu_d(float x);

        [[nodiscard]] std::vector<float> predict(const std::vector<float>& input) const;
        [[nodiscard]] std::vector<float> feed_forward(const std::vector<float>& input);

        void backpropagation(const std::vector<float>& input, const std::vector<float>& target);

        void copy_weights(const NeuralNetwork& other);

        void save(const std::string& path) const;
        void load(const std::string& path);
};

#endif