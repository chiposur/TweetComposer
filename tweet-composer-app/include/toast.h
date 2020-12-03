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

    QString getText() const { return text; }
    ToastTypes getToastType() const { return toastType; }
    int getDurationMs() const { return durationMs; }
    int getId() const { return id; }

    void setText(QString text) { this->text = text; }
    void setToastType(ToastTypes toastType) { this->toastType = toastType; }
    void setDurationMs(int durationMs) { this->durationMs = durationMs; }

private:
    static int numToasts;

    QString text;
    ToastTypes toastType;
    int durationMs;
    int id;
};

#endif // TOAST_H
