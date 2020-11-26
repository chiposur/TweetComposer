#include "toast.h"

Toast::Toast()
{

}

Toast::Toast(
    QString text,
    ToastTypes toastType,
    int durationMs)
{
    this->text = text;
    this->toastType = toastType;
    this->durationMs = durationMs;
}
