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

BoldToggleButton::BoldToggleButton(QWidget *parent) : QPushButton(parent)
{
    setText("B");
    setFixedSize(24, 24);
    setCheckable(true);
    setStyleSheet(Styles::BOLD_TOGGLE_BUTTON_STYLE_SHEET);
}

ItalicToggleButton::ItalicToggleButton(QWidget *parent) : QPushButton(parent)
{
    setText("I");
    setFixedSize(24, 24);
    setCheckable(true);
    setStyleSheet(Styles::ITALIC_TOGGLE_BUTTON_STYLE_SHEET);
}


UnderlineToggleButton::UnderlineToggleButton(QWidget *parent) : QPushButton(parent)
{
    setText("U");
    setFixedSize(24, 24);
    setCheckable(true);
    setStyleSheet(Styles::UNDERLINE_TOGGLE_BUTTON_STYLE_SHEET);
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
