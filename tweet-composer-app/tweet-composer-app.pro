QT += core gui widgets

CONFIG += c++17

INCLUDEPATH += \
    ./ \
    src/ \
    include/ \

SOURCES += \
    src/datastore.cpp \
    src/main.cpp \
    src/customcontrols.cpp \
    src/toast.cpp \
    src/settingsdialog.cpp \
    src/mainwindow.cpp \
    src/settingsmanager.cpp \
    src/composewidget.cpp \
    src/tweetdraft.cpp \
    src/tweetdraftsitemwidget.cpp \
    src/tweetdraftswidget.cpp \
    src/tweettemplate.cpp \
    src/tweettemplatesitemwidget.cpp \
    src/tweettemplateswidget.cpp \
    src/jsonserializer.cpp \

HEADERS += \
    include/settings.h \
    include/customcontrols.h \
    include/settingsdialog.h \
    include/mainwindow.h \
    include/settingsmanager.h \
    include/composewidget.h \
    include/tweetdraft.h \
    include/tweettemplate.h \
    include/tweetdraftswidget.h \
    include/tweettemplateswidget.h \
    include/datastore.h \
    include/toast.h \
    include/tweetdraftsitemwidget.h \
    include/tweettemplatesitemwidget.h \
    include/jsonserializer.h \

RESOURCES += \
    images.qrc
