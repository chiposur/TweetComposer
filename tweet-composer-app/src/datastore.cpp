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
    draftIdToIndexMap.insert(tweetDraft.getId(), tweetDrafts.count() - 1);
}

void DataStore::addTweetTemplate(const TweetTemplate &tweetTemplate)
{
    ++TweetTemplate::numTemplates;
    tweetTemplates.append(tweetTemplate);
    templateIdToIndexMap.insert(tweetTemplate.getId(), tweetTemplates.count() - 1);
}

void DataStore::deleteTweetDraftById(int id)
{
    // Make sure draft is last vector element then delete
    if (draftIdToIndexMap[id] != tweetDrafts.count() - 1)
    {
        // Swap drafts
        TweetDraft draftToMove = tweetDrafts[tweetDrafts.count() - 1];
        TweetDraft draftToDelete = tweetDrafts[draftIdToIndexMap[id]];
        tweetDrafts[draftIdToIndexMap[id]] = draftToMove;
        tweetDrafts[tweetDrafts.count() - 1] = draftToDelete;

        // Update map
        draftIdToIndexMap[draftToMove.getId()] = draftIdToIndexMap[id];
        draftIdToIndexMap[id] = tweetDrafts.count() - 1;
    }

    int lastTweetId = tweetDrafts[tweetDrafts.count() - 1].getId();
    draftIdToIndexMap.remove(lastTweetId);
    tweetDrafts.removeLast();
}

void DataStore::deleteTweetTemplateById(int id)
{
    // Make sure template is last vector element then delete
    if (templateIdToIndexMap[id] != tweetTemplates.count() - 1)
    {
        // Swap templates
        TweetTemplate templateToMove = tweetTemplates[tweetTemplates.count() - 1];
        TweetTemplate templateToDelete = tweetTemplates[templateIdToIndexMap[id]];
        tweetTemplates[templateIdToIndexMap[id]] = templateToMove;
        tweetTemplates[tweetTemplates.count() - 1] = templateToDelete;

        // Update map
        templateIdToIndexMap[templateToMove.getId()] = templateIdToIndexMap[id];
        templateIdToIndexMap[id] = tweetTemplates.count() - 1;
    }

    int lastTweetId = tweetTemplates[tweetTemplates.count() - 1].getId();
    templateIdToIndexMap.remove(lastTweetId);
    tweetTemplates.removeLast();
}
