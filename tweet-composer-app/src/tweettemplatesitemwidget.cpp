#include "tweettemplatesitemwidget.h"

#include <QVBoxLayout>

TweetTemplatesItemWidget::TweetTemplatesItemWidget(const TweetTemplate &tweetTemplate, QWidget *parent) : QWidget(parent)
{
    // TODO: style like tweet drafts
    templateId = tweetTemplate.getId();
    templateTextLabel = new QLabel(tweetTemplate.getText());

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addWidget(templateTextLabel);
}
