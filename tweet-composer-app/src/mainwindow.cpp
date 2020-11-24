#include "mainwindow.h"
#include "settings.h"

#include <QGuiApplication>
#include <QMessageBox>

bool Settings::encryptDraftsOnDisk = false;
bool Settings::encryptTemplatesOnDisk = false;

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

    QAction *exitAction = new QAction("Exit");
    fileMenu->addAction(exitAction);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitAppTriggered()));

    QAction *settingsAction = new QAction("Settings");
    fileMenu->addAction(settingsAction);

    connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettingsDialogTriggered()));

    QMenu *helpMenu = new QMenu("Help");
    menuBar->addMenu(helpMenu);

    QAction *aboutAction = new QAction("About");
    helpMenu->addAction(aboutAction);

    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutDialogTriggered()));
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

void MainWindow::exitAppTriggered()
{
    QMessageBox::StandardButton result = QMessageBox::question(this, "Exit TweetComposer?", "Do you want to exit TweetComposer?");
    if (result == QMessageBox::Yes)
    {
        qApp->quit();
    }
}

void MainWindow::showAboutDialogTriggered()
{
    QMessageBox::about(
        this,
        "About TweetComposer",
        "Permission to use the source code according to the MIT License.\n\n© 2020 Chip Osur");
}

void MainWindow::showSettingsDialogTriggered()
{
    SettingsDialog dialog(this);
    if (dialog.exec())
    {

    }
}
