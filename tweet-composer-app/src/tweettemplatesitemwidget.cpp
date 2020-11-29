#include "tweettemplatesitemwidget.h"

#include <QVBoxLayout>

TweetTemplatesItemWidget::TweetTemplatesItemWidget(const TweetTemplate &tweetTemplate, QWidget *parent) : QWidget(parent)
{
    templateId = tweetTemplate.getId();
    templateTextLabel = new QLabel(tweetTemplate.getText());

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addWidget(templateTextLabel);

    // Border:no required to fix border-bottom styling bug in Qt 5
    QString styleSheet(
        QString("QLabel { cursor:pointer; border:no; border-bottom: 1px solid #17a81a; padding: 3px 4px; }") +
        QString("QLabel:hover { background-color: #17a81a; color: white; }"));
    templateTextLabel->setStyleSheet(styleSheet);

    setCursor(Qt::PointingHandCursor);
}

void TweetTemplatesItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit templateItemClicked(templateId);
    QWidget::mouseReleaseEvent(event);
}
