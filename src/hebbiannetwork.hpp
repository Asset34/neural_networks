#ifndef HEBBIANNETWORK_HPP
#define HEBBIANNETWORK_HPP

#include <tuple>

#include <neural_network_classes/entities.hpp>
#include <neural_network_classes/neuron.hpp>
#include <neural_network_classes/inputneuron.hpp>
#include <neural_network_classes/layer.hpp>
#include <neural_network_classes/inputlayer.hpp>
#include <neural_network_classes/neuralnetwork.hpp>

#include "utills/utills.hpp"

class HebbianNetwork : public NeuralNetwork
{
public:
    HebbianNetwork(size_t inputSize, size_t memorySize);

    virtual std::string getName() const override;

    virtual bool learn(const std::vector<LearnUnit> &units) override;
    virtual std::tuple<std::vector<double>, bool> recognize(const std::vector<double> &sample) override;

    virtual void rebuild(size_t inputSize, size_t memorySize) override;

private:
    void setActivationFuncs();
    void buildConnections();

    void adjustBiases(std::vector<double> &biases, const LearnUnit &unit);
    void adjustWeights(WeightMat &weights, const LearnUnit &unit);

    bool stopCriterion(const std::vector<LearnUnit> &units);

    void reset();

    constexpr static const int MAX_ITERATIONS = 100;

    /* Layers */
    InputLayer m_inputLayer;
    Layer m_outputLayer;

    /* Parameters */
    double m_learnFactor;
    double m_accuracy;

    int m_curIteration;

};

#endif // HEBBIANNETWORK_HPP
