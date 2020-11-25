#include "datastore.h"

DataStore::DataStore(QObject *parent) : QObject(parent)
{

}

DataStore *DataStore::getInstance()
{
    static DataStore dataStore;
    return &dataStore;
}

void DataStore::setTweetDrafts(const QVector<TweetDraft> &tweetDrafts)
{
    this->tweetDrafts.empty();
    this->tweetDrafts.resize(tweetDrafts.size());
    this->tweetDrafts.append(tweetDrafts);
}

void DataStore::setTweetTemplates(const QVector<TweetTemplate> &tweetTemplates)
{
    this->tweetTemplates.empty();
    this->tweetTemplates.resize(tweetTemplates.size());
    this->tweetTemplates.append(tweetTemplates);
}

bool DataStore::getTweetDraftById(TweetDraft &/*tweetDraft*/)
{
    // TODO: implement
    return true;
}

bool DataStore::getTweetTemplateById(TweetTemplate &/*tweetTemplate*/)
{
    // TODO: implement
    return true;
}
