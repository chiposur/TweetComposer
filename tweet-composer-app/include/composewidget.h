#ifndef COMPOSEWIDGET_H
#define COMPOSEWIDGET_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextCharFormat>
#include <QToolButton>

#include <tweetdraft.h>
#include <tweettemplate.h>
#include <customcontrols.h>
#include <datastore.h>
#include <toast.h>

class TextEdit : public QTextEdit
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent = nullptr) : QTextEdit(parent) {}
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
    void loadTweetDraft(const TweetDraft &tweetDraft);
    void loadTweetTemplate(const TweetTemplate &tweetTemplate);
    void draftsBtnClicked();
    void templatesBtnClicked();

signals:
    void showTweetDrafts();
    void showTweetTemplates();
    void toastRequested(const Toast &toast);

private:
    void setFont();
    void updateBtnStates();
    void clearTweetEdit();
    bool checkAndPromptIfDirty();
    QString getFontFamilyName(const QString &fontFamily);

    QToolButton *boldToolButton;
    QToolButton *italicToolButton;
    QToolButton *underlineToolButton;

    TextEdit *tweetTextEdit;

    QLabel *charsRemainingLabel;

    QComboBox *fontFamiliesComboBox;

    StandardButton *saveAsDraftBtn;
    StandardButton *saveAsTemplateBtn;
    StandardButton *saveBtn;
    StandardButton *deleteBtn;

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
