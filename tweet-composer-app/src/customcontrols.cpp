#include "customcontrols.h"
#include "styles.h"

#include <QKeyEvent>

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent)
{
    setStyleSheet(Styles::MENU_BAR_STYLE_SHEET);
}

Menu::Menu(const QString &title, QWidget *parent) : QMenu(title, parent)
{
    setStyleSheet(Styles::MENU_STYLE_SHEET);
}

GroupBox::GroupBox(const QString &title, QWidget *parent) : QGroupBox(title, parent)
{
    setStyleSheet(Styles::GROUPBOX_STYLE_SHEET);
}

TweetTextEdit::TweetTextEdit(QWidget *parent) : QTextEdit(parent)
{
    setStyleSheet(Styles::TWEET_TEXT_EDIT_STYLE_SHEET);
}

void TweetTextEdit::keyPressEvent(QKeyEvent *e)
{
    if (toPlainText().length() >= 500 && e->key() != Qt::Key_Backspace && e->key() != Qt::Key_Delete)
    {
        // Prevent text longer than 500 characters
        e->accept();
    }
    else
    {
        QTextEdit::keyPressEvent(e);
    }
}

LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent)
{
    setStyleSheet(Styles::LINE_EDIT_STYLE_SHEET);
}

BoldToolButton::BoldToolButton(QWidget *parent) : QToolButton(parent)
{
    setStyleSheet(Styles::BOLD_TOOL_BUTTON_STYLE_SHEET);
}

ItalicToolButton::ItalicToolButton(QWidget *parent) : QToolButton(parent)
{
    setStyleSheet(Styles::ITALIC_TOOL_BUTTON_STYLE_SHEET);
}

UnderlineToolButton::UnderlineToolButton(QWidget *parent) : QToolButton(parent)
{
    setStyleSheet(Styles::UNDERLINE_TOOL_BUTTON_STYLE_SHEET);
}

ComboBox::ComboBox(QWidget *parent) : QComboBox(parent)
{
    setStyleSheet(Styles::COMBOBOX_STYLE_SHEET);
}

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
