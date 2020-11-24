QT += core gui widgets

CONFIG += c++17

INCLUDEPATH += \
    ./ \
    src/ \
    include/ \

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/settingsmanager.cpp \
    src/composewidget.cpp \
    src/tweetdraft.cpp \
    src/tweetdraftswidget.cpp \
    src/tweettemplate.cpp \
    src/tweettemplateswidget.cpp \

HEADERS += \
    include/mainwindow.h \
    include/settingsmanager.h \
    include/composewidget.h \
    include/tweetdraft.h \
    include/tweettemplate.h \
    include/tweetdraftswidget.h \
    include/tweettemplateswidget.h \

RESOURCES += \
    images.qrc
