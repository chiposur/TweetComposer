#include "tweetdraftsitemwidget.h"
#include "styles.h"

#include <QTextDocument>

TweetDraftsItemWidget::TweetDraftsItemWidget(const TweetDraft &tweetDraft, QWidget *parent) : QLabel(parent)
{
    draftId = tweetDraft.getId();
    updateText(tweetDraft.getText());
    updateName(tweetDraft.getName());

    // Border:no required to fix border-bottom styling bug in Qt 5
    QString styleSheet(
        QString("QLabel { border:no; font-size: 15px; border-bottom: 1px solid #17a81a; padding: 3px 4px; }") +
        QString("QLabel:hover { background-color: #17a81a; color: white; }"));
    setStyleSheet(styleSheet);
    setFixedWidth(Styles::TWEET_WIDTH_PX);
    setFixedHeight(sizeHint().height());
    setCursor(Qt::PointingHandCursor);
}

void TweetDraftsItemWidget::updateText(const QString &text)
{
    setText(text);

    QTextDocument doc;
    doc.setHtml(text);
    plainText = doc.toPlainText();
}

void TweetDraftsItemWidget::updateName(const QString &name)
{
    this->name = name;
}

void TweetDraftsItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit draftItemClicked(draftId);
    QWidget::mouseReleaseEvent(event);
}
