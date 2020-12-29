QT += core gui widgets network

CONFIG += c++17

INCLUDEPATH += \
    ./ \
    src/ \
    include/ \

SOURCES += \
    src/datastore.cpp \
    src/main.cpp \
    src/customcontrols.cpp \
    src/settings.cpp \
    src/styles.cpp \
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
    src/toastwidget.cpp \
    src/scrollablecontainer.cpp \
    src/twitterapiclient.cpp \

HEADERS += \
    include/settings.h \
    include/customcontrols.h \
    include/settingsdialog.h \
    include/mainwindow.h \
    include/settingsmanager.h \
    include/composewidget.h \
    include/styles.h \
    include/tweetdraft.h \
    include/tweettemplate.h \
    include/tweetdraftswidget.h \
    include/tweettemplateswidget.h \
    include/datastore.h \
    include/toast.h \
    include/tweetdraftsitemwidget.h \
    include/tweettemplatesitemwidget.h \
    include/jsonserializer.h \
    include/toastwidget.h \
    include/twitterbootstrapstyles.h \
    include/scrollablecontainer.h \
    include/twitterapiclient.h \

RESOURCES += \
    images.qrc
