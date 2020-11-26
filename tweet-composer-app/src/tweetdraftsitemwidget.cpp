#include "tweetdraftsitemwidget.h"

#include <QVBoxLayout>

TweetDraftsItemWidget::TweetDraftsItemWidget(const TweetDraft &tweetDraft, QWidget *parent) : QWidget(parent)
{
    // TODO: style like tweet drafts
    draftId = tweetDraft.getId();
    draftTextLabel = new QLabel(tweetDraft.getText());

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addWidget(draftTextLabel);
}
