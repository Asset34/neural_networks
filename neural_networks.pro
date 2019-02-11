QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = neural_networks
TEMPLATE = app

SOURCES += src/main.cpp \
    src/neural_networks/ann_core/synapse.cpp \
    src/neural_networks/ann_core/neuron.cpp \
    src/neural_networks/ann_core/inputneuron.cpp \
    src/neural_networks/ann_core/layer.cpp \
    src/neural_networks/ann_core/inputlayer.cpp \
    src/ui/SignedImageList_view_model/signedimagelistmodel.cpp \
    src/ui/SignedImageList_view_model/signedimagetableproxymodel.cpp \
    src/ui/SignedImageList_view_model/signedimageitemdelegate.cpp \
    src/ui/SignedImageList_view_model/signedimagetablewidget.cpp \
    src/ui/SignedImageList_view_model/signedimagetablemanager.cpp \
    src/ui/image_drawer/ImageDrawer.cpp \
    src/ui/image_drawer/ImageDrawerWidget.cpp \
    src/ui/mainwindow.cpp \
    src/utills/convertions.cpp \
    src/utills/utills.cpp \
    src/neural_networks/hammingnetwork.cpp \
    src/neural_networks/hebbiannetwork.cpp \
    src/neural_networks/ann_core/neuralnetwork.cpp

HEADERS += \
    src/neural_networks/ann_core/entities.hpp \
    src/neural_networks/ann_core/neuron.hpp \
    src/neural_networks/ann_core/inputneuron.hpp \
    src/neural_networks/ann_core/layer.hpp \
    src/neural_networks/ann_core/inputlayer.hpp \
    src/ui/SignedImageList_view_model/signedimagelistmodel.hpp \
    src/ui/SignedImageList_view_model/signedimagetableproxymodel.hpp \
    src/ui/SignedImageList_view_model/signedimageitemdelegate.hpp \
    src/ui/SignedImageList_view_model/signedimagetablewidget.hpp \
    src/ui/SignedImageList_view_model/signedimagetablemanager.hpp \
    src/ui/image_drawer/ImageDrawer.hpp \
    src/ui/image_drawer/ImageDrawerWidget.hpp \
    src/ui/mainwindow.hpp \
    src/utills/convertions.hpp \
    src/utills/utills.hpp \
    src/neural_networks/hammingnetwork.hpp \
    src/neural_networks/hebbiannetwork.hpp \
    src/neural_networks/ann_core/neuralnetwork.hpp

INCLUDEPATH += $$PWD/src
