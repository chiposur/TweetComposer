#include <QAction>

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

    toolButtonsLayout->addStretch();

    tweetTextEdit = new QPlainTextEdit();
    tweetTextEdit->setPlaceholderText("Compose tweet...");
    mainLayout->addWidget(tweetTextEdit);
}

void ComposeWidget::boldTriggered()
{
    isBold = !isBold;
    QTextCursor cursor = tweetTextEdit->textCursor();
    QTextCharFormat format;
    setCharFormat(format);
    cursor.setCharFormat(format);
    tweetTextEdit->setTextCursor(cursor);
}

void ComposeWidget::italicTriggered()
{
    isItalic = !isItalic;
    QTextCursor cursor = tweetTextEdit->textCursor();
    QTextCharFormat format;
    setCharFormat(format);
    cursor.setCharFormat(format);
    tweetTextEdit->setTextCursor(cursor);
}

void ComposeWidget::underlineTriggered()
{
    isUnderline = !isUnderline;
    QTextCursor cursor = tweetTextEdit->textCursor();
    QTextCharFormat format;
    setCharFormat(format);
    cursor.setCharFormat(format);
    tweetTextEdit->setTextCursor(cursor);
}

void ComposeWidget::setCharFormat(QTextCharFormat &format)
{
    format.setFontWeight(isBold ? QFont::Bold : QFont::Normal);
    format.setFontItalic(isItalic);
    format.setFontUnderline(isUnderline);
}
