#ifndef TWEETTEMPLATESWIDGET_H
#define TWEETTEMPLATESWIDGET_H

#include <QMap>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>

#include "customcontrols.h"
#include "tweettemplate.h"
#include "toast.h"
#include "tweettemplatesitemwidget.h"

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
    void onTweetTemplateEdited(const TweetTemplate &tweetTemplate);
    void onTweetTemplateDeleted(int templateId);
    void onBackPressed();
    void onTweetTemplateClicked(int templateId);
    void onSearchTextChanged(const QString &text);

private:
    QMap<int, TweetTemplatesItemWidget *> idToItemMap;
    DraftsTemplatesContainer *templatesContainer;
};

#endif // TWEETTEMPLATESWIDGET_H
