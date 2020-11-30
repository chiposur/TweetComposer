#ifndef DATASTORE_H
#define DATASTORE_H

#include <QMap>
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

    bool getTweetDraftById(int id, TweetDraft &tweetDraft);
    bool getTweetTemplateById(int id, TweetTemplate &tweetTemplate);

    void addTweetDraft(const TweetDraft &tweetDraft);
    void addTweetTemplate(const TweetTemplate &tweetTemplate);

    void editTweetDraftById(int id, const TweetDraft &tweetDraft);
    void editTweetTemplateById(int id, const TweetTemplate &tweetTemplate);

    void deleteTweetDraftById(int id);
    void deleteTweetTemplateById(int id);

    int getDraftIdIndex(int id) { return draftIdToIndexMap.contains(id) ? draftIdToIndexMap[id] : -1; };
    int getTemplateIdIndex(int id) { return templateIdToIndexMap.contains(id) ? templateIdToIndexMap[id] : -1; };

signals:
    void tweetDraftAdded(const TweetDraft &tweetDraft);
    void tweetDraftEdited(const TweetDraft &tweetDraft);
    void tweetDraftDeleted(int draftId);
    void tweetTemplateAdded(const TweetTemplate &tweetTemplate);
    void tweetTemplateEdited(const TweetTemplate &tweetTemplate);
    void tweetTemplateDeleted(int templateId);

private:
    QVector<TweetDraft> tweetDrafts = QVector<TweetDraft>();
    QVector<TweetTemplate> tweetTemplates = QVector<TweetTemplate>();

    QMap<int, int> draftIdToIndexMap = QMap<int, int>();
    QMap<int, int> templateIdToIndexMap = QMap<int, int>();
};

#endif // DATASTORE_H
