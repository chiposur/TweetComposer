#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QList>
#include <QObject>
#include <QSettings>

#include "datastore.h"
#include "jsonserializer.h"
#include "tweetdraft.h"
#include "tweettemplate.h"

class SettingsManager : public QObject
{
    Q_OBJECT

public:
    explicit SettingsManager();

    static SettingsManager *getInstance();

    void setDependencies(DataStore *dataStore, JsonSerializer *jsonSerializer);

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
    static const QString encryptTweetDraftsPath;
    static const QString encryptTweetTemplatesPath;
    static const QString persistWindowSizePath;
    static const QString apiKeyPath;
    static const QString apiSecretPath;
    static const QString accessTokenPath;
    static const QString accessTokenSecretPath;
    static const QString windowGeometryPath;
    static const QString tweetDraftsJsonPath;
    static const QString tweetTemplatesJsonPath;

    DataStore *dataStore = nullptr;
    JsonSerializer *jsonSerializer = nullptr;
    QSettings *settings;
};

#endif // SETTINGSMANAGER_H
