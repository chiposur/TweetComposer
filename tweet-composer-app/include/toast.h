#ifndef TOAST_H
#define TOAST_H

#include <QString>

class Toast
{
public:
    enum class ToastTypes
    {
        INFO,
        ERROR,
    };

    Toast();

    Toast(
        QString text,
        ToastTypes toastType = ToastTypes::INFO,
        int durationMs = 2000);

    QString getText() { return text; }
    ToastTypes getToastType() { return toastType; }
    int getDurationMs() { return durationMs; }

    void setText(QString text) { this->text = text; }
    void setToastType(ToastTypes toastType) { this->toastType = toastType; }
    void setDurationMs(int durationMs) { this->durationMs = durationMs; }

private:
    QString text;
    ToastTypes toastType;
    int durationMs;
};

#endif // TOAST_H
