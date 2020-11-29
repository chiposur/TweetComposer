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

    StandardButton *backBtn = new StandardButton("Back");
    navBtnsLayout->addWidget(backBtn);

    connect(backBtn, SIGNAL(clicked()), this, SLOT(onBackPressed()));

    navBtnsLayout->addStretch();

    QScrollArea *scrollArea = new QScrollArea();
    QWidget *templatesContainerWidget = new QWidget();
    scrollArea->setWidget(templatesContainerWidget);
    mainLayout->addWidget(templatesContainerWidget);

    templatesContainerLayout = new QVBoxLayout();
    templatesContainerWidget->setLayout(templatesContainerLayout);

    mainLayout->addStretch();
}

void TweetTemplatesWidget::onTweetTemplateAdded(const TweetTemplate &tweetTemplate)
{
    TweetTemplatesItemWidget *templateItemWidget = new TweetTemplatesItemWidget(tweetTemplate);
    templatesContainerLayout->addWidget(templateItemWidget);
    connect(templateItemWidget, SIGNAL(templateItemClicked(int)), this, SLOT(onTweetTemplateClicked(int)));
    idToItemMap.insert(tweetTemplate.getId(), templateItemWidget);
}

void TweetTemplatesWidget::onBackPressed()
{
    emit backRequested();
}

void TweetTemplatesWidget::onTweetTemplateEdited(const TweetTemplate &tweetTemplate)
{
    idToItemMap[tweetTemplate.getId()]->updateText(tweetTemplate.getText());
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
