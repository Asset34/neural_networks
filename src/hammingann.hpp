#ifndef HAMMINGANN_HPP
#define HAMMINGANN_HPP

#include "ann_classes/neuron.hpp"
#include "ann_classes/inputneuron.hpp"
#include "ann_classes/layer.hpp"
#include "ann_classes/inputlayer.hpp"
#include "ann_classes/entities.hpp"
#include "utills/vecutills.hpp"

class HammingAnn
{
public:
    HammingAnn(size_t inputSize, size_t memorySize);

    bool learn(const std::vector<vec> &samples);
    vec recognize(const vec &sample);

private:
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

#endif // HAMMINGANN_HPP
