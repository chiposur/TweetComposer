#include "tweetdraftswidget.h"
#include "customcontrols.h"

#include <QVBoxLayout>

TweetDraftsWidget::TweetDraftsWidget(QWidget *parent) : QWidget(parent)
{
    // TODO: create a scrolling list of tweet drafts, similar in appearance to Twitter app drafts
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    StandardButton *backBtn = new StandardButton("Back");
    mainLayout->addWidget(backBtn);
}

void TweetDraftsWidget::onTweetDraftAdded(const TweetDraft &/*tweetDraft*/)
{
    // TODO: add a new tweet draft item to widget
}

void TweetDraftsWidget::onBackPressed()
{
    emit backRequested();
}
