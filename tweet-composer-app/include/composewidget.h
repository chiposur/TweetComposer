#ifndef COMPOSEWIDGET_H
#define COMPOSEWIDGET_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QTextCharFormat>
#include <QToolButton>

#include <tweetdraft.h>
#include <tweettemplate.h>
#include <customcontrols.h>
#include <datastore.h>
#include <toast.h>

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

private slots:
    void clearTweetEdit();

private:
    int tweetTextLength();
    void setFont();
    void updateBtnStates();
    bool checkAndPromptIfDirty();
    QString getFontFamilyName(const QString &fontFamily);

    QToolButton *boldToolButton;
    QToolButton *italicToolButton;
    QToolButton *underlineToolButton;

    TweetTextEdit *tweetTextEdit;
    QLineEdit *nameLineEdit;
    QLabel *charsRemainingLabel;
    QComboBox *fontFamiliesComboBox;

    QPushButton *cancelBtn;
    QPushButton *saveAsDraftBtn;
    QPushButton *saveAsTemplateBtn;
    QPushButton *saveBtn;
    QPushButton *deleteBtn;

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
