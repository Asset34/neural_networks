#include "imagedrawerwidget.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFrame>
#include <QSpinBox>
#include <QPushButton>

#include <QFileDialog>

#include "imagedrawer.hpp"

ImageDrawerWidget::ImageDrawerWidget(int width, int height, QWidget *parent)
    : QWidget(parent)
{    
    // Create image drawer
    m_drawer = new ImageDrawer(width, height);
    m_drawer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create frame layout
    m_frameLayout = new QVBoxLayout;
    m_frameLayout->setContentsMargins(0, 0, 0, 0);
    m_frameLayout->addWidget(m_drawer);

    // Create drawer frame
    m_drawerFrame = new QFrame;
    m_drawerFrame->setLineWidth(2);
    m_drawerFrame->setFrameShape(QFrame::Panel);
    m_drawerFrame->setFrameShadow(QFrame::Plain);
    m_drawerFrame->setLayout(m_frameLayout);

    // Create width spin box
    m_widthSpinBox = new QSpinBox;
    m_widthSpinBox->setRange(1, 10000);
    m_widthSpinBox->setValue(width);

    // Create height spin box
    m_heightSpinBox = new QSpinBox;
    m_heightSpinBox->setRange(1, 10000);
    m_heightSpinBox->setValue(height);

    // Create size layout
    m_sizeLayout = new QFormLayout;
    m_sizeLayout->setContentsMargins(0, 0, 0, 0);
    m_sizeLayout->addRow("Width: ", m_widthSpinBox);
    m_sizeLayout->addRow("Height: ", m_heightSpinBox);

    // Create drawer layout
    m_drawerLayout = new QVBoxLayout;
    m_drawerLayout->setContentsMargins(0, 0, 0, 0);
    m_drawerLayout->addWidget(m_drawerFrame);
    m_drawerLayout->addLayout(m_sizeLayout);

    // Create control buttons
    m_loadButton = new QPushButton("Load");
    m_saveButton = new QPushButton("Save");
    m_generateButton = new QPushButton("Generate");
    m_clearButton = new QPushButton("Clear");

    // Create control layoyt;
    m_controlLayout = new QVBoxLayout;
    m_controlLayout->setContentsMargins(0, 0, 0, 0);
    m_controlLayout->addWidget(m_loadButton);
    m_controlLayout->addWidget(m_saveButton);
    m_controlLayout->addWidget(m_generateButton);
    m_controlLayout->addWidget(m_clearButton);
    m_controlLayout->addStretch(1);

    // Create main layout
    m_mainLayout = new QHBoxLayout;
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->addLayout(m_drawerLayout);
    m_mainLayout->addLayout(m_controlLayout);

    // Create widget
    setLayout(m_mainLayout);
    setContentsMargins(5, 5, 5, 5);

    // Create connections
    connect(
        m_widthSpinBox,
        static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        m_drawer,
        &ImageDrawer::setWidth
        );
    connect(
        m_heightSpinBox,
        static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        m_drawer,
        &ImageDrawer::setHeight
        );

    connect(m_loadButton, &QPushButton::clicked, this, &ImageDrawerWidget::load);
    connect(m_saveButton, &QPushButton::clicked, this, &ImageDrawerWidget::save);
    connect(m_generateButton, &QPushButton::clicked, this, &ImageDrawerWidget::generate);
    connect(m_clearButton, &QPushButton::clicked, this, &ImageDrawerWidget::clear);
    connect(m_drawer, &ImageDrawer::imageChanged, this, &ImageDrawerWidget::imageChanged);
}

const QImage &ImageDrawerWidget::getImage() const
{
    return m_drawer->getImage();
}

void ImageDrawerWidget::setImage(const QImage &image)
{
    m_drawer->setImage(image);
}

void ImageDrawerWidget::clear()
{
    m_drawer->clear();
}

void ImageDrawerWidget::generate()
{
    m_drawer->generate();
}

void ImageDrawerWidget::load()
{
    QString path = QFileDialog::getOpenFileName(
                this,
                tr("Open Image"),
                "",
                tr("Image files (*.png *.jpg *jpeg *.png *.bmp)")
                );

    if (!path.isNull()) {
        setImage(QImage(path));
    }
}

void ImageDrawerWidget::save()
{
    QString path = QFileDialog::getSaveFileName(
                this,
                tr("Save image"),
                "",
                tr("(*.bmp)")
                );

    if (!path.isNull()) {
        m_drawer->getImage().save(path);
    }
}
