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
    for (TweetDraft tweetDraft : tweetDrafts)
    {
        addTweetDraft(tweetDraft);
    }
}

void DataStore::setTweetTemplates(const QVector<TweetTemplate> &tweetTemplates)
{
    this->tweetTemplates.empty();
    this->tweetTemplates.resize(tweetTemplates.size());
    for (TweetTemplate tweetTemplate : tweetTemplates)
    {
        addTweetTemplate(tweetTemplate);
    }
}

bool DataStore::getTweetDraftById(int id, TweetDraft &tweetDraft)
{
    if (!draftIdToIndexMap.contains(id))
    {
        return false;
    }

    tweetDraft = tweetDrafts[draftIdToIndexMap[id]];

    return true;
}

bool DataStore::getTweetTemplateById(int id, TweetTemplate &tweetTemplate)
{
    if (!templateIdToIndexMap.contains(id))
    {
        return false;
    }

    tweetTemplate = tweetTemplates[templateIdToIndexMap[id]];

    return true;
}

void DataStore::addTweetDraft(const TweetDraft &tweetDraft)
{
    ++TweetDraft::numDrafts;
    tweetDrafts.append(tweetDraft);
}

void DataStore::addTweetTemplate(const TweetTemplate &tweetTemplate)
{
    ++TweetTemplate::numTemplates;
    tweetTemplates.append(tweetTemplate);
}

void DataStore::deleteTweetDraftById(int /*id*/)
{
    // TODO: swap draft to delete with last draft in vector, update former last draft in
    // map and then finally delete draft
}

void DataStore::deleteTweetTemplateById(int /*id*/)
{
    // TODO: swap template to delete with last template in vector, update former last template in
    // map and then finally delete template
}
