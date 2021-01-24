#ifndef TOASTLAYOUTMANAGER_H
#define TOASTLAYOUTMANAGER_H

#include <QMap>
#include <QObject>

#include "toast.h"
#include "toastwidget.h"

class ToastLayoutManager : public QObject
{
    Q_OBJECT
public:
    explicit ToastLayoutManager(QWidget *parent);

    void addToast(const Toast &toast);

    void updateAllToastCoordinates();
    void updateToastCoordinates(ToastWidget *toastWidget);

private slots:
    void onToastWidgetExpired(int id);

private:
    static const int TOAST_MARGIN_PX = 8;

    QWidget *parent;
    QMap<int, ToastWidget *> idToToastWidgetMap;
    int topToastHeight = 0;
};

#endif // TOASTLAYOUTMANAGER_H
