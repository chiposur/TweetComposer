#ifndef TWEETDRAFTSITEMWIDGET_H
#define TWEETDRAFTSITEMWIDGET_H

#include <QLabel>

#include <tweetdraft.h>

class TweetDraftsItemWidget : public QLabel
{
    Q_OBJECT
public:
    explicit TweetDraftsItemWidget(const TweetDraft &tweetDraft, QWidget *parent = nullptr);

    void updateText(const QString &text);
    void updateName(const QString &name);

    QString getPlainText() const { return plainText; }
    QString getName() const { return name; }

    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void draftItemClicked(int draftId);

private:
    QString plainText;
    QString name;
    int draftId;
};

#endif // TWEETDRAFTSITEMWIDGET_H
