#include "customcontrols.h"
#include "styles.h"

Button::Button(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet(Styles::BUTTON_STYLE_SHEET);
    setCursor(Qt::PointingHandCursor);
}

Button::Button(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setStyleSheet(Styles::BUTTON_STYLE_SHEET);
    setCursor(Qt::PointingHandCursor);
}

DeleteButton::DeleteButton(QWidget *parent) : QPushButton(parent)
{
    setStyleSheet(Styles::DELETE_BUTTON_STYLE_SHEET);
    setCursor(Qt::PointingHandCursor);
}

DeleteButton::DeleteButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setStyleSheet(Styles::DELETE_BUTTON_STYLE_SHEET);
    setCursor(Qt::PointingHandCursor);
}

CheckBox::CheckBox(QWidget *parent) : QCheckBox(parent)
{
    setStyleSheet(Styles::CHECKBOX_STYLE_SHEET);
}

CheckBox::CheckBox(const QString &text, QWidget *parent) : QCheckBox(text, parent)
{
    setStyleSheet(Styles::CHECKBOX_STYLE_SHEET);
}

Typeahead::Typeahead(int debounceMs, QWidget *parent) : QLineEdit(parent), debounceMs(debounceMs)
{
    setStyleSheet(Styles::TYPEAHEAD_STYLE_SHEET);

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
