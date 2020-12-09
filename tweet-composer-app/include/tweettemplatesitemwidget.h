#ifndef TWEETTEMPLATESITEMWIDGET_H
#define TWEETTEMPLATESITEMWIDGET_H

#include <QLabel>

#include <tweettemplate.h>

class TweetTemplatesItemWidget : public QLabel
{
    Q_OBJECT

public:
    explicit TweetTemplatesItemWidget(const TweetTemplate &tweetTemplate, QWidget *parent = nullptr);

    void updateText(const QString &text);
    void updateName(const QString &name);

    QString getPlainText() const { return plainText; }
    QString getName() const { return name; }

    void mouseReleaseEvent(QMouseEvent *event);

signals:
    void templateItemClicked(int templateId);

private:
    QString plainText;
    QString name;
    int templateId;
};

#endif // TWEETTEMPLATESITEMWIDGET_H
