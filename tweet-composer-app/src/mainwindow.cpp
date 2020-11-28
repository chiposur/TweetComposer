#include "mainwindow.h"
#include <jsonserializer.h>
#include "settings.h"
#include "settingsmanager.h"

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

    dataStore = DataStore::getInstance();

    // Load entities from disk
    SettingsManager *settingsMgr = SettingsManager::getInstance();
    settingsMgr->loadTweetDrafts();
    settingsMgr->loadTweetTemplates();
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

    QAction *settingsAction = new QAction("Settings");
    fileMenu->addAction(settingsAction);

    fileMenu->addSeparator();

    QAction *importDraftsAction = new QAction("Import drafts from JSON");
    fileMenu->addAction(importDraftsAction);

    QAction *importTemplatesAction = new QAction("Import templates from JSON");
    fileMenu->addAction(importTemplatesAction);

    QAction *exportDraftsAction = new QAction("Export drafts to JSON");
    fileMenu->addAction(exportDraftsAction);

    QAction *exportTemplatesAction = new QAction("Export templates to JSON");
    fileMenu->addAction(exportTemplatesAction);

    fileMenu->addSeparator();

    QAction *exitAction = new QAction("Exit");
    fileMenu->addAction(exitAction);

    connect(importDraftsAction, SIGNAL(triggered()), this, SLOT(importDraftsFromJsonTriggered()));
    connect(importTemplatesAction, SIGNAL(triggered()), this, SLOT(importTemplatesFromJsonTriggered()));
    connect(exportDraftsAction, SIGNAL(triggered()), this, SLOT(exportDraftsToJsonTriggered()));
    connect(exportTemplatesAction, SIGNAL(triggered()), this, SLOT(exportTemplatesToJsonTriggered()));
    connect(settingsAction, SIGNAL(triggered()), this, SLOT(showSettingsDialogTriggered()));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(exitAppTriggered()));

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

    connect(
        composeWidget,
        SIGNAL(tweetDraftEdited(const TweetDraft &)),
        tweetDraftsWidget,
        SLOT(onTweetDraftEdited(const TweetDraft &)));

    connect(
        composeWidget,
        SIGNAL(tweetDraftDeleted(int)),
        tweetDraftsWidget,
        SLOT(onTweetDraftDeleted(int)));

    tweetTemplatesWidget = new TweetTemplatesWidget();
    tweetTemplatesWidget->setVisible(false);
    mainLayout->addWidget(tweetTemplatesWidget);

    connect(
        composeWidget,
        SIGNAL(tweetTemplateAdded(const TweetTemplate &)),
        tweetTemplatesWidget,
        SLOT(onTweetTemplateAdded(const TweetTemplate &)));

    connect(
        composeWidget,
        SIGNAL(tweetTemplateEdited(const TweetTemplate &)),
        tweetTemplatesWidget,
        SLOT(onTweetTemplateEdited(const TweetTemplate &)));

    connect(
        composeWidget,
        SIGNAL(tweetTemplateDeleted(int)),
        tweetTemplatesWidget,
        SLOT(onTweetTemplateDeleted(int)));

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
        tweetDraftsWidget,
        SIGNAL(editDraftRequested(int)),
        this,
        SLOT(onEditDraftRequested(int)));

    connect(
        tweetTemplatesWidget,
        SIGNAL(editTemplateRequested(int)),
        this,
        SLOT(onEditTemplateRequested(int)));

    connect(
        tweetTemplatesWidget,
        SIGNAL(backRequested()),
        this,
        SLOT(showComposeWidget()));

    // Hook up toast events
    connect(
        composeWidget,
        SIGNAL(toastRequested(const Toast &)),
        this,
        SLOT(onToastRequested(const Toast &)));

    connect(
        tweetDraftsWidget,
        SIGNAL(toastRequested(const Toast &)),
        this,
        SLOT(onToastRequested(const Toast &)));

    connect(
        tweetTemplatesWidget,
        SIGNAL(toastRequested(const Toast &)),
        this,
        SLOT(onToastRequested(const Toast &)));
}

void MainWindow::exportDraftsToJsonTriggered()
{
    QString json = JsonSerializer::serialize(*dataStore->getTweetDrafts());

    // TODO: write json file to disk
}

void MainWindow::exportTemplatesToJsonTriggered()
{
    QString json = JsonSerializer::serialize(*dataStore->getTweetTemplates());

    // TODO: write json file to disk
}

void MainWindow::importDraftsFromJsonTriggered()
{
    QString json;

    // TODO: load json file from disk

    QVector<TweetDraft> tweetDrafts;
    JsonSerializer::deserialize(tweetDrafts, json);

    if (tweetDrafts.count() > 0)
    {
        for (TweetDraft tweetDraft : tweetDrafts)
        {
            dataStore->addTweetDraft(tweetDraft);
        }
    }
}

void MainWindow::importTemplatesFromJsonTriggered()
{
    QString json;

    // TODO: load json file from disk

    QVector<TweetTemplate> tweetTemplates;
    JsonSerializer::deserialize(tweetTemplates, json);

    if (tweetTemplates.count() > 0)
    {
        for (TweetTemplate tweetTemplate : tweetTemplates)
        {
            dataStore->addTweetTemplate(tweetTemplate);
        }
    }
}

void MainWindow::showComposeWidget()
{
    composeWidget->setVisible(true);
    tweetDraftsWidget->setVisible(false);
    tweetTemplatesWidget->setVisible(false);
}

void MainWindow::showTweetDraftsWidget()
{
    composeWidget->setVisible(false);
    tweetDraftsWidget->setVisible(true);
    tweetTemplatesWidget->setVisible(false);
}

void MainWindow::showTweetTemplatesWidget()
{
    composeWidget->setVisible(false);
    tweetDraftsWidget->setVisible(false);
    tweetTemplatesWidget->setVisible(true);
}

void MainWindow::onEditDraftRequested(int draftId)
{
    TweetDraft tweetDraft;
    if (DataStore::getInstance()->getTweetDraftById(draftId, tweetDraft))
    {
        composeWidget->loadTweetDraft(tweetDraft);
        showComposeWidget();
    }
}

void MainWindow::onEditTemplateRequested(int templateId)
{
    TweetTemplate tweetTemplate;
    if (DataStore::getInstance()->getTweetTemplateById(templateId, tweetTemplate))
    {
        composeWidget->loadTweetTemplate(tweetTemplate);
        showComposeWidget();
    }
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
        SettingsManager::getInstance()->saveSettings();
    }
}

void MainWindow::onToastRequested(const Toast &/*toast*/)
{
    // TODO: display toast in bottom right corner of widget for toast duration, and
    // stack toasts if multiple are requested with overlapping durations
}
