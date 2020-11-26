#include "tweetdraftswidget.h"
#include "customcontrols.h"

#include <QScrollArea>
#include <QVBoxLayout>

TweetDraftsWidget::TweetDraftsWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    StandardButton *backBtn = new StandardButton("Back");
    mainLayout->addWidget(backBtn);

    QScrollArea *scrollArea = new QScrollArea();
    QWidget *draftsContainerWidget = new QWidget();
    scrollArea->setWidget(draftsContainerWidget);
    mainLayout->addWidget(draftsContainerWidget);

    draftsContainerLayout = new QVBoxLayout();
    draftsContainerWidget->setLayout(draftsContainerLayout);
}

void TweetDraftsWidget::onTweetDraftAdded(const TweetDraft &tweetDraft)
{
    TweetDraftsItemWidget *draftItemWidget = new TweetDraftsItemWidget(tweetDraft);
    draftsContainerLayout->addWidget(draftItemWidget);
}

void TweetDraftsWidget::onBackPressed()
{
    emit backRequested();
}

void TweetDraftsWidget::onTweetDraftEdited(const TweetDraft &tweetTemplate)
{
    idToItemMap[tweetTemplate.getId()]->updateText(tweetTemplate.getText());
}

void TweetDraftsWidget::onTweetDraftDeleted(int draftId)
{
    TweetDraftsItemWidget *draftItemWidget = idToItemMap[draftId];
    idToItemMap.remove(draftId);
    delete draftItemWidget;
}
