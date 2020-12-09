#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QList>
#include <QObject>
#include <QSettings>

#include "tweetdraft.h"
#include "tweettemplate.h"
#include "jsonserializer.h"

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager(QObject *parent = nullptr);

    static SettingsManager *getInstance();

    void loadSettings();
    void loadWindowSize(QSize &windowSize);
    void loadTweetDrafts();
    void loadTweetTemplates();

    bool saveSettings();
    bool saveWindowSize(const QSize &size);
    bool saveTweetDrafts();
    bool saveTweetTemplates();

signals:

private:
    JsonSerializer *jsonSerializer;
    QSettings *settings;
};

#endif // SETTINGSMANAGER_H
