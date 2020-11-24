#include "settingsmanager.h"

SettingsManager::SettingsManager(QObject *parent) : QObject(parent)
{
    tweetDrafts = new QList<TweetDraft *>;
    tweetTemplates = new QList<TweetTemplate *>;
}

SettingsManager *SettingsManager::getInstance()
{
    static SettingsManager settingsMgr;
    return &settingsMgr;
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
