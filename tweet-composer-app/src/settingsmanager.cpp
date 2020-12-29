#include "settingsmanager.h"
#include "datastore.h"
#include "jsonserializer.h"
#include "settings.h"

#include <QString>

const QString SettingsManager::encryptTweetDraftsPath("settings/encryptTweetDrafts");
const QString SettingsManager::encryptTweetTemplatesPath("settings/encryptTweetTemplates");
const QString SettingsManager::persistWindowSizePath("settings/persistWindowSize");
const QString SettingsManager::apiKeyPath("twitterApi/apiKey");
const QString SettingsManager::apiSecretPath("twitterApi/apiSecret");
const QString SettingsManager::accessTokenPath("twitterApi/accessToken");
const QString SettingsManager::accessTokenSecretPath("twitterApi/accessTokenSecret");
const QString SettingsManager::windowGeometryPath("storage/windowGeometry");
const QString SettingsManager::tweetDraftsJsonPath("storage/tweetDraftsJson");
const QString SettingsManager::tweetTemplatesJsonPath("storage/tweetTemplatesJson");

SettingsManager::SettingsManager()
{
    jsonSerializer = JsonSerializer::getInstance();
    settings = new QSettings("Chip Osur", "TweetComposer");
}

SettingsManager *SettingsManager::getInstance()
{
    static SettingsManager settingsMgr;
    return &settingsMgr;
}

void SettingsManager::loadSettings()
{
    Settings::apiKey = settings->value(apiKeyPath, "").toString();
    Settings::apiSecret = settings->value(apiSecretPath, "").toString();
    Settings::accessToken = settings->value(accessTokenPath, "").toString();
    Settings::accessTokenSecret = settings->value(accessTokenSecretPath, "").toString();
    Settings::encryptDraftsOnDisk = settings->value(encryptTweetDraftsPath, false).toBool();
    Settings::encryptTemplatesOnDisk = settings->value(encryptTweetTemplatesPath, false).toBool();
    Settings::persistWindowState = settings->value(persistWindowSizePath, false).toBool();
}

void SettingsManager::loadWindowGeometry(QByteArray &windowGeometry)
{
    windowGeometry = settings->value(windowGeometryPath).toByteArray();
}

void SettingsManager::loadTweetDrafts()
{
    QVector<TweetDraft> tweetDrafts;
    if (jsonSerializer->deserialize(tweetDrafts, settings->value(tweetDraftsJsonPath).toString()))
    {
        int index = 0;
        while (index < tweetDrafts.count())
        {
            tweetDrafts[index].setId(++TweetDraft::numDrafts);
            ++index;
        }

        DataStore::getInstance()->setTweetDrafts(tweetDrafts);
    }
}

void SettingsManager::loadTweetTemplates()
{
    QVector<TweetTemplate> tweetTemplates;
    if (jsonSerializer->deserialize(tweetTemplates, settings->value(tweetTemplatesJsonPath).toString()))
    {
        int index = 0;
        while (index < tweetTemplates.count())
        {
            tweetTemplates[index].setId(++TweetTemplate::numTemplates);
            ++index;
        }

        DataStore::getInstance()->setTweetTemplates(tweetTemplates);
    }
}

bool SettingsManager::saveSettings()
{
    settings->setValue(apiKeyPath, Settings::apiKey);
    settings->setValue(apiSecretPath, Settings::apiSecret);
    settings->setValue(accessTokenPath, Settings::accessToken);
    settings->setValue(accessTokenSecretPath, Settings::accessTokenSecret);
    settings->setValue(encryptTweetDraftsPath, Settings::encryptDraftsOnDisk);
    settings->setValue(encryptTweetTemplatesPath, Settings::encryptTemplatesOnDisk);
    settings->setValue(persistWindowSizePath, Settings::persistWindowState);
    return true;
}

bool SettingsManager::saveWindowGeometry(const QByteArray &windowGeometry)
{
    settings->setValue(windowGeometryPath, windowGeometry);
    return true;
}

bool SettingsManager::saveTweetDrafts()
{
    bool success;
    QString tweetsDraftJson = jsonSerializer->tweetDraftsJson(success);

    if (success)
    {
        settings->setValue(tweetDraftsJsonPath, tweetsDraftJson);
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
        settings->setValue(tweetTemplatesJsonPath, tweetsTemplatesJson);
        return true;
    }
    else
    {
        return false;
    }
}
