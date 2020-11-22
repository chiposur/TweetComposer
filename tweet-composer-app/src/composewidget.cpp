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
    toolButtonsLayout->addWidget(boldToolButton);

    connect(boldToolButton, SIGNAL(clicked()), this, SLOT(boldTriggered()));

    italicToolButton = new QToolButton();
    italicToolButton->setText("I");
    italicToolButton->setCheckable(true);
    toolButtonsLayout->addWidget(italicToolButton);

    connect(italicToolButton, SIGNAL(clicked()), this, SLOT(italicTriggered()));

    underlineToolButton = new QToolButton();
    underlineToolButton->setText("U");
    underlineToolButton->setCheckable(true);
    toolButtonsLayout->addWidget(underlineToolButton);

    connect(underlineToolButton, SIGNAL(clicked()), this, SLOT(underlineTriggered()));

    toolButtonsLayout->addStretch();

    tweetTextEdit = new QTextEdit();
    tweetTextEdit->setPlaceholderText("Compose tweet...");
    mainLayout->addWidget(tweetTextEdit);
}

void ComposeWidget::boldTriggered()
{
    tweetTextEdit->setFontWeight(tweetTextEdit->fontWeight() == QFont::Bold ? QFont::Normal : QFont::Bold);
}

void ComposeWidget::italicTriggered()
{
    tweetTextEdit->setFontItalic(!tweetTextEdit->fontItalic());
}

void ComposeWidget::underlineTriggered()
{
    tweetTextEdit->setFontUnderline(!tweetTextEdit->fontUnderline());
}
