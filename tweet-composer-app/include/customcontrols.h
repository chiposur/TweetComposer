#ifndef CUSTOMCONTROLS_H
#define CUSTOMCONTROLS_H

#include <QCheckBox>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QTimer>

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
