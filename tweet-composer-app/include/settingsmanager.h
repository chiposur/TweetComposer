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
    void loadWindowGeometry(QByteArray &windowGeometry);
    void loadTweetDrafts();
    void loadTweetTemplates();

    bool saveSettings();
    bool saveWindowGeometry(const QByteArray &windowGeometry);
    bool saveTweetDrafts();
    bool saveTweetTemplates();

signals:

private:
    JsonSerializer *jsonSerializer;
    QSettings *settings;
};

#endif // SETTINGSMANAGER_H
