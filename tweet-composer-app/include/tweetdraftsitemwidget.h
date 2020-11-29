#ifndef TWEETDRAFTSITEMWIDGET_H
#define TWEETDRAFTSITEMWIDGET_H

#include <QLabel>
#include <QObject>
#include <QWidget>

#include <tweetdraft.h>

class TweetDraftsItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TweetDraftsItemWidget(const TweetDraft &tweetDraft, QWidget *parent = nullptr);

    void updateText(const QString &text) { draftTextLabel->setText(text); }

    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void draftItemClicked(int draftId);

private:
    QLabel *draftTextLabel;

    int draftId;
};

#endif // TWEETDRAFTSITEMWIDGET_H
