#include "hammingann.hpp"

#include <cmath>

#include <QDebug>

HammingAnn::HammingAnn(size_t inputSize, size_t memorySize)
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

    mat w_inputMemory(memorySize, vec(inputSize));
    vec w_memory(memorySize, 1.0);
    vec w_maxnet(memorySize, 1.0);

    mat w_maxnetLoopback(memorySize, vec(memorySize, -m_maxnetSuppression));
    for (size_t i = 0; i < memorySize; i++) {
        w_maxnetLoopback[i][i] = 1;
    }

    // Build
    m_inputLayer.connectAllToAll(m_memoryLayer, w_inputMemory);
    m_memoryLayer.connectOneToOne(m_maxnetLayer, w_memory);
    m_maxnetLayer.connectAllToAll(m_maxnetLayer, w_maxnetLoopback);
    m_maxnetLayer.connectOneToOne(m_outputLayer, w_maxnet);
}

bool HammingAnn::learn(const std::vector<vec> &samples)
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
    mat weights(m_inputSize, vec(m_memorySize));
    for (size_t i = 0; i < m_memorySize; i++) {
        for (size_t j = 0; j < m_inputSize; j++)
            weights[j][i] = samples[i][j] / 2.0;
    }

    // Set weights
    m_inputLayer.setOutputWeights(weights);

    return true;
}

vec HammingAnn::recognize(const vec &sample)
{
    if (sample.size() < m_inputSize) {
        return vec(m_memorySize, 0.0);
    }

    // Move input layer
    m_inputLayer.setInputs(sample);
    m_inputLayer.move();

    // Move memory layer
    m_memoryLayer.move();

    // Initial move of maxnet layer
    m_maxnetLayer.move();

    // Disconnect memory layer from maxnet layer
    mat w(m_memorySize, {0.0});
    m_memoryLayer.setOutputWeights(w);

    // Maxnet's competition
    vec prev(m_memorySize);
    vec cur = m_maxnetLayer.getOutputs();
    while(!VecUtills::compare(prev, cur, m_accuracy)) {
        m_maxnetLayer.move();

        prev = cur;
        cur = m_maxnetLayer.getOutputs();

        qDebug() << m_maxnetLayer.getOutputs();
    }

    // Move output layer
    m_outputLayer.move();

    return m_outputLayer.getOutputs();
}
