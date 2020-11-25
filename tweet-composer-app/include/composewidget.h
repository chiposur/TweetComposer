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

#include <tweetdraft.h>
#include <tweettemplate.h>
#include <customcontrols.h>
#include <datastore.h>

class PlainTextEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    PlainTextEdit(QWidget *parent = nullptr) : QPlainTextEdit(parent) {}
    void keyPressEvent(QKeyEvent *e);
};

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
    void onCurrentTextChanged(const QString &text);
    void saveAsDraftBtnClicked();
    void saveAsTemplateBtnClicked();
    void saveBtnClicked();
    void deleteBtnClicked();

signals:
    void tweetDraftAdded(const TweetDraft &tweetDraft);
    void tweetTemplateAdded(const TweetTemplate &tweetTemplate);
    void showTweetDrafts();
    void showTweetTemplates();

private:
    void setFont();
    void updateBtnStates();

    QHBoxLayout *toolButtonsLayout;
    QVBoxLayout *mainLayout;

    QToolButton *boldToolButton;
    QToolButton *italicToolButton;
    QToolButton *underlineToolButton;

    PlainTextEdit *tweetTextEdit;

    QLabel *charsRemainingLabel;

    QComboBox *fontFamiliesComboBox;

    StandardButton *saveAsDraftBtn;
    StandardButton *saveAsTemplateBtn;
    StandardButton *saveBtn;
    StandardButton *deleteBtn;

    static const int MAX_TWEET_LENGTH = 280;
    static const int CHARS_REMAINING_LIMIT = 20;
    static const int EDITOR_WIDTH_PX = 476;
    static const int EDITOR_HEIGHT_PX = 160;
    static const int FONT_SIZE = 15;

    bool isBold = false;
    bool isItalic = false;
    bool isUnderline = false;

    int draftId = -1;
    int templateId = -1;

    bool isDraft() { return draftId > -1; }
    bool isTemplate() { return templateId > -1; }

    QString fontFamily;

    QVector<TweetDraft> *tweetDrafts;
    QVector<TweetTemplate> *tweetTemplates;

    DataStore *dataStore;
};

#endif // COMPOSEWIDGET_H
