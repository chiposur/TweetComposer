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

    QPushButton *backBtn = new QPushButton("Back");
    backBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    navBtnsLayout->addWidget(backBtn);

    connect(backBtn, SIGNAL(clicked()), this, SIGNAL(backRequested()));

    navBtnsLayout->addStretch();

    Typeahead *search = new Typeahead(500);
    search->setPlaceholderText("Search by name or text...");
    connect(search, SIGNAL(searchTextChanged(const QString &)), this, SLOT(onSearchTextChanged(const QString &)));
    mainLayout->addWidget(search);

    draftsContainer = new ScrollableContainer();
    mainLayout->addWidget(draftsContainer);
}

void TweetDraftsWidget::onSearchTextChanged(const QString &text)
{
    for (TweetDraftsItemWidget *item : idToItemMap.values())
    {
        bool match = item->getPlainText().contains(text, Qt::CaseInsensitive)
                     || item->getName().contains(text, Qt::CaseInsensitive);
        item->setVisible(match);
    }
}

void TweetDraftsWidget::onTweetDraftAdded(const TweetDraft &tweetDraft)
{
    TweetDraftsItemWidget *draftItemWidget = new TweetDraftsItemWidget(tweetDraft);
    draftsContainer->appendWidget(draftItemWidget);

    connect(draftItemWidget, SIGNAL(draftItemClicked(int)), this, SIGNAL(editDraftRequested(int)));
    idToItemMap.insert(tweetDraft.getId(), draftItemWidget);
}

void TweetDraftsWidget::onTweetDraftEdited(const TweetDraft &tweetTemplate)
{
    TweetDraftsItemWidget *item = idToItemMap[tweetTemplate.getId()];
    item->updateText(tweetTemplate.getText());
    item->updateName(tweetTemplate.getName());
}

void TweetDraftsWidget::onTweetDraftDeleted(int draftId)
{
    TweetDraftsItemWidget *draftItemWidget = idToItemMap[draftId];
    idToItemMap.remove(draftId);
    draftItemWidget->deleteLater();
}
