TEMPLATE = app
CONFIG += c++11
CONFIG -= app_bundle
#CONFIG -= qt

QT += core

SOURCES += src/main.cpp \
    src/hammingann.cpp \
    src/ann_classes/synapse.cpp \
    src/ann_classes/neuron.cpp \
    src/ann_classes/inputneuron.cpp \
    src/ann_classes/layer.cpp \
    src/ann_classes/inputlayer.cpp \
    src/utills/vecutills.cpp

HEADERS += \
    src/hammingann.hpp \
    src/ann_classes/entities.hpp \
    src/ann_classes/neuron.hpp \
    src/ann_classes/inputneuron.hpp \
    src/ann_classes/layer.hpp \
    src/ann_classes/inputlayer.hpp \
    src/utills/vecutills.hpp
