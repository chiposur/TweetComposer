#include "customcontrols.h"
#include "styles.h"

#include <QKeyEvent>

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
