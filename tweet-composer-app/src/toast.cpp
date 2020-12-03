#include "toast.h"

int Toast::numToasts = 0;

Toast::Toast()
{
    id = ++Toast::numToasts;
}

Toast::Toast(
    QString text,
    ToastTypes toastType,
    int durationMs)
{
    this->id = ++numToasts;
    this->text = text;
    this->toastType = toastType;
    this->durationMs = durationMs;
}
