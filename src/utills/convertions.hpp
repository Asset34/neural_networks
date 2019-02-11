#ifndef CONVERTIONS_HPP
#define CONVERTIONS_HPP

#include <QImage>

#include <neural_networks/ann_core/entities.hpp>

namespace Convertions {

std::vector<double> toBipolarVector(const QImage &image);

} // Convertions

#endif // CONVERTIONS_HPP
