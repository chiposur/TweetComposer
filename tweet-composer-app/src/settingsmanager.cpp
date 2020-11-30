#include "settingsmanager.h"
#include "datastore.h"
#include "jsonserializer.h"
#include "settings.h"

#include <QSettings>
#include <QString>

QSettings settings("Chip Osur", "TweetComposer");

const QString userSettingsPath("settings");
const QString encryptTweetDraftsPath("settings/encryptTweetDrafts");
const QString encryptTweetTemplatesPath("settings/encryptTweetTemplates");
const QString storagePath("storage");
const QString tweetDraftsJsonPath("storage/tweetDraftsJson");
const QString tweetTemplatesJsonPath("storage/tweetTemplatesJson");

SettingsManager::SettingsManager(QObject *parent) : QObject(parent)
{
    jsonSerializer = JsonSerializer::getInstance();
}

SettingsManager *SettingsManager::getInstance()
{
    static SettingsManager settingsMgr;
    return &settingsMgr;
}

void SettingsManager::loadSettings()
{
    Settings::encryptDraftsOnDisk = settings.value(encryptTweetDraftsPath, false).toBool();
    Settings::encryptTemplatesOnDisk = settings.value(encryptTweetTemplatesPath, false).toBool();
}

void SettingsManager::loadTweetDrafts()
{
    QVector<TweetDraft> tweetDrafts = QVector<TweetDraft>();
    if (jsonSerializer->deserialize(tweetDrafts, settings.value(tweetDraftsJsonPath).toString()))
    {
        DataStore::getInstance()->setTweetDrafts(tweetDrafts);
    }
}

void SettingsManager::loadTweetTemplates()
{
    QVector<TweetTemplate> tweetTemplates;
    if (jsonSerializer->deserialize(tweetTemplates, settings.value(tweetTemplatesJsonPath).toString()))
    {
        DataStore::getInstance()->setTweetTemplates(tweetTemplates);
    }
}

bool SettingsManager::saveSettings()
{
    settings.setValue(encryptTweetDraftsPath, Settings::encryptDraftsOnDisk);
    settings.setValue(encryptTweetTemplatesPath, Settings::encryptTemplatesOnDisk);
    return true;
}

bool SettingsManager::saveTweetDrafts()
{
    bool success;
    QString tweetsDraftJson = jsonSerializer->tweetDraftsJson(success);

    if (success)
    {
        settings.setValue(tweetDraftsJsonPath, tweetsDraftJson);
        return true;
    }
    else
    {
        return false;
    }
}

bool SettingsManager::saveTweetTemplates()
{
    bool success;
    QString tweetsTemplatesJson = jsonSerializer->tweetTemplatesJson(success);

    if (success)
    {
        settings.setValue(tweetTemplatesJsonPath, tweetsTemplatesJson);
        return true;
    }
    else
    {
        return false;
    }
}
