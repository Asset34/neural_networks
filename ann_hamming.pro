QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ann_hamming
TEMPLATE = app

SOURCES += src/main.cpp \
    src/hammingann.cpp \
    src/neural_network_classes/synapse.cpp \
    src/neural_network_classes/neuron.cpp \
    src/neural_network_classes/inputneuron.cpp \
    src/neural_network_classes/layer.cpp \
    src/neural_network_classes/inputlayer.cpp \
    src/ui/SignedImageList_view_model/signedimagelistmodel.cpp \
    src/ui/SignedImageList_view_model/signedimagetableproxymodel.cpp \
    src/ui/SignedImageList_view_model/signedimageitemdelegate.cpp \
    src/ui/SignedImageList_view_model/signedimagetablewidget.cpp \
    src/ui/image_drawer/ImageDrawer.cpp \
    src/ui/mainwindow.cpp \
    src/utills/convertions.cpp \
    src/utills/utills.cpp

HEADERS += \
    src/hammingann.hpp \
    src/neural_network_classes/entities.hpp \
    src/neural_network_classes/neuron.hpp \
    src/neural_network_classes/inputneuron.hpp \
    src/neural_network_classes/layer.hpp \
    src/neural_network_classes/inputlayer.hpp \
    src/ui/SignedImageList_view_model/signedimagelistmodel.hpp \
    src/ui/SignedImageList_view_model/signedimagetableproxymodel.hpp \
    src/ui/SignedImageList_view_model/signedimageitemdelegate.hpp \
    src/ui/SignedImageList_view_model/signedimagetablewidget.hpp \
    src/ui/image_drawer/ImageDrawer.hpp \
    src/ui/mainwindow.hpp \
    src/utills/convertions.hpp \
    src/utills/utills.hpp

INCLUDEPATH += $$PWD/src
