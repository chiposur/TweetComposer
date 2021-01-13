#include "datastore.h"

int DataStore::numAssignedDraftIds = 0;
int DataStore::numAssignedTemplateIds = 0;

DataStore::DataStore(QObject *parent) : QObject(parent)
{
    tweetDrafts = new QVector<TweetDraft>();
    tweetTemplates = new QVector<TweetTemplate>();
    draftIdToIndexMap = new QMap<int, int>();
    templateIdToIndexMap = new QMap<int, int>();
}

DataStore::~DataStore()
{
    delete tweetDrafts;
    delete tweetTemplates;
    delete draftIdToIndexMap;
    delete templateIdToIndexMap;
}

DataStore *DataStore::getInstance()
{
    static DataStore dataStore;
    return &dataStore;
}

void DataStore::setTweetDrafts(const QVector<TweetDraft> &tweetDrafts)
{
    this->tweetDrafts->empty();
    this->tweetDrafts->resize(tweetDrafts.size());
    for (TweetDraft tweetDraft : tweetDrafts)
    {
        addTweetDraft(tweetDraft);
    }
}

void DataStore::setTweetTemplates(const QVector<TweetTemplate> &tweetTemplates)
{
    this->tweetTemplates->empty();
    this->tweetTemplates->resize(tweetTemplates.size());
    for (TweetTemplate tweetTemplate : tweetTemplates)
    {
        addTweetTemplate(tweetTemplate);
    }
}

bool DataStore::getTweetDraftById(int id, TweetDraft &tweetDraft)
{
    if (!draftIdToIndexMap->contains(id))
    {
        return false;
    }

    tweetDraft = (*tweetDrafts)[getDraftIdIndex(id)];

    return true;
}

bool DataStore::getTweetTemplateById(int id, TweetTemplate &tweetTemplate)
{
    if (!templateIdToIndexMap->contains(id))
    {
        return false;
    }

    tweetTemplate = (*tweetTemplates)[getTemplateIdIndex(id)];

    return true;
}

void DataStore::addTweetDraft(const TweetDraft &tweetDraft)
{
    assignDraftId();
    tweetDrafts->append(tweetDraft);
    draftIdToIndexMap->insert(tweetDraft.getId(), tweetDrafts->count() - 1);
    emit tweetDraftAdded(tweetDraft);
}

void DataStore::addTweetTemplate(const TweetTemplate &tweetTemplate)
{
    assignTemplateId();
    tweetTemplates->append(tweetTemplate);
    templateIdToIndexMap->insert(tweetTemplate.getId(), tweetTemplates->count() - 1);
    emit tweetTemplateAdded(tweetTemplate);
}

void DataStore::editTweetDraftById(int id, const TweetDraft &tweetDraft)
{
    (*tweetDrafts)[getDraftIdIndex(id)] = tweetDraft;
    emit tweetDraftEdited(tweetDraft);
}

void DataStore::editTweetTemplateById(int id, const TweetTemplate &tweetTemplate)
{
    (*tweetTemplates)[getTemplateIdIndex(id)] = tweetTemplate;
    emit tweetTemplateEdited(tweetTemplate);
}

void DataStore::deleteAllTweetDrafts()
{
    for (int id : draftIdToIndexMap->keys())
    {
        emit tweetDraftDeleted(id);
    }

    tweetDrafts->empty();
    draftIdToIndexMap->clear();
}

void DataStore::deleteAllTweetTemplates()
{
    for (int id : templateIdToIndexMap->keys())
    {
        emit tweetTemplateDeleted(id);
    }

    tweetTemplates->empty();
    templateIdToIndexMap->clear();
}

void DataStore::deleteTweetDraftById(int id)
{
    // Make sure draft is last vector element then delete
    if (getDraftIdIndex(id) != tweetDrafts->count() - 1)
    {
        // Swap drafts
        TweetDraft draftToMove = tweetDrafts->last();
        TweetDraft draftToDelete = (*tweetDrafts)[getDraftIdIndex(id)];
        (*tweetDrafts)[getDraftIdIndex(id)] = draftToMove;
        tweetDrafts->last() = draftToDelete;

        // Update map
        (*draftIdToIndexMap)[draftToMove.getId()] = getDraftIdIndex(id);
        (*draftIdToIndexMap)[id] = tweetDrafts->count() - 1;
    }

    int lastTweetId = tweetDrafts->last().getId();
    draftIdToIndexMap->remove(lastTweetId);
    tweetDrafts->removeLast();
    emit tweetDraftDeleted(lastTweetId);
}

void DataStore::deleteTweetTemplateById(int id)
{
    // Make sure template is last vector element then delete
    if (getTemplateIdIndex(id) != tweetTemplates->count() - 1)
    {
        // Swap templates
        TweetTemplate templateToMove = tweetTemplates->last();
        TweetTemplate templateToDelete = (*tweetTemplates)[getTemplateIdIndex(id)];
        (*tweetTemplates)[getTemplateIdIndex(id)] = templateToMove;
        tweetTemplates->last() = templateToDelete;

        // Update map
        (*templateIdToIndexMap)[templateToMove.getId()] = getTemplateIdIndex(id);
        (*templateIdToIndexMap)[id] = tweetTemplates->count() - 1;
    }

    int lastTweetId = tweetTemplates->last().getId();
    templateIdToIndexMap->remove(lastTweetId);
    tweetTemplates->removeLast();
    emit tweetTemplateDeleted(lastTweetId);
}
