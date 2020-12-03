#include "toastwidget.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>

QString ToastWidget::infoBgColor = "#5bc0de";
QString ToastWidget::errorBgColor = "#d9534f";
QString ToastWidget::infoTextColor = "#004085";
QString ToastWidget::errorTextColor = "#721c24";
QString ToastWidget::infoBorderColor = "#b8daff";
QString ToastWidget::errorBorderColor = "#f5c6cb";

ToastWidget::ToastWidget(const Toast &toast, QWidget *parent) : QLabel(parent)
{
    toastId = toast.getId();
    setText(toast.getText());

    QString backgroundColor;
    QString textColor;
    QString borderColor;
    switch (toast.getToastType())
    {
    case Toast::ToastTypes::INFO:
        backgroundColor = infoBgColor;
        textColor = infoTextColor;
        borderColor = infoBorderColor;
        break;
    case Toast::ToastTypes::ERROR:
        backgroundColor = errorBgColor;
        textColor = errorTextColor;
        borderColor = errorBorderColor;
        break;
    default:
        backgroundColor = infoBgColor;
        textColor = infoTextColor;
        borderColor = infoBorderColor;
    }

    QString styleString =
        QString("QLabel {") +
        "background-color: %1; color: %2; border: 1px solid %3;" +
        "}";

    setStyleSheet(
        QString(styleString)
        .arg(backgroundColor)
        .arg(textColor)
        .arg(borderColor));

    QTimer::singleShot(toast.getDurationMs(), this, SLOT(onDurationExpired()));
}

void ToastWidget::onDurationExpired()
{
    emit toastWidgetExpired(height());
    deleteLater();
}
