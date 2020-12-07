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

    StandardButton *draftsBtn = new StandardButton("Drafts");
    StandardButton *templatesBtn = new StandardButton("Templates");
    navBtnsLayout->addWidget(draftsBtn);
    navBtnsLayout->addWidget(templatesBtn);

    connect(draftsBtn, SIGNAL(clicked()), this, SLOT(draftsBtnClicked()));
    connect(templatesBtn, SIGNAL(clicked()), this, SLOT(templatesBtnClicked()));

    navBtnsLayout->addStretch();

    QHBoxLayout *toolButtonsLayout = new QHBoxLayout();
    toolButtonsLayout->setSpacing(0);
    toolButtonsLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(toolButtonsLayout);

    boldToolButton = new QToolButton();
    boldToolButton->setText("B");
    boldToolButton->setCheckable(true);
    boldToolButton->setStyleSheet("QToolButton { font-weight: bold; }");
    toolButtonsLayout->addWidget(boldToolButton);

    connect(boldToolButton, SIGNAL(clicked()), this, SLOT(boldTriggered()));

    italicToolButton = new QToolButton();
    italicToolButton->setText("I");
    italicToolButton->setCheckable(true);
    italicToolButton->setStyleSheet("QToolButton { font-style: italic; }");
    toolButtonsLayout->addWidget(italicToolButton);

    connect(italicToolButton, SIGNAL(clicked()), this, SLOT(italicTriggered()));

    underlineToolButton = new QToolButton();
    underlineToolButton->setText("U");
    underlineToolButton->setCheckable(true);
    underlineToolButton->setStyleSheet("QToolButton { text-decoration: underline; }");
    toolButtonsLayout->addWidget(underlineToolButton);

    connect(underlineToolButton, SIGNAL(clicked()), this, SLOT(underlineTriggered()));

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

    tweetTextEdit = new TextEdit();
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
    tweetTextEdit->setStyleSheet("QTextEdit { font-size: 15px; }");

    connect(tweetTextEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    QHBoxLayout *editorBottomLayout = new QHBoxLayout();
    toolButtonsLayout->setSpacing(0);
    toolButtonsLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(editorBottomLayout);

    saveAsDraftBtn = new StandardButton("Save as Draft");
    saveAsTemplateBtn = new StandardButton("Save as Template");
    saveBtn = new StandardButton();
    deleteBtn = new StandardButton();

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

QString ComposeWidget::getFontFamilyName(const QString &fontFamily)
{
    return fontFamily == "Helvetica" ? "Helvetica [Cronyx]" : "Times New Roman";
}

void ComposeWidget::boldTriggered()
{
    isBold = !isBold;
    tweetTextEdit->setFontWeight(isBold ? QFont::Bold : QFont::Normal);
}

void ComposeWidget::italicTriggered()
{
    isItalic = !isItalic;
    tweetTextEdit->setFontItalic(isItalic);
}

void ComposeWidget::underlineTriggered()
{
    isUnderline = !isUnderline;
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
    if (isTemplate() || isDraft())
    {
        saveAsDraftBtn->setVisible(false);
        saveAsTemplateBtn->setVisible(false);
        saveBtn->setVisible(true);
        deleteBtn->setVisible(true);

        saveBtn->setText(isDraft() ? "Save Draft" : "Save Template");
        saveBtn->setEnabled(tweetTextEdit->toPlainText().length() > 0);
        deleteBtn->setText(isDraft() ? "Delete Draft" : "Delete Template");
    }
    else
    {
        saveAsDraftBtn->setVisible(true);
        saveAsDraftBtn->setEnabled(tweetTextEdit->toPlainText().length() > 0);
        saveAsTemplateBtn->setVisible(true);
        saveAsTemplateBtn->setEnabled(tweetTextEdit->toPlainText().length() > 0);
        saveBtn->setVisible(false);
        deleteBtn->setVisible(false);
    }
}

void ComposeWidget::saveAsDraftBtnClicked()
{
    TweetDraft tweetDraft;
    tweetDraft.setId(TweetDraft::numDrafts + 1);
    tweetDraft.setText(tweetTextEdit->toHtml());
    dataStore->addTweetDraft(tweetDraft);
    tweetTextEdit->setHtml("");

    SettingsManager::getInstance()->saveTweetDrafts();

    Toast toast("Tweet saved as draft", Toast::ToastTypes::INFO, 2000);
    emit toastRequested(toast);
}

void ComposeWidget::saveAsTemplateBtnClicked()
{
    TweetTemplate tweetTemplate;
    tweetTemplate.setId(TweetTemplate::numTemplates + 1);
    tweetTemplate.setText(tweetTextEdit->toHtml());
    dataStore->addTweetTemplate(tweetTemplate);
    tweetTextEdit->setHtml("");

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

void TextEdit::keyPressEvent(QKeyEvent *e)
{
    if (toPlainText().length() >= 500 && e->key() != Qt::Key_Backspace && e->key() != Qt::Key_Delete)
    {
        // Prevent text longer than 500 characters
        e->accept();
    }
    else
    {
        QTextEdit::keyPressEvent(e);
    }
}
