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

    QList<TweetDraft *> *getTweetDrafts() { return tweetDrafts; };
    QList<TweetTemplate *> *getTweetTemplates() { return tweetTemplates; };

    bool saveTweetDrafts();
    bool saveTweetTemplates();

    QString serializeSettingsToJson();

signals:

private:
    QList<TweetDraft *> *tweetDrafts;
    QList<TweetTemplate *> *tweetTemplates;
};

#endif // SETTINGSMANAGER_H
