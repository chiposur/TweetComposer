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
    backBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    navBtnsLayout->addWidget(backBtn);

    connect(backBtn, SIGNAL(clicked()), this, SLOT(onBackPressed()));

    navBtnsLayout->addStretch();

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setStyleSheet("QScrollArea { background: transparent; border: none; }");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    QWidget *draftsContainerWidget = new QWidget();
    draftsContainerLayout = new QVBoxLayout();
    draftsContainerLayout->setContentsMargins(0, 0, 0, 0);
    draftsContainerLayout->addStretch();
    draftsContainerWidget->setLayout(draftsContainerLayout);
    scrollArea->setWidget(draftsContainerWidget);

    mainLayout->addWidget(scrollArea);
}

void TweetDraftsWidget::onTweetDraftAdded(const TweetDraft &tweetDraft)
{
    TweetDraftsItemWidget *draftItemWidget = new TweetDraftsItemWidget(tweetDraft);

    // Insert draft item before the stretch at the end of the layout
    draftsContainerLayout->insertWidget(draftsContainerLayout->count() - 1, draftItemWidget);

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
