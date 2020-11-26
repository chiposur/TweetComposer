#include "tweettemplateswidget.h"
#include "customcontrols.h"

#include <QScrollArea>
#include <QVBoxLayout>

TweetTemplatesWidget::TweetTemplatesWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    StandardButton *backBtn = new StandardButton("Back");
    mainLayout->addWidget(backBtn);

    QScrollArea *scrollArea = new QScrollArea();
    QWidget *templatesContainerWidget = new QWidget();
    scrollArea->setWidget(templatesContainerWidget);
    mainLayout->addWidget(templatesContainerWidget);

    templatesContainerLayout = new QVBoxLayout();
    templatesContainerWidget->setLayout(templatesContainerLayout);
}

void TweetTemplatesWidget::onTweetTemplateAdded(const TweetTemplate &tweetTemplate)
{
    TweetTemplatesItemWidget *templateItemWidget = new TweetTemplatesItemWidget(tweetTemplate);
    templatesContainerLayout->addWidget(templateItemWidget);
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
