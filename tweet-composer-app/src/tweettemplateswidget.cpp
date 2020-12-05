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
    backBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    navBtnsLayout->addWidget(backBtn);

    connect(backBtn, SIGNAL(clicked()), this, SLOT(onBackPressed()));

    navBtnsLayout->addStretch();

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setStyleSheet("QScrollArea { background: transparent; border: none; }");
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    QWidget *templatesContainerWidget = new QWidget();
    templatesContainerLayout = new QVBoxLayout();
    templatesContainerLayout->setContentsMargins(0, 0, 0, 0);
    templatesContainerLayout->addStretch();
    templatesContainerWidget->setLayout(templatesContainerLayout);
    scrollArea->setWidget(templatesContainerWidget);

    mainLayout->addWidget(scrollArea);
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
