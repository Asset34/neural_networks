#include "vecutills.hpp"

#include <cmath>

namespace VecUtills {

bool compare(const vec &v1, const vec &v2, double accuracy)
{
    if (v1.size() != v2.size()) {
        return false;
    }

    for (size_t i = 0; i < v1.size(); i++) {
        if (fabs(v1[i] - v2[i]) > accuracy) {
            return false;
        }
    }

    return true;
}

bool isImpulse(const vec &v)
{
    int count = 0;

    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] > 0.0) {
            count++;
        }
    }

    return (count == 1) ? true : false;
}

int toIndex(const vec &v)
{
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] > 0.0) {
            return i;
        }
    }

    return -1;
}

} // VecUtills
