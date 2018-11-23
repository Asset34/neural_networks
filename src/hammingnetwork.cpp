#include "hammingnetwork.hpp"

#include <cmath>

HammingNetwork::HammingNetwork(size_t inputSize, size_t memorySize)
    : NeuralNetwork(inputSize, memorySize),
      m_inputLayer(inputSize),
      m_memoryLayer(memorySize, inputSize / 2.0),
      m_maxnetLayer(memorySize),
      m_outputLayer(memorySize),
      m_memoryFactor(1.0),
      m_memoryBound(inputSize),
      m_maxnetSuppression(1.0 / memorySize),
      m_accuracy(1e-7)
{
    setActivationFuncs();
    buildConnections();
}

std::string HammingNetwork::getName() const
{
    return "Hamming network";
}

bool HammingNetwork::learn(const std::vector<LearnUnit> &samples)
{
    if (samples.size() != m_memorySize) {
        return false;
    }
    for (LearnUnit unit : samples) {
        if (unit.sample.size() != m_inputSize) {
            return false;
        }
    }

    // Compute weights
    WeightMat weights(m_memorySize, WeightVec(m_inputSize));
    for (size_t i = 0; i < m_memorySize; i++) {
        for (size_t j = 0; j < m_inputSize; j++) {
            weights[i][j] = samples[i].sample[j] / 2.0;
        }
    }

    m_memoryLayer.setWeights(weights);

    return true;
}

std::tuple<std::vector<double>, bool> HammingNetwork::recognize(
        const std::vector<double> &sample)
{
    if (sample.size() != m_inputSize) {
        return std::make_tuple(std::vector<double>(m_memorySize, 0.0), false);
    }

    reset();

    enableTransitionToMaxnet();

    m_inputLayer.setInputs(sample);
    m_inputLayer.move();
    m_memoryLayer.move();
    m_maxnetLayer.move();

    disableTransitionToMaxnet();

    // Maxnet's competition
    std::vector<double> prev;
    std::vector<double> cur = m_maxnetLayer.getOutputs();
    do {
        m_maxnetLayer.move();

        prev = cur;
        cur = m_maxnetLayer.getOutputs();
    }
    while (!Utills::compare(prev, cur, m_accuracy));

    m_outputLayer.move();

    return std::make_tuple(m_outputLayer.getOutputs(), true);
}

void HammingNetwork::rebuild(size_t inputSize, size_t memorySize)
{
    NeuralNetwork::rebuild(inputSize, memorySize);

    // Rebuild layers
    m_inputLayer = InputLayer(inputSize);
    m_memoryLayer = Layer(memorySize, inputSize / 2.0);
    m_maxnetLayer = Layer(memorySize);
    m_outputLayer = Layer(memorySize);

    setParameters();
    setActivationFuncs();
    buildConnections();
}

void HammingNetwork::setParameters()
{
    m_memoryBound = m_inputSize;
    m_maxnetSuppression = 1.0 / m_memorySize;
}

void HammingNetwork::setActivationFuncs()
{
    m_memoryLayer.setActivationFunc(
        [this](double x) -> double
        {
            if (x <= m_accuracy)        return 0.0;
            else if (x > m_memoryBound) return m_memoryBound;
            else                        return m_memoryFactor * x;
        }
    );
    m_maxnetLayer.setActivationFunc(
        [this](double x) -> double
        {
            if (x <= m_accuracy) return 0.0;
            else                 return x;
        }
    );
    m_outputLayer.setActivationFunc(
        [this](double x) -> double
        {
            if (x <= m_accuracy) return 0.0;
            else                 return 1.0;
        }
    );
}

void HammingNetwork::buildConnections()
{
    // Build weights
    WeightMat w_inputToMemory(m_memorySize, WeightVec(m_inputSize));
    WeightVec w_memoryToMaxnet(m_memorySize, 1.0);
    WeightMat w_maxnetLoopback(m_memorySize, WeightVec(m_memorySize, -m_maxnetSuppression));
    for (size_t i = 0; i < m_memorySize; i++) {
        w_maxnetLoopback[i][i] = 1;
    }
    WeightVec w_maxnetToOutput(m_memorySize, 1.0);

    // Build network
    m_inputLayer.connectAllToAll(m_memoryLayer, w_inputToMemory);
    m_memoryLayer.connectOneToOne(m_maxnetLayer, w_memoryToMaxnet);
    m_maxnetLayer.connectLoopback(w_maxnetLoopback);
    m_maxnetLayer.connectOneToOne(m_outputLayer, w_maxnetToOutput);
}

void HammingNetwork::enableTransitionToMaxnet()
{
    WeightMat weights(m_memorySize, {1.0});
    m_maxnetLayer.setWeights(weights);
}

void HammingNetwork::disableTransitionToMaxnet()
{
    WeightMat weights(m_memorySize, {0.0});
    m_maxnetLayer.setWeights(weights);
}

void HammingNetwork::reset()
{
    m_maxnetLayer.reset();
}
