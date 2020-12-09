#ifndef CUSTOMCONTROLS_H
#define CUSTOMCONTROLS_H

#include <QColor>
#include <QLineEdit>
#include <QObject>
#include <QPushButton>
#include <QTimer>

class StandardButton : public QPushButton
{
    Q_OBJECT

public:
    StandardButton(const QString &text, QWidget *parent = nullptr);
    StandardButton(QWidget *parent = nullptr);

private:
    static const QColor standardGreen;
};

class DeleteButton : public QPushButton
{
    Q_OBJECT

public:
    DeleteButton(const QString &text, QWidget *parent = nullptr);
    DeleteButton(QWidget *parent = nullptr);

private:
    static const QColor deleteRed;
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
