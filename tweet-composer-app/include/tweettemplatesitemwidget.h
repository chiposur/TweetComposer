#ifndef TWEETTEMPLATESITEMWIDGET_H
#define TWEETTEMPLATESITEMWIDGET_H

#include <QLabel>

#include <tweettemplate.h>

class TweetTemplatesItemWidget : public QLabel
{
    Q_OBJECT

public:
    explicit TweetTemplatesItemWidget(const TweetTemplate &tweetTemplate, QWidget *parent = nullptr);

    void updateText(const QString &text) { setText(text); }

    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void templateItemClicked(int templateId);

private:
    int templateId;
};

#endif // TWEETTEMPLATESITEMWIDGET_H
