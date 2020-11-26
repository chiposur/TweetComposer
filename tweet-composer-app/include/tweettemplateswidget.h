#ifndef TWEETTEMPLATESWIDGET_H
#define TWEETTEMPLATESWIDGET_H

#include <QObject>
#include <QWidget>

#include "tweettemplate.h"
#include "toast.h"

class TweetTemplatesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TweetTemplatesWidget(QWidget *parent = nullptr);

signals:
    void backRequested();
    void toastRequested(const Toast &toast);
    void editTemplateRequested(int templateId);

public slots:
    void onTweetTemplateAdded(const TweetTemplate &tweetTemplate);
    void onBackPressed();
};

#endif // TWEETTEMPLATESWIDGET_H
