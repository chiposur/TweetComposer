#ifndef DATASTORE_H
#define DATASTORE_H

#include <QObject>
#include <QVector>

#include <tweetdraft.h>
#include <tweettemplate.h>

class DataStore : public QObject
{
    Q_OBJECT
public:
    explicit DataStore(QObject *parent = nullptr);

    static DataStore *getInstance();

    void setTweetDrafts(const QVector<TweetDraft> &tweetDrafts);
    void setTweetTemplates(const QVector<TweetTemplate> &tweetTemplates);

    QVector<TweetDraft> *getTweetDrafts() { return &tweetDrafts; }
    QVector<TweetTemplate> *getTweetTemplates() { return &tweetTemplates; }

    bool getTweetDraftById(TweetDraft &tweetDraft);
    bool getTweetTemplateById(TweetTemplate &tweetTemplate);

signals:

private:
    QVector<TweetDraft> tweetDrafts = QVector<TweetDraft>();
    QVector<TweetTemplate> tweetTemplates = QVector<TweetTemplate>();
};

#endif // DATASTORE_H
