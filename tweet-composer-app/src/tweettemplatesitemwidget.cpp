#include "tweettemplatesitemwidget.h"
#include "styles.h"

#include <QTextDocument>

TweetTemplatesItemWidget::TweetTemplatesItemWidget(const TweetTemplate &tweetTemplate, QWidget *parent) : QLabel(parent)
{
    templateId = tweetTemplate.getId();
    updateText(tweetTemplate.getText());
    updateName(tweetTemplate.getName());

    // Border:no required to fix border-bottom styling bug in Qt 5
    QString styleSheet(
        QString("QLabel { border:no; font-size: 15px; border-bottom: 1px solid #17a81a; padding: 3px 4px; }") +
        QString("QLabel:hover { background-color: #17a81a; color: white; }"));
    setStyleSheet(styleSheet);
    setFixedWidth(Styles::TWEET_WIDTH_PX);
    setFixedHeight(sizeHint().height());
    setCursor(Qt::PointingHandCursor);
}

void TweetTemplatesItemWidget::updateText(const QString &text)
{
    setText(text);

    QTextDocument doc;
    doc.setHtml(text);
    plainText = doc.toPlainText();
}

void TweetTemplatesItemWidget::updateName(const QString &name)
{
    this->name = name;
}

void TweetTemplatesItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit templateItemClicked(templateId);
    QWidget::mouseReleaseEvent(event);
}
