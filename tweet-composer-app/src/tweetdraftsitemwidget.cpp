#include "tweetdraftsitemwidget.h"
#include "styles.h"

#include <QTextDocument>

TweetDraftsItemWidget::TweetDraftsItemWidget(const TweetDraft &tweetDraft, QWidget *parent) : QLabel(parent)
{
    draftId = tweetDraft.getId();
    setText(tweetDraft.getText());
    setName(tweetDraft.getName());
    setFixedWidth(Styles::TWEET_WIDTH_PX);
    setFixedHeight(sizeHint().height());
    setCursor(Qt::PointingHandCursor);
}

void TweetDraftsItemWidget::setName(const QString &name)
{
    this->name = name;
}

void TweetDraftsItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit draftItemClicked(draftId);
    QWidget::mouseReleaseEvent(event);
}

void TweetDraftsItemWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    setStyleSheet(Styles::TWEET_DRAFTS_ITEM_HOVER_STYLE_SHEET);
}

void TweetDraftsItemWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    setStyleSheet("");
}

