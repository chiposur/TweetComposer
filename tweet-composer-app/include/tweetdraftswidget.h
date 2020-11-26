#ifndef TWEETDRAFTSWIDGET_H
#define TWEETDRAFTSWIDGET_H

#include <QObject>
#include <QWidget>

#include "tweetdraft.h"
#include "toast.h"

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
    void onBackPressed();
};

#endif // TWEETDRAFTSWIDGET_H
