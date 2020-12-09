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
        {"text", tweetDraft.getText()},
        {"name", tweetDraft.getName()}
    };

    return draftObject;
}

QJsonObject createQJsonObject(const TweetTemplate &tweetTemplate)
{
    QJsonObject templateObject
    {
        {"id", tweetTemplate.getId()},
        {"text", tweetTemplate.getText()},
        {"name", tweetTemplate.getName()}
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

        if (jsonObject.contains("name"))
        {
            QString name = jsonObject["name"].toString();
            if (name.length() > 200)
            {
                name = name.replace(200, name.length() - 200, "");
            }
            tweetDraft.setName(name);
        }

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

        if (jsonObject.contains("name"))
        {
            QString name = jsonObject["name"].toString();
            if (name.length() > 200)
            {
                name = name.replace(200, name.length() - 200, "");
            }
            tweetTemplate.setName(name);
        }

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
    QJsonObject root = jsonDocument->object();
    QJsonArray draftsArray = root["tweetDrafts"].toArray();
    draftsArray.append(QJsonValue(createQJsonObject(tweetDraft)));
    root["tweetDrafts"] = draftsArray;
    jsonDocument->setObject(root);
}

void JsonSerializer::onTweetDraftEdited(const TweetDraft &tweetDraft)
{
    QJsonObject root = jsonDocument->object();
    QJsonArray draftsArray = root["tweetDrafts"].toArray();
    for (QJsonValue value : draftsArray)
    {
        if (value.toObject()["id"] == tweetDraft.getId())
        {
            value = QJsonValue(createQJsonObject(tweetDraft));
        }
    }

    root["tweetDrafts"] = draftsArray;
    jsonDocument->setObject(root);
}

void JsonSerializer::onTweetDraftDeleted(int draftId)
{
    QJsonObject root = jsonDocument->object();
    QJsonArray draftsArray = root["tweetDrafts"].toArray();
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
    root["tweetDrafts"] = draftsArray;
    jsonDocument->setObject(root);
}

void JsonSerializer::onTweetTemplateAdded(const TweetTemplate &tweetTemplate)
{
    QJsonObject root = jsonDocument->object();
    QJsonArray draftsArray = root["tweetTemplates"].toArray();
    draftsArray.append(QJsonValue(createQJsonObject(tweetTemplate)));
    root["tweetTemplates"] = draftsArray;
    jsonDocument->setObject(root);
}

void JsonSerializer::onTweetTemplateEdited(const TweetTemplate &tweetTemplate)
{
    QJsonObject root = jsonDocument->object();
    QJsonArray draftsArray = root["tweetTemplates"].toArray();
    for (QJsonValue value : draftsArray)
    {
        if (value.toObject()["id"] == tweetTemplate.getId())
        {
            value = QJsonValue(createQJsonObject(tweetTemplate));
        }
    }

    root["tweetTemplates"] = draftsArray;
    jsonDocument->setObject(root);
}

void JsonSerializer::onTweetTemplateDeleted(int templateId)
{
    QJsonObject root = jsonDocument->object();
    QJsonArray draftsArray = root["tweetTemplates"].toArray();
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
    root["tweetTemplates"] = draftsArray;
    jsonDocument->setObject(root);
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
        QJsonArray tweetDraftsJson = jsonDocument->object()["tweetDrafts"].toArray();
        QJsonDocument doc(tweetDraftsJson);
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
