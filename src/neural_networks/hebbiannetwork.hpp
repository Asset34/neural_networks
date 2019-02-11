#ifndef HEBBIANNETWORK_HPP
#define HEBBIANNETWORK_HPP

#include <tuple>

#include "ann_core/entities.hpp"
#include "ann_core/neuron.hpp"
#include "ann_core/inputneuron.hpp"
#include "ann_core/layer.hpp"
#include "ann_core/inputlayer.hpp"
#include "ann_core/neuralnetwork.hpp"

#include <utills/utills.hpp>

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
