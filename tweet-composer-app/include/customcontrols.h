#ifndef CUSTOMCONTROLS_H
#define CUSTOMCONTROLS_H

#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QMenu>
#include <QMenuBar>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QTextEdit>
#include <QTimer>
#include <QToolButton>

class TweetTextEdit : public QTextEdit
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

class UnderlineToggleButton : public QPushButton
{
    Q_OBJECT

public:
    UnderlineToggleButton(QWidget *parent = nullptr);
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

class Typeahead : public QLineEdit
{
    Q_OBJECT

public:
    Typeahead(int debounceMs, QWidget *parent = nullptr);

signals:
    void textChanged(const QString &text);

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void onDebounceTimeout();

private:
    int debounceMs;
    QTimer *debounceTimer;
};

#endif // CUSTOMCONTROLS_H
