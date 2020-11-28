#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QString>
#include <QVector>

#include <tweetdraft.h>
#include <tweettemplate.h>

class JsonSerializer
{
public:
    static QString serialize(const TweetDraft &tweetDraft);
    static QString serialize(const TweetTemplate &tweetTemplate);
    static QString serialize(const QVector<TweetDraft> &tweetDrafts);
    static QString serialize(const QVector<TweetTemplate> &tweetTemplates);

    static bool deserialize(QVector<TweetDraft> &tweetDrafts, const QString &json);
    static bool deserialize(QVector<TweetTemplate> &tweetTemplates, const QString &json);
    static bool deserialize(TweetDraft &tweetDraft, const QString &json);
    static bool deserialize(TweetTemplate &tweetTemplate, const QString &json);
};

#endif
