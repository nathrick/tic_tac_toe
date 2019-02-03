TEMPLATE = app

QT += qml quick
CONFIG += c++17

SOURCES += main.cpp \
    gameengine.cpp

RESOURCES += qml.qrc \
    pictures.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    gameengine.h
