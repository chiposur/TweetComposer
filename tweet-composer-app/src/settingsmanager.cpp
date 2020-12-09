#include "settingsmanager.h"
#include "datastore.h"
#include "jsonserializer.h"
#include "settings.h"

#include <QString>

const QString userSettingsPath("settings");
const QString encryptTweetDraftsPath("settings/encryptTweetDrafts");
const QString encryptTweetTemplatesPath("settings/encryptTweetTemplates");
const QString persistWindowSizePath("settings/persistWindowSize");
const QString storagePath("storage");
const QString windowSizeWidthPath("storage/windowSizeWidth");
const QString windowSizeHeightPath("storage/windowSizeHeight");
const QString tweetDraftsJsonPath("storage/tweetDraftsJson");
const QString tweetTemplatesJsonPath("storage/tweetTemplatesJson");

SettingsManager::SettingsManager(QObject *parent) : QObject(parent)
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
    Settings::encryptDraftsOnDisk = settings->value(encryptTweetDraftsPath, false).toBool();
    Settings::encryptTemplatesOnDisk = settings->value(encryptTweetTemplatesPath, false).toBool();
    Settings::persistWindowSize = settings->value(persistWindowSizePath, false).toBool();
}

void SettingsManager::loadWindowSize(QSize &windowSize)
{
    windowSize.setWidth(settings->value(windowSizeWidthPath, 0).toInt());
    windowSize.setHeight(settings->value(windowSizeHeightPath, 0).toInt());
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
    settings->setValue(encryptTweetDraftsPath, Settings::encryptDraftsOnDisk);
    settings->setValue(encryptTweetTemplatesPath, Settings::encryptTemplatesOnDisk);
    settings->setValue(persistWindowSizePath, Settings::persistWindowSize);
    return true;
}

bool SettingsManager::saveWindowSize(const QSize &size)
{
    settings->setValue(windowSizeWidthPath, size.width());
    settings->setValue(windowSizeHeightPath, size.height());
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
