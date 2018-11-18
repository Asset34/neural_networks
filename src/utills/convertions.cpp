#include "convertions.hpp"

namespace Convertions {

std::vector<double> toBipolarVector(const QImage &image)
{
    // Convert image to grayscale format
    QImage convertedImage;
    if (image.format() != QImage::Format_Grayscale8) {
        convertedImage = image.convertToFormat(QImage::Format_Grayscale8);
    }
    else {
        convertedImage = image;
    }

    // Get bipolar vector from converted image
    int pixelCount = convertedImage.width() * convertedImage.height();
    std::vector<double> bipolar(pixelCount);

    uchar *bits = convertedImage.bits();
    for (int i = 0; i < pixelCount; i++) {
        bipolar[i] = (bits[i] == 0) ? -1.0 : 1.0;
    }

    return bipolar;
}

} // Convertions
