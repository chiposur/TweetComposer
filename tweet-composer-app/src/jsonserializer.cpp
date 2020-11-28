#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include "jsonserializer.h"

QJsonObject createQJsonObject(const TweetDraft &tweetDraft)
{
    QJsonObject draftObject
    {
        {"id", tweetDraft.getId()},
        {"text", tweetDraft.getText()}
    };

    return draftObject;
}

QJsonObject createQJsonObject(const TweetTemplate &tweetTemplate)
{
    QJsonObject templateObject
    {
        {"id", tweetTemplate.getId()},
        {"text", tweetTemplate.getText()}
    };

    return templateObject;
}

bool deserializeQJsonObject(const QJsonObject &jsonObject, TweetDraft &tweetDraft)
{
    bool hasId = jsonObject.contains("id") && jsonObject["id"].isDouble();
    bool hasText = jsonObject.contains("text") && jsonObject["text"].isString();
    if (hasId && hasText)
    {
   tweetDraft.setText(jsonObject["text"].toString());
        return true;
    }
    else
    {
        return false;
    } 
}

bool deserializeQJsonObject(const QJsonObject &jsonObject, TweetTemplate &tweetTemplate)
{
    bool hasId = jsonObject.contains("id") && jsonObject["id"].isDouble();
    bool hasText = jsonObject.contains("text") && jsonObject["text"].isString();
    if (hasId && hasText)
    {
   tweetTemplate.setText(jsonObject["text"].toString());
        return true;
    }
    else
    {
        return false;
    } 
	}

QString JsonSerializer::serialize(const TweetDraft &tweetDraft)
{
    QJsonDocument doc(createQJsonObject(tweetDraft));
    return doc.toJson();
}

QString JsonSerializer::serialize(const TweetTemplate &tweetTemplate)
{
    QJsonDocument doc(createQJsonObject(tweetTemplate));
    return doc.toJson();
}

QString JsonSerializer::serialize(const QVector<TweetDraft> &tweetDrafts)
{
    QJsonArray jsonArray;
    for (TweetDraft tweetDraft : tweetDrafts)
    {
      jsonArray.push_back(createQJsonObject(tweetDraft));
    }

    QJsonObject draftsObject;
    draftsObject["tweetDrafts"] = jsonArray;
    QJsonDocument doc(draftsObject);
    return doc.toJson();
}

QString JsonSerializer::serialize(const QVector<TweetTemplate> &tweetTemplates)
{
    QJsonArray jsonArray;
    for (TweetTemplate tweetTemplate : tweetTemplates)
    {
      jsonArray.push_back(createQJsonObject(tweetTemplate));
    }

    QJsonObject draftsObject;
    draftsObject["tweetTemplates"] = jsonArray;
    QJsonDocument doc(draftsObject);
    return doc.toJson();
}

bool JsonSerializer::deserialize(QVector<TweetDraft> &tweetDrafts, const QString &json)
{
    QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));

    if (!doc.isObject() || doc.object().contains("tweetDrafts") || !doc["tweetDrafts"].isArray())
    {
        return false;
    }

    for (QJsonValue value : doc["tweetDrafts"].toArray())
    {
        if (!value.isObject())
        {
            continue;
        }

        TweetDraft deserializedDraft;
        if (deserializeQJsonObject(value.toObject(), deserializedDraft))
        {
            tweetDrafts.append(deserializedDraft);
        }
    }

    return true;
}

bool JsonSerializer::deserialize(QVector<TweetTemplate> &tweetTemplates, const QString &json)
{
    QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));

    if (!doc.isObject() || !doc.object().contains("tweetTemplates") || !doc["tweetTemplates"].isArray())
    {
        return false;
    }

    for (QJsonValue value : doc["tweetTemplates"].toArray())
    {
        if (!value.isObject())
        {
            continue;
        }

        TweetTemplate deserializedTemplate;
        if (deserializeQJsonObject(value.toObject(), deserializedTemplate))
        {
            tweetTemplates.append(deserializedTemplate);
        }
    }

    return true;
}

bool JsonSerializer::deserialize(TweetDraft &tweetDraft, const QString &json)
{
    QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));

    if (!doc.isObject())
    {
        return false;
    }

    return deserializeQJsonObject(doc.object(), tweetDraft);
}

bool JsonSerializer::deserialize(TweetTemplate &tweetTemplate, const QString &json)
{
    QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));

    if (!doc.isObject())
    {
        return false;
    }

    return deserializeQJsonObject(doc.object(), tweetTemplate);
}
