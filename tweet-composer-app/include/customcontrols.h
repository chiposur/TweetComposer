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

class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar(QWidget *parent = nullptr);
};

class Menu : public QMenu
{
    Q_OBJECT
public:
    Menu(const QString &title, QWidget *parent = nullptr);
};

class GroupBox : public QGroupBox
{
    Q_OBJECT
public:
    GroupBox(const QString &title, QWidget *parent = nullptr);
};

class TweetTextEdit : public QTextEdit
{
    Q_OBJECT

public:
    TweetTextEdit(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent *e);
};

class LineEdit : public QLineEdit
{
    Q_OBJECT

public:
    LineEdit(QWidget *parent = nullptr);
};

class ComboBox : public QComboBox
{
    Q_OBJECT

public:
    ComboBox(QWidget *parent = nullptr);
};

class BoldToolButton : public QToolButton
{
    Q_OBJECT

public:
    BoldToolButton(QWidget *parent = nullptr);
};

class ItalicToolButton : public QToolButton
{
    Q_OBJECT

public:
    ItalicToolButton(QWidget *parent = nullptr);
};

class UnderlineToolButton : public QToolButton
{
    Q_OBJECT

public:
    UnderlineToolButton(QWidget *parent = nullptr);
};

class Button : public QPushButton
{
    Q_OBJECT

public:
    Button(const QString &text, QWidget *parent = nullptr);
    Button(QWidget *parent = nullptr);

private:
    static const QString STYLE_SHEET;
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

class CheckBox : public QCheckBox
{
    Q_OBJECT

public:
    CheckBox(const QString &text, QWidget *parent = nullptr);
    CheckBox(QWidget *parent = nullptr);
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
