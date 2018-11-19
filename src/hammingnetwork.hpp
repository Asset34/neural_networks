#ifndef HAMMINGNETWORK_HPP
#define HAMMINGNETWORK_HPP

#include <tuple>

#include <neural_network_classes/entities.hpp>
#include <neural_network_classes/neuron.hpp>
#include <neural_network_classes/inputneuron.hpp>
#include <neural_network_classes/layer.hpp>
#include <neural_network_classes/inputlayer.hpp>

#include "utills/utills.hpp"

class HammingNetwork
{
public:
    HammingNetwork(size_t inputSize, size_t memorySize);

    bool learn(const std::vector<std::vector<double>> &samples);
    std::tuple<std::vector<double>, bool> recognize(const std::vector<double> &sample);

private:
    void enableTransition();
    void disableTransition();

    void reset();

    /* Sizes */
    size_t m_inputSize;
    size_t m_memorySize;

    /* Layers */
    InputLayer m_inputLayer;
    Layer m_memoryLayer;
    Layer m_maxnetLayer;
    Layer m_outputLayer;

    /* Parameters */
    double m_memoryFactor;
    double m_memoryBound;
    double m_maxnetSuppression;
    double m_accuracy;

};

#endif // HAMMINGNETWORK_HPP
