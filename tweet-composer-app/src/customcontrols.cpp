#include "customcontrols.h"
#include "styles.h"

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

Typeahead::Typeahead(int debounceMs, QWidget *parent) : QLineEdit(parent), debounceMs(debounceMs)
{
    setStyleSheet(
        QString("QLineEdit { font-size: 15px; border-radius: %1px; "
                "background: transparent; border: 2px solid %2; padding: %3px %4px; }")
        .arg(QString::number(Styles::TYPEAHEAD_BORDER_RADIUS))
        .arg(Styles::TYPEAHEAD_BORDER_COLOR)
        .arg(QString::number(Styles::TYPEAHEAD_PADDING_TOP_BOTTOM))
        .arg(QString::number(Styles::TYPEAHEAD_PADDING_LEFT_RIGHT)));

    debounceTimer = new QTimer();
    debounceTimer->setSingleShot(true);
    connect(debounceTimer, SIGNAL(timeout()), this, SLOT(onDebounceTimeout()));
}

void Typeahead::keyPressEvent(QKeyEvent *event)
{
    debounceTimer->start(debounceMs);
    QLineEdit::keyPressEvent(event);
}

void Typeahead::onDebounceTimeout()
{
    emit textChanged(text());
}
