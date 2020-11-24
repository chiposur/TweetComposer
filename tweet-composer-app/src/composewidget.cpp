#include <QAction>
#include <QClipboard>
#include <QFont>
#include <QGuiApplication>
#include <QSpacerItem>

#include "composewidget.h"
#include "settingsmanager.h"

ComposeWidget::ComposeWidget(QWidget *parent) : QWidget(parent)
{
    SettingsManager *settingsMgr = SettingsManager::getInstance();
    tweetDrafts = settingsMgr->getTweetDrafts();
    tweetTemplates = settingsMgr->getTweetTemplates();

    mainLayout = new QVBoxLayout();
    setLayout(mainLayout);

    toolButtonsLayout = new QHBoxLayout();
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
    fontFamilies << "Default font";
    fontFamilies << "Times";
    fontFamilies << "Helvetica";
    fontFamiliesComboBox->addItems(fontFamilies);
    toolButtonsLayout->addWidget(fontFamiliesComboBox);

    connect(fontFamiliesComboBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onCurrentTextChanged(const QString &)));

    fontFamily = fontFamilies.first();

    toolButtonsLayout->addStretch();

    tweetTextEdit = new PlainTextEdit();
    tweetTextEdit->setPlaceholderText("Compose tweet...");
    mainLayout->addWidget(tweetTextEdit);

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

    setFont();
    updateBtnStates();
}

void ComposeWidget::setFont()
{
    QString fontFamilyStr;

    if (fontFamily == "Times") fontFamilyStr = "Times New Roman";
    else if (fontFamily == "Helvetica") fontFamilyStr = "Helvetica [Cronyx]";
    else fontFamilyStr = QGuiApplication::font().family();

    QFont font(
        fontFamilyStr,
        tweetTextEdit->font().pointSize(),
        isBold ? QFont::Bold : QFont::Normal,
        isItalic);
    font.setUnderline(isUnderline);

    QTextCursor textCursor = tweetTextEdit->textCursor();
    QTextCharFormat charFormat = textCursor.charFormat();
    charFormat.setFont(font);
    textCursor.setCharFormat(charFormat);

    tweetTextEdit->setTextCursor(textCursor);
}

void ComposeWidget::boldTriggered()
{
    isBold = !isBold;
    setFont();
}

void ComposeWidget::italicTriggered()
{
    isItalic = !isItalic;
    setFont();
}

void ComposeWidget::underlineTriggered()
{
    isUnderline = !isUnderline;
    setFont();
}

void ComposeWidget::onTextChanged()
{
    // Set chars remaining label
    QString charsRemainingText;
    int charsRemaining = MAX_TWEET_LENGTH - tweetTextEdit->toPlainText().length();
    if (charsRemaining <=  CHARS_REMAINING_LIMIT)
    {
        charsRemainingText = QString::number(charsRemaining);
        charsRemainingLabel->setStyleSheet(QString("QLabel { color: %1; }").arg(charsRemaining >= 0 ? "black" : "red"));
    }

    charsRemainingLabel->setText(charsRemainingText);

    updateBtnStates();
}

void ComposeWidget::onCurrentTextChanged(const QString &text)
{
    fontFamily = text;
    setFont();
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
    TweetDraft *tweetDraft = new TweetDraft();
    tweetDraft->setText(tweetTextEdit->toPlainText());
    tweetDrafts->append(tweetDraft);
    tweetTextEdit->setPlainText("");

    emit tweetDraftAdded(*tweetDraft);
}

void ComposeWidget::saveAsTemplateBtnClicked()
{
    TweetTemplate *tweetTemplate = new TweetTemplate();
    tweetTemplate->setText(tweetTextEdit->toPlainText());
    tweetTemplates->append(tweetTemplate);
    tweetTextEdit->setPlainText("");

    emit tweetTemplateAdded(*tweetTemplate);
}

void ComposeWidget::saveBtnClicked()
{
    // TODO: save tweet draft or template by modifying its text member
    // then clear compose widget and reset its state

    // Perist changes
    if (isDraft())
    {
        SettingsManager::getInstance()->saveTweetDrafts();
    }
    else
    {
        SettingsManager::getInstance()->saveTweetTemplates();
    }
}

void ComposeWidget::deleteBtnClicked()
{
    // TODO: delete tweet draft or template from the appropriate QList

    // Perist changes
    if (isDraft())
    {
        SettingsManager::getInstance()->saveTweetDrafts();
    }
    else
    {
        SettingsManager::getInstance()->saveTweetTemplates();
    }
}

void PlainTextEdit::keyPressEvent(QKeyEvent *e)
{
    if (toPlainText().length() >= 500 && e->key() != Qt::Key_Backspace && e->key() != Qt::Key_Delete)
    {
        // Prevent text longer than 500 characters
        e->accept();
    }
    else
    {
        QPlainTextEdit::keyPressEvent(e);
    }
}
