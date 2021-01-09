#include <QAction>
#include <QApplication>
#include <QClipboard>
#include <QFont>
#include <QGuiApplication>
#include <QMessageBox>
#include <QSpacerItem>

#include <string>

#include "composewidget.h"
#include "settings.h"
#include "settingsmanager.h"
#include "styles.h"

const QString ComposeWidget::MATH_SANS_BOLD_ALPHABET = QString::fromUtf8("𝗮𝗯𝗰𝗱𝗲𝗳𝗴𝗵𝗶𝗷𝗸𝗹𝗺𝗻𝗼𝗽𝗾𝗿𝘀𝘁𝘂𝘃𝘄𝘅𝘆𝘇𝗔𝗕𝗖𝗗𝗘𝗙𝗚𝗛𝗜𝗝𝗞𝗟𝗠𝗡𝗢𝗣𝗤𝗥𝗦𝗧𝗨𝗩𝗪𝗫𝗬𝗭𝟬𝟭𝟮𝟯𝟰𝟱𝟲𝟳𝟴𝟵");
const QString ComposeWidget::MATH_SANS_ITALIC_ALPHABET = QString::fromUtf8("𝘢𝘣𝘤𝘥𝘦𝘧𝘨𝘩𝘪𝘫𝘬𝘭𝘮𝘯𝘰𝘱𝘲𝘳𝘴𝘵𝘶𝘷𝘸𝘹𝘺𝘻𝘈𝘉𝘊𝘋𝘌𝘍𝘎𝘏𝘐𝘑𝘒𝘓𝘔𝘕𝘖𝘗𝘘𝘙𝘚𝘛𝘜𝘝𝘞𝘟𝘠𝘡0123456789");
const QString ComposeWidget::MATH_SANS_BOLD_ITALIC_ALPHABET = QString::fromUtf8("𝙖𝙗𝙘𝙙𝙚𝙛𝙜𝙝𝙞𝙟𝙠𝙡𝙢𝙣𝙤𝙥𝙦𝙧𝙨𝙩𝙪𝙫𝙬𝙭𝙮𝙯𝘼𝘽𝘾𝘿𝙀𝙁𝙂𝙃𝙄𝙅𝙆𝙇𝙈𝙉𝙊𝙋𝙌𝙍𝙎𝙏𝙐𝙑𝙒𝙓𝙔𝙕𝟬𝟭𝟮𝟯𝟰𝟱𝟲𝟳𝟴𝟵");
const QString ComposeWidget::MATH_SERIF_BOLD_ALPHABET = QString::fromUtf8("𝐚𝐛𝐜𝐝𝐞𝐟𝐠𝐡𝐢𝐣𝐤𝐥𝐦𝐧𝐨𝐩𝐪𝐫𝐬𝐭𝐮𝐯𝐰𝐱𝐲𝐳𝐀𝐁𝐂𝐃𝐄𝐅𝐆𝐇𝐈𝐉𝐊𝐋𝐌𝐍𝐎𝐏𝐐𝐑𝐒𝐓𝐔𝐕𝐖𝐗𝐘𝐙𝟎𝟏𝟐𝟑𝟒𝟓𝟔𝟕𝟖𝟗");
const QString ComposeWidget::MATH_SERIF_ITALIC_ALPHABET = QString::fromUtf8("𝘢𝘣𝘤𝘥𝘦𝘧𝘨𝘩𝘪𝘫𝘬𝘭𝘮𝘯𝘰𝘱𝘲𝘳𝘴𝘵𝘶𝘷𝘸𝘹𝘺𝘻𝘈𝘉𝘊𝘋𝘌𝘍𝘎𝘏𝘐𝘑𝘒𝘓𝘔𝘕𝘖𝘗𝘘𝘙𝘚𝘛𝘜𝘝𝘞𝘟𝘠𝘡0123456789");
const QString ComposeWidget::MATH_SERIF_BOLD_ITALIC_ALPHABET = QString::fromUtf8("𝙖𝙗𝙘𝙙𝙚𝙛𝙜𝙝𝙞𝙟𝙠𝙡𝙢𝙣𝙤𝙥𝙦𝙧𝙨𝙩𝙪𝙫𝙬𝙭𝙮𝙯𝘼𝘽𝘾𝘿𝙀𝙁𝙂𝙃𝙄𝙅𝙆𝙇𝙈𝙉𝙊𝙋𝙌𝙍𝙎𝙏𝙐𝙑𝙒𝙓𝙔𝙕𝟎𝟏𝟐𝟑𝟒𝟓𝟔𝟕𝟖𝟗");

ComposeWidget::ComposeWidget(QWidget *parent) : QWidget(parent)
{
    dataStore = DataStore::getInstance();
    tweetDrafts = dataStore->getTweetDrafts();
    tweetTemplates = dataStore->getTweetTemplates();

    twitterApiClient = TwitterApiClient::getInstance();
    connect(
        twitterApiClient,
        SIGNAL(updateStatusFinished(RequestId, TwitterApiClient::ResultType)),
        this,
        SLOT(onUpdateStatusFinished(RequestId, TwitterApiClient::ResultType)));

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

    boldToggleButton = new BoldToggleButton();
    boldToggleButton->setCheckable(true);
    toolButtonsLayout->addWidget(boldToggleButton);

    connect(boldToggleButton, SIGNAL(toggled(bool)), this, SLOT(boldToggled(bool)));

    italicToggleButton = new ItalicToggleButton();
    italicToggleButton->setCheckable(true);
    toolButtonsLayout->addWidget(italicToggleButton);

    connect(italicToggleButton, SIGNAL(toggled(bool)), this, SLOT(italicToggled(bool)));

    toolButtonsLayout->addSpacerItem(new QSpacerItem(8, 0));

    fontFamiliesComboBox = new QComboBox();
    toolButtonsLayout->addWidget(fontFamiliesComboBox);
    fontFamiliesComboBox->setItemDelegate(new ComboBoxItemDelegate(fontFamiliesComboBox));
    QStringList fontFamilies;
    fontFamilies << "Helvetica"; // Helvetica is default twitter font
    fontFamilies << "Times";
    fontFamiliesComboBox->addItems(fontFamilies);

    QFont font;
    font.setFamily("Helvetica");
    fontFamiliesComboBox->setItemData(0, font, Qt::FontRole);
    font.setFamily("Times New Roman");
    fontFamiliesComboBox->setItemData(1, font, Qt::FontRole);

    connect(fontFamiliesComboBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onCurrentTextChanged(const QString &)));

    fontFamily = getFontFamilyName(fontFamilies.first());

    toolButtonsLayout->addStretch();

    tweetTextEdit = new TweetTextEdit();
    mainLayout->addWidget(tweetTextEdit);
    tweetTextEdit->setPlaceholderText("Compose tweet...");

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
    tweetBtn = new TwitterButton("Tweet");

    editorBottomLayout->addWidget(saveAsDraftBtn);
    editorBottomLayout->addWidget(saveAsTemplateBtn);
    editorBottomLayout->addWidget(saveBtn);
    editorBottomLayout->addWidget(deleteBtn);
    editorBottomLayout->addStretch();
    editorBottomLayout->addWidget(tweetBtn);

    charsRemainingLabel = new QLabel();
    editorBottomLayout->addWidget(charsRemainingLabel);

    connect(saveAsDraftBtn, SIGNAL(clicked()), this, SLOT(saveAsDraftBtnClicked()));
    connect(saveAsTemplateBtn, SIGNAL(clicked()), this, SLOT(saveAsTemplateBtnClicked()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveBtnClicked()));
    connect(deleteBtn, SIGNAL(clicked()), this, SLOT(deleteBtnClicked()));
    connect(tweetBtn, SIGNAL(clicked()), this, SLOT(tweetBtnClicked()));

    mainLayout->addStretch();

    updateBtnStates();
    setFont();

    connect(
        tweetTextEdit->document(),
        SIGNAL(contentsChange(int, int, int)),
        this,
        SLOT(onTweetTextDocumentContentsChange(int, int, int)));
}

void ComposeWidget::onTweetTextDocumentContentsChange(int position, int charsRemoved, int charsAdded)
{
    Q_UNUSED(charsRemoved)

    if (charsAdded == 0 || !(isBold || isItalic))
    {
        return;
    }

    disconnect(
        tweetTextEdit->document(),
        SIGNAL(contentsChange(int, int, int)),
        this,
        SLOT(onTweetTextDocumentContentsChange(int, int, int)));

    QString tweetText = tweetTextEdit->document()->toPlainText();
    QString replacementText;
    replacementText.append(tweetText.left(position).toUtf8());
    int index = position;
    while (index < position + charsAdded)
    {
        QChar currentChar = tweetText[index];

        bool isLatinOrDigit = (currentChar >= 'a' && currentChar <= 'z') || (currentChar >= 'A' && currentChar <= 'Z')
            || currentChar.isDigit();
        if (!isLatinOrDigit || currentChar.isSurrogate())
        {
            replacementText.append(currentChar);
            ++index;
            continue;
        }

        QString alphabet;
        if (fontFamily == "Helvetica" && isBold && isItalic)
        {
            alphabet = MATH_SANS_BOLD_ITALIC_ALPHABET;
        }
        else if (fontFamily == "Helvetica" && isBold)
        {
            alphabet = MATH_SANS_BOLD_ALPHABET;
        }
        else if (fontFamily == "Helvetica")
        {
            alphabet = MATH_SANS_ITALIC_ALPHABET;
        }
        else if (isBold && isItalic)
        {
            alphabet = MATH_SERIF_BOLD_ITALIC_ALPHABET;
        }
        else if (isBold)
        {
            alphabet = MATH_SERIF_BOLD_ALPHABET;
        }
        else
        {
            alphabet = MATH_SERIF_ITALIC_ALPHABET;
        }

        // Math font has a width of 4 bytes comprising two surrogate QChar's
        int newCharIndex;
        if (currentChar.isLetter())
        {
            newCharIndex = ((currentChar.toLower().toLatin1() - 'a') + (currentChar.isUpper() ? 26 : 0)) * 2;
        }
        else
        {
            newCharIndex = ((currentChar.toLatin1() - '0') + 52) * 2;
        }

        QStringRef newChar(&alphabet, newCharIndex, 2);
        replacementText.append(newChar);
        ++index;
    }

    tweetText.remove(position, charsAdded);
    tweetText.insert(position, replacementText);
    tweetTextEdit->document()->setPlainText(replacementText);

    connect(
        tweetTextEdit->document(),
        SIGNAL(contentsChange(int, int, int)),
        this,
        SLOT(onTweetTextDocumentContentsChange(int, int, int)));
}

void ComposeWidget::setFont()
{
    QTextCharFormat charFormat;
    charFormat.setFontFamily(fontFamily);
    tweetTextEdit->setCurrentCharFormat(charFormat);
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
    setFont();
}

void ComposeWidget::italicToggled(bool checked)
{
    isItalic = checked;
    setFont();
}

void ComposeWidget::onTextChanged()
{
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
    fontFamily = getFontFamilyName(text);
    QFont font = fontFamiliesComboBox->font();
    font.setFamily(fontFamily);
    fontFamiliesComboBox->setFont(font);
    setFont();
}

void ComposeWidget::updateBtnStates()
{
    int tweetLength = tweetTextLength();
    int tweetHasText = tweetLength > 0;
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

    tweetBtn->setEnabled(tweetHasText && tweetLength <= Styles::TWEET_MAX_LENGTH);
}

void ComposeWidget::saveAsDraftBtnClicked()
{
    TweetDraft tweetDraft;
    tweetDraft.setId(TweetDraft::numDrafts + 1);
    tweetDraft.setText(tweetTextEdit->toPlainText());
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
    tweetTemplate.setText(tweetTextEdit->toPlainText());
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
    if (isDraft())
    {
        if (dataStore->getDraftIdIndex(draftId) > -1)
        {
            TweetDraft tweetDraft;
            if (dataStore->getTweetDraftById(draftId, tweetDraft))
            {
                tweetDraft.setText(tweetTextEdit->toPlainText());
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
            tweetTemplate.setText(tweetTextEdit->toPlainText());
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

void ComposeWidget::tweetBtnClicked()
{
    bool credentialsNotSet = Settings::apiKey.isEmpty()
        || Settings::apiSecret.isEmpty()
        || Settings::accessToken.isEmpty()
        || Settings::accessTokenSecret.isEmpty();
    if (credentialsNotSet)
    {
        QMessageBox::warning(
            this,
            "Credentials not set",
            "Twitter API credentials not set. Set them in the Settings dialog to use this feature.");
        return;
    }

    QApplication::setOverrideCursor(Qt::WaitCursor);
    twitterApiClient->updateStatus(tweetTextEdit->toPlainText());
}

void ComposeWidget::onUpdateStatusFinished(RequestId id, TwitterApiClient::ResultType result)
{
    Q_UNUSED(id);
    QApplication::restoreOverrideCursor();

    Toast toast;
    if (result == TwitterApiClient::ResultType::OK)
    {
        toast.setText("Tweet posted to Twitter");
    }
    else if (result == TwitterApiClient::ResultType::TIMEOUT)
    {
        toast.setText("Tweet post timed out");
        toast.setToastType(Toast::ToastTypes::ERROR);
    }
    else if (result == TwitterApiClient::ResultType::UNKNOWN_NETWORK_ERROR)
    {
        toast.setText("Tweet failed to post to Twitter: unknown network error");
        toast.setToastType(Toast::ToastTypes::ERROR);
    }
    else if (result == TwitterApiClient::ResultType::PROTOCOL_INVALID_OPERATION_ERROR)
    {
        toast.setText("Tweet failed to post to Twitter: protocol invalid operation error");
        toast.setToastType(Toast::ToastTypes::ERROR);
    }
    else
    {
        toast.setText("Tweet failed to post to Twitter");
        toast.setToastType(Toast::ToastTypes::ERROR);
    }

    emit toastRequested(toast);
}

void ComposeWidget::clearTweetEdit()
{
    tweetTextEdit->setPlainText("");
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

    disconnect(
        tweetTextEdit->document(),
        SIGNAL(contentsChange(int, int, int)),
        this,
        SLOT(onTweetTextDocumentContentsChange(int, int, int)));

    tweetTextEdit->setPlainText(tweetDraft.getText());
    nameLineEdit->setText(tweetDraft.getName());
    draftId = tweetDraft.getId();
    templateId = -1;
    updateBtnStates();

    connect(
        tweetTextEdit->document(),
        SIGNAL(contentsChange(int, int, int)),
        this,
        SLOT(onTweetTextDocumentContentsChange(int, int, int)));
}

void ComposeWidget::loadTweetTemplate(const TweetTemplate &tweetTemplate)
{
    if (checkAndPromptIfDirty())
    {
        return;
    }

    disconnect(
        tweetTextEdit->document(),
        SIGNAL(contentsChange(int, int, int)),
        this,
        SLOT(onTweetTextDocumentContentsChange(int, int, int)));

    tweetTextEdit->setPlainText(tweetTemplate.getText());
    nameLineEdit->setText(tweetTemplate.getName());
    templateId = tweetTemplate.getId();
    draftId = -1;
    updateBtnStates();

    connect(
        tweetTextEdit->document(),
        SIGNAL(contentsChange(int, int, int)),
        this,
        SLOT(onTweetTextDocumentContentsChange(int, int, int)));
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
