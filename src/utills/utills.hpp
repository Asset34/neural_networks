#ifndef UTILLS_HPP
#define UTILLS_HPP

#include <QVector>

#include <neural_network_classes/entities.hpp>

namespace Utills {

bool compare(const std::vector<double> &vec1, const std::vector<double> &vec2, double accuracy);
QVector<int> getIndexes(const std::vector<double> &vec);

} // Utills

#endif // UTILLS_HPP
