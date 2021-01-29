#include "tweettemplatesitemwidget.h"
#include "styles.h"

TweetTemplatesItemWidget::TweetTemplatesItemWidget(const TweetTemplate &tweetTemplate, QWidget *parent) : QLabel(parent)
{
    templateId = tweetTemplate.getId();
    setText(tweetTemplate.getText());
    setName(tweetTemplate.getName());
    setFixedWidth(Styles::TWEET_WIDTH_PX);
    setFixedHeight(sizeHint().height());
    setCursor(Qt::PointingHandCursor);
}

void TweetTemplatesItemWidget::setName(const QString &name)
{
    this->name = name;
}

void TweetTemplatesItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit templateItemClicked(templateId);
    QWidget::mouseReleaseEvent(event);
}

void TweetTemplatesItemWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    setStyleSheet(Styles::TWEET_TEMPLATES_ITEM_HOVER_STYLE_SHEET);
}

void TweetTemplatesItemWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    setStyleSheet("");
}
