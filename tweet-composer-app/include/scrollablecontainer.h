#ifndef SCROLLABLECONTAINER_H
#define SCROLLABLECONTAINER_H

#include <QScrollArea>
#include <QVBoxLayout>

class ScrollableContainer : public QScrollArea
{
    Q_OBJECT

public:
    ScrollableContainer(QWidget *parent = nullptr);

    void appendWidget(QWidget *widget);

private:
    QVBoxLayout *scrollableContainerLayout;
};
#endif // SCROLLABLECONTAINER_H
