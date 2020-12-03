#ifndef TOASTWIDGET_H
#define TOASTWIDGET_H

#include <QLabel>

#include "toast.h"

class ToastWidget : public QLabel
{
    Q_OBJECT

public:
    ToastWidget(const Toast &toast, QWidget *parent = nullptr);

signals:
    void toastWidgetExpired(int height);

private slots:
    void onDurationExpired();

private:
    static QString infoBgColor;
    static QString errorBgColor;
    static QString infoTextColor;
    static QString errorTextColor;
    static QString infoBorderColor;
    static QString errorBorderColor;

    int toastId;
};

#endif
