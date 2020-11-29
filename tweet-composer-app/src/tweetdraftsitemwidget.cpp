#include "tweetdraftsitemwidget.h"

#include <QVBoxLayout>

TweetDraftsItemWidget::TweetDraftsItemWidget(const TweetDraft &tweetDraft, QWidget *parent) : QWidget(parent)
{
    draftId = tweetDraft.getId();
    draftTextLabel = new QLabel(tweetDraft.getText());

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);
    mainLayout->addWidget(draftTextLabel);

    // Border:no required to fix border-bottom styling bug in Qt 5
    QString styleSheet(
        QString("QLabel { border:no; border-bottom: 1px solid #17a81a; padding: 3px 4px; }") +
        QString("QLabel:hover { background-color: #17a81a; color: white; }"));
    draftTextLabel->setStyleSheet(styleSheet);

    setCursor(Qt::PointingHandCursor);
}

void TweetDraftsItemWidget::mouseReleaseEvent(QMouseEvent *event)
{
    emit draftItemClicked(draftId);
    QWidget::mouseReleaseEvent(event);
}
