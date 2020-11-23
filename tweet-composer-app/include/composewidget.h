#ifndef COMPOSEWIDGET_H
#define COMPOSEWIDGET_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QPlainTextEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextCharFormat>
#include <QToolButton>

class ComposeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComposeWidget(QWidget *parent = nullptr);

public slots:
    void boldTriggered();
    void italicTriggered();
    void underlineTriggered();
    void onTextChanged();
    void onCopyClicked();
    void onCurrentTextChanged(const QString &text);

private:
    void setFont();

    QHBoxLayout *toolButtonsLayout;
    QVBoxLayout *mainLayout;

    QToolButton *boldToolButton;
    QToolButton *italicToolButton;
    QToolButton *underlineToolButton;

    QPlainTextEdit *tweetTextEdit;

    QLabel *charsRemainingLabel;

    QComboBox *fontFamiliesComboBox;

    static const int MAX_TWEET_LENGTH = 280;
    static const int CHARS_REMAINING_LIMIT = 20;

    bool isBold = false;
    bool isItalic = false;
    bool isUnderline = false;

    QString fontFamily;
};

#endif // COMPOSEWIDGET_H
