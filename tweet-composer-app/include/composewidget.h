#ifndef COMPOSEWIDGET_H
#define COMPOSEWIDGET_H

#include <QHBoxLayout>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QTextCharFormat>
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
    void setCharFormat(QTextCharFormat &format);

    QHBoxLayout *toolButtonsLayout;
    QVBoxLayout *mainLayout;

    QToolButton *boldToolButton;
    QToolButton *italicToolButton;
    QToolButton *underlineToolButton;

    QPlainTextEdit *tweetTextEdit;

    bool isBold = false;
    bool isItalic = false;
    bool isUnderline = false;
};

#endif // COMPOSEWIDGET_H
