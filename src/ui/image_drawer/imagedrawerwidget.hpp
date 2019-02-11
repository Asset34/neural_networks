#ifndef IMAGEDRAWERWIDGET_HPP
#define IMAGEDRAWERWIDGET_HPP

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;
class QFormLayout;
class QFrame;
class QSpinBox;
class QPushButton;
class ImageDrawer;

class ImageDrawerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImageDrawerWidget(int width, int height, QWidget *parent = nullptr);

    const QImage &getImage() const;

public slots:
    void setImage(const QImage &image);
    void clear();
    void generate();

private:
    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_drawerLayout;
    QVBoxLayout *m_controlLayout;
    QVBoxLayout *m_frameLayout;
    QFormLayout *m_sizeLayout;

    QFrame *m_drawerFrame;

    QSpinBox *m_widthSpinBox;
    QSpinBox *m_heightSpinBox;

    QPushButton *m_loadButton;
    QPushButton *m_saveButton;
    QPushButton *m_generateButton;
    QPushButton *m_clearButton;

    ImageDrawer *m_drawer;

private slots:
    void load();
    void save();

signals:
    void imageChanged(const QImage &image);

};

#endif // IMAGEDRAWERWIDGET_HPP
