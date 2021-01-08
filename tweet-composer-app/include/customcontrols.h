#ifndef CUSTOMCONTROLS_H
#define CUSTOMCONTROLS_H

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QStyledItemDelegate>
#include <QPlainTextEdit>
#include <QTimer>
#include <QToolButton>

class ComboBoxItemDelegate : public QStyledItemDelegate
{
public:
    ComboBoxItemDelegate(QComboBox *comboBox);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    static const QString STYLE_SHEET;
    static const QString HOVER_STYLE_SHEET;

    QComboBox *comboBox;

    mutable QLabel itemRenderLabel;
};

class TweetTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    TweetTextEdit(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *e);
};

class BoldToggleButton : public QPushButton
{
    Q_OBJECT

public:
    BoldToggleButton(QWidget *parent = nullptr);
};

class ItalicToggleButton : public QPushButton
{
    Q_OBJECT

public:
    ItalicToggleButton(QWidget *parent = nullptr);
};

class DeleteButton : public QPushButton
{
    Q_OBJECT

public:
    DeleteButton(const QString &text, QWidget *parent = nullptr);
    DeleteButton(QWidget *parent = nullptr);

private:
    static const QString STYLE_SHEET;
};

class TwitterButton : public QPushButton
{
    Q_OBJECT

public:
    TwitterButton(const QString &text, QWidget *parent = nullptr);
    TwitterButton(QWidget *parent = nullptr);
};

class Typeahead : public QLineEdit
{
    Q_OBJECT

public:
    Typeahead(int debounceMs, QWidget *parent = nullptr);

signals:
    void searchTextChanged(const QString &text);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onDebounceTimeout();

private:
    int debounceMs;
    QTimer *debounceTimer;
};

#endif // CUSTOMCONTROLS_H
