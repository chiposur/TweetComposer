#ifndef COMPOSEWIDGET_H
#define COMPOSEWIDGET_H

#include <QComboBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QVBoxLayout>

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
    void loadTweetDraft(const TweetDraft &tweetDraft);
    void loadTweetTemplate(const TweetTemplate &tweetTemplate);

signals:
    void showTweetDrafts();
    void showTweetTemplates();
    void toastRequested(const Toast &toast);

private slots:
    void boldToggled(bool checked);
    void italicToggled(bool checked);
    void draftsBtnClicked();
    void templatesBtnClicked();
    void clearTweetEdit();
    void saveAsDraftBtnClicked();
    void saveAsTemplateBtnClicked();
    void saveBtnClicked();
    void deleteBtnClicked();
    void tweetBtnClicked();
    void onUpdateStatusFinished(RequestId id, TwitterApiClient::ResultType result);
    void onTweetTextDocumentContentsChange(int position, int charsRemoved, int charsAdded);
    void onTextChanged();
    void onCurrentTextChanged(const QString &text);

private:
    int tweetTextLength();
    void setFont();
    void updateBtnStates();
    bool checkAndPromptIfDirty();
    QString getFontFamilyName(const QString &fontFamily);

    BoldToggleButton *boldToggleButton;
    ItalicToggleButton *italicToggleButton;

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

    static const QString MATH_SANS_BOLD_ALPHABET;
    static const QString MATH_SANS_ITALIC_ALPHABET;
    static const QString MATH_SANS_BOLD_ITALIC_ALPHABET;
    static const QString MATH_SERIF_BOLD_ALPHABET;
    static const QString MATH_SERIF_ITALIC_ALPHABET;
    static const QString MATH_SERIF_BOLD_ITALIC_ALPHABET;

    bool isBold = false;
    bool isItalic = false;

    int draftId = -1;
    int templateId = -1;

    bool isDraft() { return draftId > -1; }
    bool isTemplate() { return templateId > -1; }

    QString fontFamily;

    DataStore *dataStore;
    TwitterApiClient *twitterApiClient;
};

#endif // COMPOSEWIDGET_H
