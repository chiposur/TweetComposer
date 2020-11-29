#include "customcontrols.h"

const QColor StandardButton::standardGreen("#17a81a");
const QColor DeleteButton::deleteRed("#ff0000");

StandardButton::StandardButton(QWidget *parent) : QPushButton(parent)
{
    QString styleSheet =
        QString("QPushButton { color: %1; border: none; background-color: transparent; padding: 3px 4px; } ") +
        QString("QPushButton:disabled { color: gray; }") +
        QString("QPushButton:hover { color: white; border-width: 2px; border-color: %1; background-color: %1; }");

    setStyleSheet(styleSheet.arg(standardGreen.name()));
    setCursor(Qt::PointingHandCursor);
}

StandardButton::StandardButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    QString styleSheet =
        QString("QPushButton { color: %1; border: none; background-color: transparent; padding: 3px 4px; } ") +
        QString("QPushButton:disabled { color: gray; }") +
        QString("QPushButton:hover { color: white; border-width: 2px; border-color: %1; background-color: %1; }");

    setStyleSheet(styleSheet.arg(standardGreen.name()));
    setCursor(Qt::PointingHandCursor);
}

DeleteButton::DeleteButton(QWidget *parent) : QPushButton(parent)
{
    QString styleSheet =
        QString("QPushButton { color: %1; border: none; background-color: transparent; padding: 3px 4px; } ") +
        QString("QPushButton:disabled { color: gray; }") +
        QString("QPushButton:hover { color: white; border-width: 2px; border-color: %1; background-color: %1; }");

    setStyleSheet(styleSheet.arg(deleteRed.name()));
    setCursor(Qt::PointingHandCursor);
}

DeleteButton::DeleteButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    QString styleSheet =
        QString("QPushButton { color: %1; border: none; background-color: transparent; padding: 3px 4px; } ") +
        QString("QPushButton:disabled { color: gray; }") +
        QString("QPushButton:hover { color: white; border-width: 2px; border-color: %1; background-color: %1; }");

    setStyleSheet(styleSheet.arg(deleteRed.name()));
    setCursor(Qt::PointingHandCursor);
}
