#include "tweettemplatesitemwidget.h"

TweetTemplatesItemWidget::TweetTemplatesItemWidget(const TweetTemplate &tweetTemplate, QWidget *parent) : QLabel(parent)
{
    templateId = tweetTemplate.getId();
    setText(tweetTemplate.getText());

    // Border:no required to fix border-bottom styling bug in Qt 5
    QString styleSheet(
        QString("QLabel { cursor:pointer; border:no; border-bottom: 1px solid #17a81a; padding: 3px 4px; }") +
        QString("QLabel:hover { background-color: #17a81a; color: white; }"));
    setStyleSheet(styleSheet);

    setCursor(Qt::PointingHandCursor);
}

void TweetTemplatesItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit templateItemClicked(templateId);
    QWidget::mouseReleaseEvent(event);
}
