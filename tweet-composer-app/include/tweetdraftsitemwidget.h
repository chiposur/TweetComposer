#ifndef TWEETDRAFTSITEMWIDGET_H
#define TWEETDRAFTSITEMWIDGET_H

#include <QLabel>

#include <tweetdraft.h>

class TweetDraftsItemWidget : public QLabel
{
    Q_OBJECT
public:
    explicit TweetDraftsItemWidget(const TweetDraft &tweetDraft, QWidget *parent = nullptr);

    void setName(const QString &name);

    QString getName() const { return name; }

    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void draftItemClicked(int draftId);

private:
    QString name;
    int draftId;
};

#endif // TWEETDRAFTSITEMWIDGET_H
