#include "hammingnetwork.hpp"

#include <cmath>

#include <QDebug>

HammingNetwork::HammingNetwork(size_t inputSize, size_t memorySize)
    : m_inputSize(inputSize),
      m_memorySize(memorySize),
      m_inputLayer(inputSize),
      m_memoryLayer(memorySize, inputSize / 2.0),
      m_maxnetLayer(memorySize),
      m_outputLayer(memorySize),
      m_memoryFactor(1.0),
      m_memoryBound(inputSize),
      m_maxnetSuppression(1.0 / memorySize),
      m_accuracy(1e-7)
{
    // Create activation functions
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

    // Init weights

    WeightMat w_inputMemory(memorySize, WeightVec(inputSize));
    WeightVec w_memory(memorySize, 1.0);
    WeightVec w_maxnet(memorySize, 1.0);

    WeightMat w_maxnetLoopback(memorySize, WeightVec(memorySize, -m_maxnetSuppression));
    for (size_t i = 0; i < memorySize; i++) {
        w_maxnetLoopback[i][i] = 1;
    }

    // Build
    m_inputLayer.connectAllToAll(m_memoryLayer, w_inputMemory);
    m_memoryLayer.connectOneToOne(m_maxnetLayer, w_memory);
    m_maxnetLayer.connectAllToAll(m_maxnetLayer, w_maxnetLoopback);
    m_maxnetLayer.connectOneToOne(m_outputLayer, w_maxnet);
}

bool HammingNetwork::learn(const std::vector<std::vector<double>> &samples)
{
    if (samples.size() != m_memorySize) {
        return false;
    }

    for (size_t i = 0; i < samples.size(); i++) {
        if (samples[i].size() != m_inputSize) {
            return false;
        }
    }

    // Compute weight matrix
    WeightMat weights(m_memorySize, WeightVec(m_inputSize));
    for (size_t i = 0; i < m_memorySize; i++) {
        for (size_t j = 0; j < m_inputSize; j++) {
            weights[i][j] = samples[i][j] / 2.0;
        }
    }

    // Set weights
    m_memoryLayer.setWeights(weights);

    return true;
}

std::tuple<std::vector<double>, bool> HammingNetwork::recognize(
        const std::vector<double> &sample)
{
    if (sample.size() != m_inputSize) {
        return std::make_tuple(std::vector<double>(m_memorySize, 0.0), false);
    }

    // Reset
    reset();

    // Enable transition beetwen Memory and Maxnet layers
    enableTransition();

    // Move input layer
    m_inputLayer.setInputs(sample);
    m_inputLayer.move();

    // Mov ememory layer
    m_memoryLayer.move();

    // Initial move of maxnet layer
    m_maxnetLayer.move();

    // Disable transition beetwen Memory and Maxnet layers
    disableTransition();

    // Maxnet's competition
    std::vector<double> prev;
    std::vector<double> cur = m_maxnetLayer.getOutputs();
    do {
        m_maxnetLayer.move();

        prev = cur;
        cur = m_maxnetLayer.getOutputs();
    }
    while (!Utills::compare(prev, cur, m_accuracy));

    // Move output layer
    m_outputLayer.move();

    return std::make_tuple(m_outputLayer.getOutputs(), true);
}

void HammingNetwork::enableTransition()
{
    WeightMat weights(m_memorySize, {1.0});
    m_maxnetLayer.setWeights(weights);
}

void HammingNetwork::disableTransition()
{
    WeightMat weights(m_memorySize, {0.0});
    m_maxnetLayer.setWeights(weights);
}

void HammingNetwork::reset()
{
    m_maxnetLayer.reset();
}
