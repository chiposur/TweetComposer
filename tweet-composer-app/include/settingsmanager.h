#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QList>
#include <QObject>

#include <tweetdraft.h>
#include <tweettemplate.h>

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager(QObject *parent = nullptr);

    static SettingsManager *getInstance();

    void loadTweetDrafts();
    void loadTweetTemplates();

    bool saveSettings();
    bool saveTweetDrafts();
    bool saveTweetTemplates();

    QString serializeSettingsToJson();

signals:

private:
};

#endif // SETTINGSMANAGER_H
