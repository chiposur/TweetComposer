#ifndef TWEETTEMPLATESITEMWIDGET_H
#define TWEETTEMPLATESITEMWIDGET_H

#include <QLabel>

#include <tweettemplate.h>

class TweetTemplatesItemWidget : public QLabel
{
    Q_OBJECT

public:
    explicit TweetTemplatesItemWidget(const TweetTemplate &tweetTemplate, QWidget *parent = nullptr);

    void setName(const QString &name);

    QString getName() const { return name; }

    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void templateItemClicked(int templateId);

private:
    QString name;
    int templateId;
};

#endif // TWEETTEMPLATESITEMWIDGET_H
