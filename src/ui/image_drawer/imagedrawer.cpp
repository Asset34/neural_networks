#include "imagedrawer.hpp"

#include <QPainter>
#include <QMouseEvent>
#include <QtMath>
#include <QDateTime>

QRandomGenerator ImageDrawer::m_randGenerator =
        QRandomGenerator(static_cast<quint32>(QDateTime::currentSecsSinceEpoch()));

ImageDrawer::ImageDrawer(int width, int height, QWidget *parent)
    : QWidget(parent),
      m_image(width, height, QImage::Format::Format_Mono),
      m_colorIndexes({QColor(Qt::white).rgb(), QColor(Qt::black).rgb()}),
      m_isGridEnabled(true)
{
    m_image.setColorTable(m_colorIndexes);
    clear();
}

int ImageDrawer::getWidth() const
{
    return m_image.width();
}

int ImageDrawer::getHeight() const
{
    return m_image.height();
}

QSize ImageDrawer::getSize() const
{
    return m_image.size();
}

const QImage &ImageDrawer::getImage() const
{
    return m_image;
}

bool ImageDrawer::isGridEnabled() const
{
    return m_isGridEnabled;
}

void ImageDrawer::setWidth(int width)
{
    setSize(width, m_image.height());
}

void ImageDrawer::setHeight(int height)
{
    setSize(m_image.width(), height);
}

void ImageDrawer::setSize(int width, int height)
{
    m_image = QImage(width, height, QImage::Format::Format_Mono);
    m_image.setColorTable(m_colorIndexes);

    clear();
    updateImage();
}

void ImageDrawer::setImage(const QImage &image)
{
    if (image.format() == QImage::Format::Format_Mono) {
        m_image = image;
    }
    else {
        m_image = image.convertToFormat(QImage::Format::Format_Mono);
    }
    m_image.setColorTable(m_colorIndexes);

    updateImage();
}

void ImageDrawer::setGridEnabled(bool flag)
{
    m_isGridEnabled = flag;
    update();
}

void ImageDrawer::generate()
{
    for (int i = 0; i < m_image.width(); i++) {
        for (int j = 0; j < m_image.height(); j++) {
            setRandom(QPoint(i, j));
        }
    }

    updateImage();
}

void ImageDrawer::clear()
{
    m_image.fill(PIXCOLOR_WHITE);

    updateImage();
}

void ImageDrawer::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);

    // Set coord system
    painter.setWindow(0, 0, m_image.width(), m_image.height());

    // Draw image
    drawImage(&painter);

    // Draw grid
    if (m_isGridEnabled) {
        drawGrid(&painter);
    }

    painter.end();
}

void ImageDrawer::mousePressEvent(QMouseEvent *event)
{
    if (checkPoint(event->pos())) {
        QPoint imagePoint = toImagePoint(event->pos());

        if (event->button() == Qt::MouseButton::LeftButton) {
            m_image.setPixel(imagePoint, PIXCOLOR_BLACK);
        }
        else if(event->button() == Qt::MouseButton::RightButton) {
            m_image.setPixel(imagePoint, PIXCOLOR_WHITE);
        }

        updateImage();
    }

    QWidget::mousePressEvent(event);
}

void ImageDrawer::mouseMoveEvent(QMouseEvent *event)
{
    if (checkPoint(event->pos()) && event->buttons() &
            (Qt::MouseButton::LeftButton | Qt::MouseButton::RightButton)) {
        QPoint imagePoint = toImagePoint(event->pos());

        if (event->buttons() & Qt::MouseButton::LeftButton) {
            m_image.setPixel(imagePoint, PIXCOLOR_BLACK);
        }
        else {
            m_image.setPixel(imagePoint, PIXCOLOR_WHITE);
        }

        updateImage();
    }

    QWidget::mouseMoveEvent(event);
}

void ImageDrawer::drawImage(QPainter *painter)
{
    painter->save();

    painter->drawImage(0, 0, m_image);

    painter->restore();
}

void ImageDrawer::drawGrid(QPainter *painter)
{
    painter->save();

    painter->setPen(QPen(Qt::gray, 0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));

    for (int x = 1; x < m_image.width(); x++) {
        painter->drawLine(QLine(x, 0, x, m_image.height()));
    }

    for (int y = 1; y < m_image.height(); y++) {
        painter->drawLine(QLine(0, y, m_image.width(), y));
    }

    painter->restore();
}

void ImageDrawer::setRandom(const QPoint &point)
{
    int value = m_randGenerator.bounded(0, 2);

    m_image.setPixel(point, value);
}

bool ImageDrawer::checkPoint(const QPoint &realPoint) const
{
    if (realPoint.x() < 0 || realPoint.x() >= width()) {
        return false;
    }
    if (realPoint.y() < 0 || realPoint.y() >= height()) {
        return false;
    }

    return true;
}

QPoint ImageDrawer::toImagePoint(const QPoint &realPoint) const
{
    int x = qFloor(realPoint.x() * static_cast<double>(m_image.width()) / width());
    int y = qFloor(realPoint.y() * static_cast<double>(m_image.height()) / height());

    return QPoint(x, y);
}

void ImageDrawer::updateImage()
{
    update();
    emit imageChanged(m_image);
}
