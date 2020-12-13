#include <QAction>
#include <QClipboard>
#include <QFont>
#include <QGuiApplication>
#include <QMessageBox>
#include <QSpacerItem>

#include "composewidget.h"
#include "settingsmanager.h"
#include "styles.h"

ComposeWidget::ComposeWidget(QWidget *parent) : QWidget(parent)
{
    dataStore = DataStore::getInstance();
    tweetDrafts = dataStore->getTweetDrafts();
    tweetTemplates = dataStore->getTweetTemplates();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    QHBoxLayout *navBtnsLayout = new QHBoxLayout();
    mainLayout->addLayout(navBtnsLayout);

    cancelBtn  = new QPushButton();
    navBtnsLayout->addWidget(cancelBtn);

    connect(cancelBtn, SIGNAL(clicked()), this, SLOT(clearTweetEdit()));

    navBtnsLayout->addStretch();

    QPushButton *draftsBtn = new QPushButton("Drafts");
    QPushButton *templatesBtn = new QPushButton("Templates");
    navBtnsLayout->addWidget(draftsBtn);
    navBtnsLayout->addWidget(templatesBtn);

    connect(draftsBtn, SIGNAL(clicked()), this, SLOT(draftsBtnClicked()));
    connect(templatesBtn, SIGNAL(clicked()), this, SLOT(templatesBtnClicked()));

    QHBoxLayout *toolButtonsLayout = new QHBoxLayout();
    toolButtonsLayout->setSpacing(0);
    toolButtonsLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(toolButtonsLayout);

    boldToggleButton = new BoldToggleButton("B");
    boldToggleButton->setCheckable(true);
    toolButtonsLayout->addWidget(boldToggleButton);

    connect(boldToggleButton, SIGNAL(toggled(bool)), this, SLOT(boldToggled(bool)));

    italicToggleButton = new ItalicToggleButton("I");
    italicToggleButton->setCheckable(true);
    toolButtonsLayout->addWidget(italicToggleButton);

    connect(italicToggleButton, SIGNAL(toggled(bool)), this, SLOT(italicToggled(bool)));

    underlineToggleButton = new UnderlineToggleButton("U");
    underlineToggleButton->setCheckable(true);
    toolButtonsLayout->addWidget(underlineToggleButton);

    connect(underlineToggleButton, SIGNAL(toggled(bool)), this, SLOT(underlineToggled(bool)));

    toolButtonsLayout->addSpacerItem(new QSpacerItem(8, 0));

    fontFamiliesComboBox = new QComboBox();
    QStringList fontFamilies;
    fontFamilies << "Helvetica"; // Helvetica is default twitter font
    fontFamilies << "Times";
    fontFamiliesComboBox->addItems(fontFamilies);
    toolButtonsLayout->addWidget(fontFamiliesComboBox);

    connect(fontFamiliesComboBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onCurrentTextChanged(const QString &)));

    fontFamily = fontFamilies.first();

    toolButtonsLayout->addStretch();

    tweetTextEdit = new TweetTextEdit();
    mainLayout->addWidget(tweetTextEdit);
    tweetTextEdit->setFontWeight(isBold ? QFont::Bold : QFont::Normal);
    tweetTextEdit->setFontItalic(isItalic);
    tweetTextEdit->setFontUnderline(isUnderline);
    tweetTextEdit->setFontFamily(getFontFamilyName(fontFamily));
    tweetTextEdit->setPlaceholderText("Compose tweet...");
    tweetTextEdit->setAcceptRichText(false);

    int frameWidth = tweetTextEdit->frameWidth();
    int editorWidth = Styles::TWEET_WIDTH_PX + frameWidth;
    int editorHeight = Styles::TWEET_MAX_HEIGHT_PX + frameWidth;
    tweetTextEdit->setFixedWidth(editorWidth);
    tweetTextEdit->setFixedHeight(editorHeight);

    connect(tweetTextEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    nameLineEdit = new QLineEdit();
    nameLineEdit->setPlaceholderText("Enter an optional name...");
    nameLineEdit->setMaxLength(200);
    nameLineEdit->setFixedWidth(tweetTextEdit->width());
    mainLayout->addWidget(nameLineEdit);

    QHBoxLayout *editorBottomLayout = new QHBoxLayout();
    toolButtonsLayout->setSpacing(0);
    toolButtonsLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(editorBottomLayout);

    saveAsDraftBtn = new QPushButton("Save as Draft");
    saveAsTemplateBtn = new QPushButton("Save as Template");
    saveBtn = new QPushButton();
    deleteBtn = new QPushButton();

    editorBottomLayout->addWidget(saveAsDraftBtn);
    editorBottomLayout->addWidget(saveAsTemplateBtn);
    editorBottomLayout->addWidget(saveBtn);
    editorBottomLayout->addWidget(deleteBtn);

    connect(saveAsDraftBtn, SIGNAL(clicked()), this, SLOT(saveAsDraftBtnClicked()));
    connect(saveAsTemplateBtn, SIGNAL(clicked()), this, SLOT(saveAsTemplateBtnClicked()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveBtnClicked()));
    connect(deleteBtn, SIGNAL(clicked()), this, SLOT(deleteBtnClicked()));

    editorBottomLayout->addStretch();

    charsRemainingLabel = new QLabel();
    editorBottomLayout->addWidget(charsRemainingLabel);

    mainLayout->addStretch();

    updateBtnStates();
}

int ComposeWidget::tweetTextLength()
{
    return tweetTextEdit->toPlainText().length();
}

QString ComposeWidget::getFontFamilyName(const QString &fontFamily)
{
    return fontFamily == "Helvetica" ? "Helvetica [Cronyx]" : "Times New Roman";
}

void ComposeWidget::boldToggled(bool checked)
{
    isBold = checked;
    tweetTextEdit->setFontWeight(isBold ? QFont::Bold : QFont::Normal);
}

void ComposeWidget::italicToggled(bool checked)
{
    isItalic = checked;
    tweetTextEdit->setFontItalic(isItalic);
}

void ComposeWidget::underlineToggled(bool checked)
{
    isUnderline = checked;
    tweetTextEdit->setFontUnderline(isUnderline);
}

void ComposeWidget::onTextChanged()
{
    // Set chars remaining label
    QString charsRemainingText;
    int charsRemaining = Styles::TWEET_MAX_LENGTH - tweetTextEdit->toPlainText().length();
    if (charsRemaining <=  Styles::TWEET_CHARS_REMAINING_LIMIT)
    {
        charsRemainingText = QString::number(charsRemaining);
        charsRemainingLabel->setStyleSheet(QString("QLabel { color: %1; }").arg(charsRemaining >= 0 ? "black" : "red"));
    }

    charsRemainingLabel->setText(charsRemainingText);

    updateBtnStates();
}

void ComposeWidget::onCurrentTextChanged(const QString &text)
{
    fontFamily = text ;
    tweetTextEdit->setFontFamily(getFontFamilyName(fontFamily));
}

void ComposeWidget::updateBtnStates()
{
    int tweetHasText = tweetTextLength() > 0;
    if (isTemplate() || isDraft())
    {
        cancelBtn->setText("Cancel edit");
        cancelBtn->setVisible(true);
        saveAsDraftBtn->setVisible(false);
        saveAsTemplateBtn->setVisible(false);
        saveBtn->setVisible(true);
        saveBtn->setText(isDraft() ? "Save Draft" : "Save Template");
        saveBtn->setEnabled(tweetHasText);
        deleteBtn->setVisible(true);
        deleteBtn->setText(isDraft() ? "Delete Draft" : "Delete Template");
    }
    else
    {
        cancelBtn->setVisible(tweetHasText);
        cancelBtn->setText("Clear");
        saveAsDraftBtn->setVisible(true);
        saveAsDraftBtn->setEnabled(tweetHasText);
        saveAsTemplateBtn->setVisible(true);
        saveAsTemplateBtn->setEnabled(tweetHasText);
        saveBtn->setVisible(false);
        deleteBtn->setVisible(false);
    }
}

void ComposeWidget::saveAsDraftBtnClicked()
{
    TweetDraft tweetDraft;
    tweetDraft.setId(TweetDraft::numDrafts + 1);
    tweetDraft.setText(tweetTextEdit->toHtml());
    tweetDraft.setName(nameLineEdit->text());
    dataStore->addTweetDraft(tweetDraft);
    clearTweetEdit();

    SettingsManager::getInstance()->saveTweetDrafts();

    Toast toast("Tweet saved as draft", Toast::ToastTypes::INFO, 2000);
    emit toastRequested(toast);
}

void ComposeWidget::saveAsTemplateBtnClicked()
{
    TweetTemplate tweetTemplate;
    tweetTemplate.setId(TweetTemplate::numTemplates + 1);
    tweetTemplate.setText(tweetTextEdit->toHtml());
    tweetTemplate.setName(nameLineEdit->text());
    dataStore->addTweetTemplate(tweetTemplate);
    clearTweetEdit();

    SettingsManager::getInstance()->saveTweetTemplates();

    Toast toast("Tweet saved as template", Toast::ToastTypes::INFO, 2000);
    emit toastRequested(toast);
}

void ComposeWidget::saveBtnClicked()
{
    bool success = false;

    // Perist changes
    if (isDraft())
    {
        if (dataStore->getDraftIdIndex(draftId) > -1)
        {
            TweetDraft tweetDraft;
            if (dataStore->getTweetDraftById(draftId, tweetDraft))
            {
                tweetDraft.setText(tweetTextEdit->toHtml());
                tweetDraft.setName(nameLineEdit->text());
                dataStore->editTweetDraftById(draftId, tweetDraft);
                success = SettingsManager::getInstance()->saveTweetDrafts();
            }
        }
    }
    else
    {
        TweetTemplate tweetTemplate;
        if (dataStore->getTweetTemplateById(templateId, tweetTemplate))
        {
            tweetTemplate.setText(tweetTextEdit->toHtml());
            tweetTemplate.setName(nameLineEdit->text());
            dataStore->editTweetTemplateById(templateId, tweetTemplate);
            success = SettingsManager::getInstance()->saveTweetTemplates();
        }
    }

    QString toastMessage =
        QString("%1%2 saved")
        .arg(isDraft() ? "Draft" : "Template")
        .arg(success ? "" : " not");
    Toast::ToastTypes toastType = success ? Toast::ToastTypes::INFO : Toast::ToastTypes::ERROR;
    Toast toast(toastMessage, toastType, 2000);
    emit toastRequested(toast);

    if (success)
    {
        clearTweetEdit();
    }
}

void ComposeWidget::deleteBtnClicked()
{
    // Perist changes
    bool success = false;
    if (isDraft())
    {
        if (dataStore->getDraftIdIndex(draftId) > -1)
        {
            dataStore->deleteTweetDraftById(draftId);
            success = SettingsManager::getInstance()->saveTweetDrafts();
        }

    }
    else
    {
        if (dataStore->getTemplateIdIndex(templateId) > -1)
        {
            dataStore->deleteTweetTemplateById(templateId);
            success = SettingsManager::getInstance()->saveTweetTemplates();
        }
    }

    QString toastMessage =
        QString("%1%2 deleted")
        .arg(isDraft() ? "Draft" : "Template")
        .arg(success ? "" : " not");
    Toast::ToastTypes toastType = success ? Toast::ToastTypes::INFO : Toast::ToastTypes::ERROR;
    Toast toast(toastMessage, toastType, 2000);
    emit toastRequested(toast);

    if (success)
    {
        clearTweetEdit();
    }
}

void ComposeWidget::clearTweetEdit()
{
    tweetTextEdit->setHtml("");
    nameLineEdit->setText("");
    draftId = templateId = -1;
    updateBtnStates();
}

void ComposeWidget::loadTweetDraft(const TweetDraft &tweetDraft)
{
    if (checkAndPromptIfDirty())
    {
        return;
    }

    tweetTextEdit->setHtml(tweetDraft.getText());
    nameLineEdit->setText(tweetDraft.getName());
    draftId = tweetDraft.getId();
    templateId = -1;
    updateBtnStates();
}

void ComposeWidget::loadTweetTemplate(const TweetTemplate &tweetTemplate)
{
    if (checkAndPromptIfDirty())
    {
        return;
    }

    tweetTextEdit->setHtml(tweetTemplate.getText());
    nameLineEdit->setText(tweetTemplate.getName());
    templateId = tweetTemplate.getId();
    draftId = -1;
    updateBtnStates();
}

bool ComposeWidget::checkAndPromptIfDirty()
{
    bool cancelLoad = false;
    if (!tweetTextEdit->toPlainText().isEmpty())
    {
        QMessageBox::StandardButton result = QMessageBox::question(this, "Clear tweet?", "Do you want to clear the current tweet?");
        if (result != QMessageBox::Yes)
        {
            cancelLoad = true;
        }
    }

    return cancelLoad;
}

void ComposeWidget::draftsBtnClicked()
{
    emit showTweetDrafts();
}

void ComposeWidget::templatesBtnClicked()
{
    emit showTweetTemplates();
}
