#include "utills.hpp"

#include <cmath>

namespace Utills {

bool compare(const std::vector<double> &vec1, const std::vector<double> &vec2, double accuracy)
{
    if (vec1.size() != vec2.size()) {
        return false;
    }

    for (size_t i = 0; i < vec1.size(); i++) {
        if (fabs(vec1[i] - vec2[i]) > accuracy) {
            return false;
        }
    }

    return true;
}

QVector<int> getIndexes(const std::vector<double> &vec)
{
    QVector<int> indexes;

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] > 0.0) {
            indexes.push_back(i);
        }
    }

    return indexes;
}

} // Utills
