#ifndef VECUTILLS_HPP
#define VECUTILLS_HPP

#include <src/ann_classes/entities.hpp>

namespace VecUtills {

bool compare(const vec &v1, const vec &v2, double accuracy);
bool isImpulse(const vec &v);
int toIndex(const vec &v);

} // VecUtills

#endif // VECUTILLS_HPP
