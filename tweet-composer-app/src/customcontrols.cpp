#include "customcontrols.h"

#include <QLabel>
#include <QPainter>

#include <QKeyEvent>

const QString ComboBoxItemDelegate::STYLE_SHEET =
    "QLabel {"
    "font-size: 15px;"
    "padding: 2px 1px;"
    "background-color: white;"
    "color: #17a81a;"
    "font-family: %1;"
    "}";

const QString ComboBoxItemDelegate::HOVER_STYLE_SHEET =
    "QLabel {"
    "font-size: 15px;"
    "padding: 2px 1px;"
    "background-color: #17a81a;"
    "color: white;"
    "font-family: %1;"
    "}";

ComboBoxItemDelegate::ComboBoxItemDelegate(QComboBox *comboBox)
{
    this->comboBox = comboBox;
}

void ComboBoxItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    itemRenderLabel.setText(comboBox->itemText(index.row()));
    QFont font = comboBox->itemData(index.row(), Qt::FontRole).value<QFont>();
    QString fontFamily = font.family();
    itemRenderLabel.setStyleSheet(
        option.state & QStyle::State_MouseOver ? HOVER_STYLE_SHEET.arg(fontFamily) : STYLE_SHEET.arg(fontFamily));
    itemRenderLabel.render(painter, option.rect.topLeft());
}

QSize ComboBoxItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(option)
    Q_UNUSED(index)
    return QSize(comboBox->size().width(), 24);
}

TweetTextEdit::TweetTextEdit(QWidget *parent) : QPlainTextEdit(parent)
{

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
        QPlainTextEdit::keyPressEvent(e);
    }
}

BoldToggleButton::BoldToggleButton(QWidget *parent) : QPushButton(parent)
{
    setText("B");
    setFixedSize(24, 24);
    setCheckable(true);
}

ItalicToggleButton::ItalicToggleButton(QWidget *parent) : QPushButton(parent)
{
    setText("I");
    setFixedSize(24, 24);
    setCheckable(true);
}

DeleteButton::DeleteButton(QWidget *parent) : QPushButton(parent)
{
    setCursor(Qt::PointingHandCursor);
}

DeleteButton::DeleteButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setCursor(Qt::PointingHandCursor);
}

TwitterButton::TwitterButton(QWidget *parent) : QPushButton(parent)
{
    setCursor(Qt::PointingHandCursor);
}

TwitterButton::TwitterButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setCursor(Qt::PointingHandCursor);
}

Typeahead::Typeahead(int debounceMs, QWidget *parent) : QLineEdit(parent), debounceMs(debounceMs)
{
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
    emit searchTextChanged(text());
}
