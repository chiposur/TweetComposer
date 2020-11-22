QT += core gui widgets

CONFIG += c++17

INCLUDEPATH += \
    ./ \
    src/ \
    include/ \

SOURCES += \
    src/composewidget.cpp \
    src/main.cpp \
    src/mainwindow.cpp \

HEADERS += \
    include/mainwindow.h \
    include/composewidget.h

RESOURCES += \
    images.qrc
