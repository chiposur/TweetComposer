#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QList>
#include <QObject>

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
    void loadTweetDrafts();
    void loadTweetTemplates();

    bool saveSettings();
    bool saveTweetDrafts();
    bool saveTweetTemplates();

signals:

private:
    JsonSerializer *jsonSerializer;
};

#endif // SETTINGSMANAGER_H
