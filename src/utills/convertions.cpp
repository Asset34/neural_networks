#include "convertions.hpp"

namespace Convertions {

std::vector<double> toBipolarVector(const QImage &image)
{
    // Convert image to monochrome format
    QImage convertedImage;
    if (image.format() != QImage::Format::Format_Mono) {
        convertedImage = image.convertToFormat(QImage::Format::Format_Mono);
    }
    else {
        convertedImage = image;
    }

    // Create bipolar vector
    std::vector<double> bipolar;
    bipolar.reserve(convertedImage.width() * convertedImage.height());
    bool isWhite;
    for (int i = 0; i < convertedImage.height(); i++) {
        for (int j = 0; j < convertedImage.width(); j++) {
            isWhite = (convertedImage.pixelColor(j, i) == Qt::GlobalColor::white);
            bipolar.push_back(isWhite ? -1.0 : 1.0);
        }
    }

    return bipolar;
}

} // Convertions
