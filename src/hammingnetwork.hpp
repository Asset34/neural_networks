#ifndef HAMMINGNETWORK_HPP
#define HAMMINGNETWORK_HPP

#include <tuple>

#include <neural_network_classes/entities.hpp>
#include <neural_network_classes/neuron.hpp>
#include <neural_network_classes/inputneuron.hpp>
#include <neural_network_classes/layer.hpp>
#include <neural_network_classes/inputlayer.hpp>
#include <neural_network_classes/neuralnetwork.hpp>

#include "utills/utills.hpp"

class HammingNetwork : public NeuralNetwork
{
public:
    HammingNetwork(size_t inputSize, size_t memorySize);

    virtual std::string getName() const override;

    virtual bool learn(const std::vector<LearnUnit> &samples) override;
    virtual std::tuple<std::vector<double>, bool> recognize(const std::vector<double> &sample) override;

    virtual void rebuild(size_t inputSize, size_t memorySize) override;

private:
    void setParameters();
    void setActivationFuncs();
    void buildConnections();

    void enableTransitionToMaxnet();
    void disableTransitionToMaxnet();

    void reset();

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
