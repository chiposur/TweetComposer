#ifndef TWEETDRAFTSWIDGET_H
#define TWEETDRAFTSWIDGET_H

#include <QMap>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

#include "customcontrols.h"
#include "tweetdraft.h"
#include "toast.h"
#include "tweetdraftsitemwidget.h"

class TweetDraftsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TweetDraftsWidget(QWidget *parent = nullptr);

signals:
    void backRequested();
    void toastRequested(const Toast &toast);
    void editDraftRequested(int draftId);

public slots:
    void onTweetDraftAdded(const TweetDraft &tweetDraft);
    void onTweetDraftEdited(const TweetDraft &tweetDraft);
    void onTweetDraftDeleted(int draftId);
    void onBackPressed();
    void onTweetDraftClicked(int draftId);
    void onSearchTextChanged(const QString &text);

private:
    QMap<int, TweetDraftsItemWidget *> idToItemMap;
    DraftsTemplatesContainer *draftsContainer;
};

#endif // TWEETDRAFTSWIDGET_H
