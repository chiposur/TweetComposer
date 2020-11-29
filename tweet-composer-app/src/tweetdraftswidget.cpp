#include "tweetdraftswidget.h"
#include "customcontrols.h"

#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>

TweetDraftsWidget::TweetDraftsWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    QHBoxLayout *navBtnsLayout = new QHBoxLayout();
    mainLayout->addLayout(navBtnsLayout);

    StandardButton *backBtn = new StandardButton("Back");
    navBtnsLayout->addWidget(backBtn);

    connect(backBtn, SIGNAL(clicked()), this, SLOT(onBackPressed()));

    navBtnsLayout->addStretch();

    QScrollArea *scrollArea = new QScrollArea();
    QWidget *draftsContainerWidget = new QWidget();
    scrollArea->setWidget(draftsContainerWidget);
    mainLayout->addWidget(draftsContainerWidget);

    draftsContainerLayout = new QVBoxLayout();
    draftsContainerWidget->setLayout(draftsContainerLayout);

    mainLayout->addStretch();
}

void TweetDraftsWidget::onTweetDraftAdded(const TweetDraft &tweetDraft)
{
    TweetDraftsItemWidget *draftItemWidget = new TweetDraftsItemWidget(tweetDraft);
    draftsContainerLayout->addWidget(draftItemWidget);
    connect(draftItemWidget, SIGNAL(draftItemClicked(int)), this, SLOT(onTweetDraftClicked(int)));
    idToItemMap.insert(tweetDraft.getId(), draftItemWidget);
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

void TweetDraftsWidget::onTweetDraftClicked(int draftId)
{
    emit editDraftRequested(draftId);
}
