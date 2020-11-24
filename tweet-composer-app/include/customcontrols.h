#ifndef CUSTOMCONTROLS_H
#define CUSTOMCONTROLS_H

#include <QColor>
#include <QObject>
#include <QPushButton>

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

#endif // CUSTOMCONTROLS_H
