#ifndef COMPOSEWIDGET_H
#define COMPOSEWIDGET_H

#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QToolButton>

class ComposeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ComposeWidget(QWidget *parent = nullptr);

signals:

public slots:
    void boldTriggered();
    void italicTriggered();
    void underlineTriggered();

private:
    QHBoxLayout *toolButtonsLayout;
    QVBoxLayout *mainLayout;

    QToolButton *boldToolButton;
    QToolButton *italicToolButton;
    QToolButton *underlineToolButton;

    QTextEdit *tweetTextEdit;
};

#endif // COMPOSEWIDGET_H
