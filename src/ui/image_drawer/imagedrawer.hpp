#ifndef IMAGEDRAWER_HPP
#define IMAGEDRAWER_HPP

#include <QWidget>
#include <QSize>
#include <QImage>
#include <QRandomGenerator>

class ImageDrawer : public QWidget
{
    Q_OBJECT

public:
    explicit ImageDrawer(int width, int height, QWidget *parent = nullptr);

    int getWidth() const;
    int getHeight() const;
    QSize getSize() const;

    const QImage &getImage() const;

    bool isGridEnabled() const;

public slots:
    void setWidth(int width);
    void setHeight(int height);
    void setSize(int width, int height);
    void setImage(const QImage &image);
    void setGridEnabled(bool flag);

    void generate();
    void clear();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    void drawImage(QPainter *painter);
    void drawGrid(QPainter *painter);

    void setRandom(const QPoint &point);

    bool checkPoint(const QPoint &realPoint) const;

    QPoint toImagePoint(const QPoint &realPoint) const;

    void updateImage();

    constexpr static const int PIXCOLOR_WHITE = 0;
    constexpr static const int PIXCOLOR_BLACK = 1;

    static QRandomGenerator m_randGenerator;

    QImage m_image;

    QVector<QRgb> m_colorIndexes;

    bool m_isGridEnabled;

signals:
    void imageChanged(const QImage &image);

};

#endif // IMAGEDRAWER_HPP
