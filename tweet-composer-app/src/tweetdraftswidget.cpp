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

    connect(backBtn, SIGNAL(clicked()), this, SLOT(onBackPressed()));

    navBtnsLayout->addStretch();

    Typeahead *search = new Typeahead(500);
    search->setPlaceholderText("Search by name or text...");
    connect(search, SIGNAL(textChanged(const QString &)), this, SLOT(onSearchTextChanged(const QString &)));
    mainLayout->addWidget(search);

    DraftsTemplatesContainer *draftsContainer = new DraftsTemplatesContainer();
    draftsLayout = draftsContainer->draftsTemplatesContainerLayout;
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

    // Insert draft item before the stretch at the end of the layout
    draftsLayout->insertWidget(draftsLayout->count() - 1, draftItemWidget);

    connect(draftItemWidget, SIGNAL(draftItemClicked(int)), this, SLOT(onTweetDraftClicked(int)));
    idToItemMap.insert(tweetDraft.getId(), draftItemWidget);
}

void TweetDraftsWidget::onBackPressed()
{
    emit backRequested();
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
    delete draftItemWidget;
}

void TweetDraftsWidget::onTweetDraftClicked(int draftId)
{
    emit editDraftRequested(draftId);
}
