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

#include "tweetdraft.h"
#include "tweettemplate.h"
#include "customcontrols.h"
#include "datastore.h"
#include "toast.h"
#include "twitterapiclient.h"

class ComposeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ComposeWidget(QWidget *parent = nullptr);

public slots:
    void boldToggled(bool checked);
    void italicToggled(bool checked);
    void underlineToggled(bool checked);
    void onTextChanged();
    void onCurrentTextChanged(const QString &text);
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
    void saveAsDraftBtnClicked();
    void saveAsTemplateBtnClicked();
    void saveBtnClicked();
    void deleteBtnClicked();
    void tweetBtnClicked();
    void onUpdateStatusFinished(RequestId id, TwitterApiClient::ResultType result);

private:
    int tweetTextLength();
    void setFont();
    void updateBtnStates();
    bool checkAndPromptIfDirty();
    QString getFontFamilyName(const QString &fontFamily);

    BoldToggleButton *boldToggleButton;
    ItalicToggleButton *italicToggleButton;
    UnderlineToggleButton *underlineToggleButton;

    TweetTextEdit *tweetTextEdit;
    QLineEdit *nameLineEdit;
    QLabel *charsRemainingLabel;
    QComboBox *fontFamiliesComboBox;

    QPushButton *cancelBtn;
    QPushButton *saveAsDraftBtn;
    QPushButton *saveAsTemplateBtn;
    QPushButton *saveBtn;
    QPushButton *deleteBtn;
    QPushButton *tweetBtn;

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
    TwitterApiClient *twitterApiClient;
};

#endif // COMPOSEWIDGET_H
