#ifndef TWEETDRAFTSITEMWIDGET_H
#define TWEETDRAFTSITEMWIDGET_H

#include <QLabel>

#include <tweetdraft.h>

class TweetDraftsItemWidget : public QLabel
{
    Q_OBJECT
public:
    explicit TweetDraftsItemWidget(const TweetDraft &tweetDraft, QWidget *parent = nullptr);

    void updateText(const QString &text) { setText(text); }

    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void draftItemClicked(int draftId);

private:
    int draftId;
};

#endif // TWEETDRAFTSITEMWIDGET_H
