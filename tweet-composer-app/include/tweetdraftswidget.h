#ifndef TWEETDRAFTSWIDGET_H
#define TWEETDRAFTSWIDGET_H

#include <QMap>
#include <QWidget>

#include "scrollablecontainer.h"
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

private slots:
    void onSearchTextChanged(const QString &text);

private:
    QMap<int, TweetDraftsItemWidget *> idToItemMap;
    ScrollableContainer *draftsContainer;
};

#endif // TWEETDRAFTSWIDGET_H
