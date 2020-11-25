#include "settingsmanager.h"
#include "datastore.h"

SettingsManager::SettingsManager(QObject *parent) : QObject(parent)
{

}

SettingsManager *SettingsManager::getInstance()
{
    static SettingsManager settingsMgr;
    return &settingsMgr;
}

void SettingsManager::loadTweetDrafts()
{
    QVector<TweetDraft> tweetDrafts = QVector<TweetDraft>();

    // TODO: load drafts from disk

    DataStore::getInstance()->setTweetDrafts(tweetDrafts);
}

void SettingsManager::loadTweetTemplates()
{
    QVector<TweetTemplate> tweetTemplates;

    // TODO: load templates from disk

    DataStore::getInstance()->setTweetTemplates(tweetTemplates);
}

bool SettingsManager::saveSettings()
{
    // TODO: implement saving of settings
    return true;
}

bool SettingsManager::saveTweetDrafts()
{
    // TODO: implement saving and serializing drafts to QSettings
    return true;
}

bool SettingsManager::saveTweetTemplates()
{
    // TODO: implement saving and serializing templates to QSettings
    return true;
}

QString SettingsManager::serializeSettingsToJson()
{
    QString jsonSettings;

    // TODO: serialize QSettings to Json for exporting and downloading

    return jsonSettings;
}
