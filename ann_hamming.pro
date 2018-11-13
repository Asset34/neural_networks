QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ann_hamming
TEMPLATE = app

SOURCES += src/main.cpp \
    src/hammingann.cpp \
    src/utills/vecutills.cpp \
    src/ann_classes/synapse.cpp \
    src/ann_classes/neuron.cpp \
    src/ann_classes/inputneuron.cpp \
    src/ann_classes/layer.cpp \
    src/ann_classes/inputlayer.cpp \
    src/ui/SignedImageList_view_model/signedimagelistmodel.cpp \
    src/ui/SignedImageList_view_model/signedimagetableproxymodel.cpp \
    src/ui/SignedImageList_view_model/signedimageitemdelegate.cpp \
    src/ui/SignedImageList_view_model/signedimagelistwidget.cpp

HEADERS += \
    src/hammingann.hpp \
    src/utills/vecutills.hpp \
    src/ann_classes/entities.hpp \
    src/ann_classes/neuron.hpp \
    src/ann_classes/inputneuron.hpp \
    src/ann_classes/layer.hpp \
    src/ann_classes/inputlayer.hpp \
    src/ui/SignedImageList_view_model/signedimagelistmodel.hpp \
    src/ui/SignedImageList_view_model/signedimagetableproxymodel.hpp \
    src/ui/SignedImageList_view_model/signedimageitemdelegate.hpp \
    src/ui/SignedImageList_view_model/signedimagelistwidget.hpp
