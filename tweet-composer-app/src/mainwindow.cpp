#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("TweetComposer");
    setWindowIcon(APP_ICON);

    QWidget *mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    createMenuBar();
    createMainLayout();
}

MainWindow::~MainWindow()
{
}

void MainWindow::createMenuBar()
{
    QMenuBar *menuBar = new QMenuBar(this);
    setMenuBar(menuBar);

    QMenu *fileMenu = new QMenu("File");
    menuBar->addMenu(fileMenu);

    QMenu *helpMenu = new QMenu("Help");
    menuBar->addMenu(helpMenu);
}

void MainWindow::createMainLayout()
{
    mainLayout = new QVBoxLayout();
    centralWidget()->setLayout(mainLayout);

    composeWidget = new ComposeWidget();
    mainLayout->addWidget(composeWidget);

    tweetDraftsWidget = new TweetDraftsWidget();
    tweetDraftsWidget->setVisible(false);
    mainLayout->addWidget(tweetDraftsWidget);

    connect(
        composeWidget,
        SIGNAL(tweetDraftAdded(const TweetDraft &)),
        tweetDraftsWidget,
        SLOT(onTweetDraftAdded(const TweetDraft &)));

    tweetTemplatesWidget = new TweetTemplatesWidget();
    tweetTemplatesWidget->setVisible(false);
    mainLayout->addWidget(tweetTemplatesWidget);

    connect(
        composeWidget,
        SIGNAL(tweetTemplateAdded(const TweetTemplate &)),
        tweetTemplatesWidget,
        SLOT(onTweetTemplateAdded(const TweetTemplate &)));

    // Hook up events for changing views
    connect(
        composeWidget,
        SIGNAL(showTweetDrafts()),
        this,
        SLOT(showTweetDraftsWidget()));

    connect(
        composeWidget,
        SIGNAL(showTweetTemplates()),
        this,
        SLOT(showTweetTemplatesWidget()));

    connect(
        tweetDraftsWidget,
        SIGNAL(backRequested()),
        this,
        SLOT(showComposeWidget()));

    connect(
        tweetTemplatesWidget,
        SIGNAL(backRequested()),
        this,
        SLOT(showComposeWidget()));
}

void MainWindow::showComposeWidget()
{
    composeWidget->setEnabled(true);
    tweetDraftsWidget->setVisible(false);
    tweetTemplatesWidget->setVisible(false);
}

void MainWindow::showTweetDraftsWidget()
{
    composeWidget->setEnabled(false);
    tweetDraftsWidget->setVisible(true);
    tweetTemplatesWidget->setVisible(false);
}

void MainWindow::showTweetTemplatesWidget()
{
    composeWidget->setEnabled(false);
    tweetDraftsWidget->setVisible(false);
    tweetTemplatesWidget->setVisible(true);
}
