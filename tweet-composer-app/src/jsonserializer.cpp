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

JsonSerializer::JsonSerializer(QString json)
{
    jsonDocument = new QJsonDocument(QJsonDocument::fromJson(json.toUtf8()));
}

JsonSerializer::~JsonSerializer()
{
    delete jsonDocument;
}

JsonSerializer *JsonSerializer::getInstance()
{
    static JsonSerializer jsonSerializer("{ \"tweetDrafts\": [], \"tweetTemplates\": [] }");
    return &jsonSerializer;
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

    QJsonDocument doc(jsonArray);
    return doc.toJson();
}

QString JsonSerializer::serialize(const QVector<TweetTemplate> &tweetTemplates)
{
    QJsonArray jsonArray;
    for (TweetTemplate tweetTemplate : tweetTemplates)
    {
      jsonArray.push_back(createQJsonObject(tweetTemplate));
    }

    QJsonDocument doc(jsonArray);
    return doc.toJson();
}

bool JsonSerializer::deserialize(QVector<TweetDraft> &tweetDrafts, const QString &json)
{
    QJsonDocument doc(QJsonDocument::fromJson(json.toUtf8()));

    if (!doc.isArray())
    {
        return false;
    }

    for (QJsonValue value : doc.array())
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

    if (!doc.isArray())
    {
        return false;
    }

    for (QJsonValue value : doc.array())
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

void JsonSerializer::onTweetDraftAdded(const TweetDraft &tweetDraft)
{
    QJsonArray draftsArray = (*jsonDocument)["tweetDrafts"].toArray();
    draftsArray.append(QJsonValue(createQJsonObject(tweetDraft)));
    jsonDocument->object()["tweetDrafts"] = draftsArray;
}

void JsonSerializer::onTweetDraftEdited(const TweetDraft &tweetDraft)
{
    QJsonArray draftsArray = (*jsonDocument)["tweetDrafts"].toArray();
    for (QJsonValue value : draftsArray)
    {
        if (value.toObject()["id"] == tweetDraft.getId())
        {
            value = QJsonValue(createQJsonObject(tweetDraft));
        }
    }

    jsonDocument->object()["tweetDrafts"] = draftsArray;
}

void JsonSerializer::onTweetDraftDeleted(int draftId)
{
    QJsonArray draftsArray = (*jsonDocument)["tweetDrafts"].toArray();
    int index = 0;
    for (QJsonValue value : draftsArray)
    {
        if (value.toObject()["id"] == draftId)
        {
            break;
        }

        ++index;
    }

    draftsArray.removeAt(index);
    jsonDocument->object()["tweetDrafts"] = draftsArray;
}

void JsonSerializer::onTweetTemplateAdded(const TweetTemplate &tweetTemplate)
{
    QJsonArray templatesArray = (*jsonDocument)["tweetTemplates"].toArray();
    templatesArray.append(QJsonValue(createQJsonObject(tweetTemplate)));
    jsonDocument->object()["tweetTemplates"] = templatesArray;
}

void JsonSerializer::onTweetTemplateEdited(const TweetTemplate &tweetTemplate)
{
    QJsonArray draftsArray = (*jsonDocument)["tweetTemplates"].toArray();
    for (QJsonValue value : draftsArray)
    {
        if (value.toObject()["id"] == tweetTemplate.getId())
        {
            value = QJsonValue(createQJsonObject(tweetTemplate));
        }
    }

    jsonDocument->object()["tweetTemplates"] = draftsArray;
}

void JsonSerializer::onTweetTemplateDeleted(int templateId)
{
    QJsonArray draftsArray = (*jsonDocument)["tweetTemplates"].toArray();
    int index = 0;
    for (QJsonValue value : draftsArray)
    {
        if (value.toObject()["id"] == templateId)
        {
            break;
        }

        ++index;
    }

    draftsArray.removeAt(index);
    jsonDocument->object()["tweetTemplates"] = draftsArray;
}

QString JsonSerializer::json()
{
    return jsonDocument->toJson();
}

QString JsonSerializer::tweetDraftsJson(bool &success)
{
    QString json;

    if (!jsonDocument->isObject()
        || !jsonDocument->object().contains("tweetDrafts")
        || !jsonDocument->object()["tweetDrafts"].isArray())
    {
        success = false;
    }
    else
    {
        QJsonArray tweetTemplatesJson = jsonDocument->object()["tweetDrafts"].toArray();
        QJsonDocument doc(tweetTemplatesJson);
        json = doc.toJson();
        success = true;
    }

    return json;
}

QString JsonSerializer::tweetTemplatesJson(bool &success)
{
    QString json;

    if (!jsonDocument->isObject()
        || !jsonDocument->object().contains("tweetTemplates")
        || !jsonDocument->object()["tweetTemplates"].isArray())
    {
        success = false;
    }
    else
    {
        QJsonArray tweetTemplatesJson = jsonDocument->object()["tweetTemplates"].toArray();
        QJsonDocument doc(tweetTemplatesJson);
        json = doc.toJson();
        success = true;
    }

    return json;
}
