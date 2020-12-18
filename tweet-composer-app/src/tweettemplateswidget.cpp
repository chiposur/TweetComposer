#include "tweettemplateswidget.h"

#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>

TweetTemplatesWidget::TweetTemplatesWidget(QWidget *parent) : QWidget(parent)
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

    templatesContainer = new DraftsTemplatesContainer();
    mainLayout->addWidget(templatesContainer);
}

void TweetTemplatesWidget::onSearchTextChanged(const QString &text)
{
    for (TweetTemplatesItemWidget *item : idToItemMap.values())
    {
        bool match = item->getPlainText().contains(text, Qt::CaseInsensitive)
                     || item->getName().contains(text, Qt::CaseInsensitive);
        item->setVisible(match);
    }
}

void TweetTemplatesWidget::onTweetTemplateAdded(const TweetTemplate &tweetTemplate)
{
    TweetTemplatesItemWidget *templateItemWidget = new TweetTemplatesItemWidget(tweetTemplate);
    templatesContainer->appendWidget(templateItemWidget);

    connect(templateItemWidget, SIGNAL(templateItemClicked(int)), this, SLOT(onTweetTemplateClicked(int)));
    idToItemMap.insert(tweetTemplate.getId(), templateItemWidget);
}

void TweetTemplatesWidget::onBackPressed()
{
    emit backRequested();
}

void TweetTemplatesWidget::onTweetTemplateEdited(const TweetTemplate &tweetTemplate)
{
    TweetTemplatesItemWidget *item = idToItemMap[tweetTemplate.getId()];
    item->updateText(tweetTemplate.getText());
    item->updateName(tweetTemplate.getName());
}

void TweetTemplatesWidget::onTweetTemplateDeleted(int templateId)
{
    TweetTemplatesItemWidget *templateItemWidget = idToItemMap[templateId];
    idToItemMap.remove(templateId);
    templateItemWidget->deleteLater();
}

void TweetTemplatesWidget::onTweetTemplateClicked(int templateId)
{
    emit editTemplateRequested(templateId);
}
