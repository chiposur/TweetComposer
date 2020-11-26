#include "tweettemplateswidget.h"
#include "customcontrols.h"

#include <QVBoxLayout>

TweetTemplatesWidget::TweetTemplatesWidget(QWidget *parent) : QWidget(parent)
{
    // TODO: create a scrolling list of tweet templates, similar in appearance to Twitter app drafts
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    StandardButton *backBtn = new StandardButton("Back");
    mainLayout->addWidget(backBtn);
}

void TweetTemplatesWidget::onTweetTemplateAdded(const TweetTemplate &/*tweetTemplate*/)
{
    // TODO: add a new tweet template item to widget
}

void TweetTemplatesWidget::onBackPressed()
{
    emit backRequested();
}

void TweetTemplatesWidget::onTweetTemplateEdited(const TweetTemplate &/*tweetTemplate*/)
{
    // TODO: implement
}
