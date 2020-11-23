#include <QAction>
#include <QClipboard>
#include <QFont>
#include <QGuiApplication>
#include <QPushButton>
#include <QSpacerItem>

#include "composewidget.h"

ComposeWidget::ComposeWidget(QWidget *parent) : QWidget(parent)
{
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
    fontFamilies << "Times";
    fontFamilies << "Helvetica";
    fontFamiliesComboBox->addItems(fontFamilies);
    toolButtonsLayout->addWidget(fontFamiliesComboBox);

    connect(fontFamiliesComboBox, SIGNAL(currentTextChanged(const QString &)), this, SLOT(onCurrentTextChanged(const QString &)));

    fontFamily = fontFamilies.first();

    toolButtonsLayout->addStretch();

    tweetTextEdit = new QPlainTextEdit();
    tweetTextEdit->setPlaceholderText("Compose tweet...");
    mainLayout->addWidget(tweetTextEdit);

    connect(tweetTextEdit, SIGNAL(textChanged()), this, SLOT(onTextChanged()));

    QHBoxLayout *editorBottomLayout = new QHBoxLayout();
    toolButtonsLayout->setSpacing(0);
    toolButtonsLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addLayout(editorBottomLayout);

    QPushButton *copyButton = new QPushButton("Copy");
    editorBottomLayout->addWidget(copyButton);

    connect(copyButton, SIGNAL(clicked()), this, SLOT(onCopyClicked()));

    editorBottomLayout->addStretch();

    charsRemainingLabel = new QLabel();
    editorBottomLayout->addWidget(charsRemainingLabel);

    setFont();
}

void ComposeWidget::setFont()
{
    QFont font(
        fontFamily == "Times" ? "Times New Roman" : "Helvetica [Cronyx]",
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
}

void ComposeWidget::onCopyClicked()
{
    QGuiApplication::clipboard()->setText(tweetTextEdit->toPlainText());
}

void ComposeWidget::onCurrentTextChanged(const QString &text)
{
    fontFamily = text;
    setFont();
}
