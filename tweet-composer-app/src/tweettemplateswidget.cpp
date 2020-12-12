#include "tweettemplateswidget.h"
#include "customcontrols.h"

#include <QHBoxLayout>
#include <QScrollArea>
#include <QVBoxLayout>

TweetTemplatesWidget::TweetTemplatesWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    QHBoxLayout *navBtnsLayout = new QHBoxLayout();
    mainLayout->addLayout(navBtnsLayout);

    Button *backBtn = new Button("Back");
    backBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    navBtnsLayout->addWidget(backBtn);

    connect(backBtn, SIGNAL(clicked()), this, SLOT(onBackPressed()));

    navBtnsLayout->addStretch();

    Typeahead *search = new Typeahead(500);
    search->setPlaceholderText("Search by name or text...");
    connect(search, SIGNAL(textChanged(const QString &)), this, SLOT(onSearchTextChanged(const QString &)));
    mainLayout->addWidget(search);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setStyleSheet("QScrollArea { background: transparent; border: none; }");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    QWidget *templatesContainerWidget = new QWidget();
    templatesContainerWidget->setStyleSheet("QWidget { background: transparent; }");
    templatesContainerLayout = new QVBoxLayout();
    templatesContainerLayout->setContentsMargins(0, 0, 0, 0);
    templatesContainerLayout->addStretch();
    templatesContainerWidget->setLayout(templatesContainerLayout);
    scrollArea->setWidget(templatesContainerWidget);

    mainLayout->addWidget(scrollArea);
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

    // Insert template item before the stretch at the end of the layout
    templatesContainerLayout->insertWidget(templatesContainerLayout->count() - 1, templateItemWidget);

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
    delete templateItemWidget;
}

void TweetTemplatesWidget::onTweetTemplateClicked(int templateId)
{
    emit editTemplateRequested(templateId);
}
