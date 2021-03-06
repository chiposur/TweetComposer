#ifndef TOASTWIDGET_H
#define TOASTWIDGET_H

#include <QLabel>

#include "toast.h"

class ToastWidget : public QLabel
{
    Q_OBJECT

public:
    ToastWidget(
        const Toast &toast,
        const QString &text,
        QWidget *parent = nullptr);

signals:
    void toastWidgetExpired(int id);

private slots:
    void onDurationExpired();

private:
    int toastId;
};

#endif
