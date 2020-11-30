#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QMap>
#include <QObject>
#include <QString>
#include <QVector>

#include <tweetdraft.h>
#include <tweettemplate.h>

class JsonSerializer : public QObject
{
    Q_OBJECT

public:
    JsonSerializer(QString json);

    ~JsonSerializer();

    static JsonSerializer *getInstance();

    QString json();
    QString tweetDraftsJson(bool &success);
    QString tweetTemplatesJson(bool &success);

    static QString serialize(const TweetDraft &tweetDraft);
    static QString serialize(const TweetTemplate &tweetTemplate);
    static QString serialize(const QVector<TweetDraft> &tweetDrafts);
    static QString serialize(const QVector<TweetTemplate> &tweetTemplates);

    static bool deserialize(QVector<TweetDraft> &tweetDrafts, const QString &json);
    static bool deserialize(QVector<TweetTemplate> &tweetTemplates, const QString &json);
    static bool deserialize(TweetDraft &tweetDraft, const QString &json);
    static bool deserialize(TweetTemplate &tweetTemplate, const QString &json);

public slots:
    void onTweetDraftAdded(const TweetDraft &tweetDraft);
    void onTweetDraftEdited(const TweetDraft &tweetDraft);
    void onTweetDraftDeleted(int draftId);
    void onTweetTemplateAdded(const TweetTemplate &tweetTemplate);
    void onTweetTemplateEdited(const TweetTemplate &tweetTemplate);
    void onTweetTemplateDeleted(int templateId);

private:
    JsonSerializer();

    QJsonDocument *jsonDocument;
};

#endif
