#include "hebbiannetwork.hpp"

HebbianNetwork::HebbianNetwork(size_t inputSize, size_t memorySize)
    : NeuralNetwork(inputSize, memorySize),
      m_inputLayer(inputSize),
      m_outputLayer(memorySize),
      m_learnFactor(0.3),
      m_accuracy(1e-7),
      m_curIteration(0)
{
    setActivationFuncs();
    buildConnections();
}

std::string HebbianNetwork::getName() const
{
    return "Hebbian Network";
}

bool HebbianNetwork::learn(const std::vector<LearnUnit> &units)
{
    if (units.size() != m_memorySize) {
        return false;
    }

    reset();

    WeightMat weights(m_memorySize, WeightVec(m_inputSize, 0.0));
    std::vector<double> biases(m_memorySize, 0.0);
    do {
        for (LearnUnit unit : units) {
            adjustBiases(biases, unit);
            adjustWeights(weights, unit);
        }

        m_outputLayer.setBiases(biases);
        m_outputLayer.setWeights(weights);

        m_curIteration++;
    }
    while(!stopCriterion(units));

    return true;
}

std::tuple<std::vector<double>, bool> HebbianNetwork::recognize(
        const std::vector<double> &sample)
{
    if (sample.size() != m_inputSize) {
        return std::make_tuple(std::vector<double>(m_memorySize, 0.0), false);
    }

    m_inputLayer.setInputs(sample);
    m_inputLayer.move();
    m_outputLayer.move();

    return std::make_tuple(m_outputLayer.getOutputs(), true);
}

void HebbianNetwork::rebuild(size_t inputSize, size_t memorySize)
{
    NeuralNetwork::rebuild(inputSize, memorySize);

    // Rebuild layers
    m_inputLayer = InputLayer(inputSize);
    m_outputLayer = Layer(memorySize);

    setActivationFuncs();
    buildConnections();
}

void HebbianNetwork::setActivationFuncs()
{
    m_outputLayer.setActivationFunc(
        [this](double x) -> double
        {
            if (x <= m_accuracy) return -1.0;
            else                 return  1.0;
        }
    );
}

void HebbianNetwork::buildConnections()
{
    m_inputLayer.connectAllToAll(m_outputLayer);
}

void HebbianNetwork::adjustBiases(std::vector<double> &biases, const LearnUnit &unit)
{
    for (size_t i = 0 ; i < m_memorySize; i++) {
        biases[i] += m_learnFactor * unit.result[i] * (1.0 - unit.result[i] * biases[i]);
    }
}

void HebbianNetwork::adjustWeights(WeightMat &weights, const LearnUnit &unit)
{
    for (size_t i = 0; i < m_memorySize; i++) {
        for (size_t j = 0; j < m_inputSize; j++) {
            weights[i][j] += m_learnFactor * unit.result[i] * (unit.sample[j] - unit.result[i] * weights[i][j]);
        }
    }
}

bool HebbianNetwork::stopCriterion(const std::vector<LearnUnit> &units)
{
    if (m_curIteration >= MAX_ITERATIONS) {
        return true;
    }

    for (LearnUnit unit : units) {
        m_inputLayer.setInputs(unit.sample);
        m_inputLayer.move();
        m_outputLayer.move();

        if (!Utills::compare(
                    m_outputLayer.getOutputs(),
                    unit.result,
                    m_accuracy
                )) {
            return false;
        }
    }

    return true;
}

void HebbianNetwork::reset()
{
    m_curIteration = 0;
}
