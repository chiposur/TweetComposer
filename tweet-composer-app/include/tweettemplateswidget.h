#ifndef TWEETTEMPLATESWIDGET_H
#define TWEETTEMPLATESWIDGET_H

#include <QObject>
#include <QWidget>

#include "tweettemplate.h"

class TweetTemplatesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TweetTemplatesWidget(QWidget *parent = nullptr);

signals:
    void backRequested();

public slots:
    void onTweetTemplateAdded(const TweetTemplate &tweetTemplate);
    void onBackPressed();
};

#endif // TWEETTEMPLATESWIDGET_H
