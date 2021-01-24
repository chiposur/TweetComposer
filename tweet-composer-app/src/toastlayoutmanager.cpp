#include "toastlayoutmanager.h"

ToastLayoutManager::ToastLayoutManager(QWidget *parent)
{
    this->parent = parent;
}

void ToastLayoutManager::addToast(const Toast &toast)
{
    ToastWidget *toastWidget = new ToastWidget(toast, toast.getText(), parent);
    idToToastWidgetMap.insert(toast.getId(), toastWidget);
    connect(toastWidget, SIGNAL(toastWidgetExpired(int)), this, SLOT(onToastWidgetExpired(int)));
    moveToTop(toastWidget);
}

void ToastLayoutManager::updatePositions()
{
    topToastHeight = 0;
    for (ToastWidget *toastWidget : idToToastWidgetMap.values())
    {
        moveToTop(toastWidget);
    }
}

void ToastLayoutManager::moveToTop(ToastWidget *toastWidget)
{
    topToastHeight += TOAST_MARGIN_PX + toastWidget->height();
    int toastX = parent->width() - toastWidget->width() - TOAST_MARGIN_PX;
    int toastY = parent->height() - topToastHeight;
    toastWidget->move(toastX, toastY);
    toastWidget->setVisible(true);
}

void ToastLayoutManager::onToastWidgetExpired(int id)
{
    idToToastWidgetMap.remove(id);
    updatePositions();
}
