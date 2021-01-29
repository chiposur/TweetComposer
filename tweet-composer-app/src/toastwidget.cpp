#include "toastwidget.h"
#include "twitterbootstrapstyles.h"

#include <QTimer>

ToastWidget::ToastWidget(
    const Toast &toast,
    const QString &text,
    QWidget *parent)
    : QLabel(text, parent)
{
    toastId = toast.getId();

    QString backgroundColor;
    QString textColor;
    QString borderColor;
    switch (toast.getToastType())
    {
    case Toast::ToastTypes::INFO:
        backgroundColor = TwitterBootstrapStyles::INFO_BG_COLOR;
        textColor = TwitterBootstrapStyles::INFO_TEXT_COLOR;
        borderColor = TwitterBootstrapStyles::INFO_BORDER_COLOR;
        break;
    case Toast::ToastTypes::ERROR:
        backgroundColor = TwitterBootstrapStyles::ERROR_BG_COLOR;
        textColor = TwitterBootstrapStyles::ERROR_TEXT_COLOR;
        borderColor = TwitterBootstrapStyles::ERROR_BORDER_COLOR;
        break;
    default:
        backgroundColor = TwitterBootstrapStyles::INFO_BG_COLOR;
        textColor = TwitterBootstrapStyles::INFO_TEXT_COLOR;
        borderColor = TwitterBootstrapStyles::INFO_BORDER_COLOR;
    }

    QString styleString =
        QString("QLabel {") +
        "background-color: %1; color: %2; border: 1px solid %3;" +
        "padding: 8px;"
        "}";

    setStyleSheet(
        QString(styleString)
        .arg(backgroundColor)
        .arg(textColor)
        .arg(borderColor));

    setFixedSize(sizeHint());
    QTimer::singleShot(toast.getDurationMs(), this, SLOT(onDurationExpired()));
}

void ToastWidget::onDurationExpired()
{
    emit toastWidgetExpired(toastId);
    deleteLater();
}
