#ifndef TWEETTEMPLATESITEMWIDGET_H
#define TWEETTEMPLATESITEMWIDGET_H

#include <QLabel>
#include <QObject>
#include <QWidget>

#include <tweettemplate.h>

class TweetTemplatesItemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TweetTemplatesItemWidget(const TweetTemplate &tweetTemplate, QWidget *parent = nullptr);

    void updateText(const QString &text) { templateTextLabel->setText(text); }

    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void templateItemClicked(int templateId);

private:
    QLabel *templateTextLabel;

    int templateId;
};

#endif // TWEETTEMPLATESITEMWIDGET_H
