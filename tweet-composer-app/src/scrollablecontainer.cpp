#include "scrollablecontainer.h"

ScrollableContainer::ScrollableContainer(QWidget *parent) : QScrollArea(parent)
{
    setStyleSheet("QScrollArea { background: transparent; border: none; }");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWidgetResizable(true);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    QWidget *containerWidget = new QWidget();
    containerWidget->setStyleSheet("QWidget { background: transparent; }");
    scrollableContainerLayout = new QVBoxLayout();
    scrollableContainerLayout->setContentsMargins(0, 0, 0, 0);
    scrollableContainerLayout->addStretch();
    containerWidget->setLayout(scrollableContainerLayout);
    setWidget(containerWidget);
}

void ScrollableContainer::appendWidget(QWidget *widget)
{
    // Insert widget before the stretch at the end of the layout
    scrollableContainerLayout->insertWidget(scrollableContainerLayout->count() - 1, widget);
}
