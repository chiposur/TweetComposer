#include "mainwindow.h"
#include "jsonserializer.h"
#include "settings.h"
#include "settingsmanager.h"
#include "toastwidget.h"
#include "styles.h"

#include <QApplication>
#include <QFileDialog>
#include <QGuiApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("TweetComposer");
    setWindowIcon(APP_ICON);
    updateAppStyles();

    QWidget *mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    initAndConnectSingletons();
    createMenuBar();
    createMainLayout();
    loadSettings();
    loadEntities();

    // Set minimum size to startup size hint
    setMinimumSize(sizeHint());
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateAppStyles()
{
    QString appStyleSheet =
        Styles::MAIN_WINDOW_STYLE_SHEET +
        Styles::MENU_BAR_STYLE_SHEET +
        Styles::MENU_STYLE_SHEET +
        Styles::GROUPBOX_STYLE_SHEET +
        Styles::LINE_EDIT_STYLE_SHEET +
        Styles::COMBOBOX_STYLE_SHEET +
        Styles::BUTTON_STYLE_SHEET +
        Styles::CHECKBOX_STYLE_SHEET;

    qApp->setStyleSheet(appStyleSheet);
}

void MainWindow::loadSettings()
{
    settingsManager->loadSettings();

    if (Settings::persistWindowState)
    {
        QByteArray windowGeometry;
        settingsManager->loadWindowGeometry(windowGeometry);

        if (!restoreGeometry(windowGeometry))
        {
            settingsManager->saveWindowGeometry(saveGeometry());
        }
    }
}

void MainWindow::loadEntities()
{
    settingsManager->loadTweetDrafts();
    settingsManager->loadTweetTemplates();
}

void MainWindow::initAndConnectSingletons()
{
    dataStore = DataStore::getInstance();
    jsonSerializer = JsonSerializer::getInstance();
    settingsManager = SettingsManager::getInstance();

    // Connect DataStore singleton add/edit/delete signals to JsonSerializer singleton
    connect(
        dataStore,
        SIGNAL(tweetDraftAdded(const TweetDraft &)),
        jsonSerializer,
        SLOT(onTweetDraftAdded(const TweetDraft &)));

    connect(
        dataStore,
        SIGNAL(tweetDraftEdited(const TweetDraft &)),
        jsonSerializer,
        SLOT(onTweetDraftEdited(const TweetDraft &)));

    connect(
        dataStore,
        SIGNAL(tweetDraftDeleted(int)),
        jsonSerializer,
        SLOT(onTweetDraftDeleted(int)));

    connect(
        dataStore,
        SIGNAL(tweetTemplateAdded(const TweetTemplate &)),
        jsonSerializer,
        SLOT(onTweetTemplateAdded(const TweetTemplate &)));

    connect(
        dataStore,
        SIGNAL(tweetTemplateEdited(const TweetTemplate &)),
        jsonSerializer,
        SLOT(onTweetTemplateEdited(const TweetTemplate &)));

    connect(
        dataStore,
        SIGNAL(tweetTemplateDeleted(int)),
        jsonSerializer,
        SLOT(onTweetTemplateDeleted(int)));
}

void MainWindow::createMenuBar()
{
    QMenuBar *menuBar = new QMenuBar();
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
        dataStore,
        SIGNAL(tweetDraftAdded(const TweetDraft &)),
        tweetDraftsWidget,
        SLOT(onTweetDraftAdded(const TweetDraft &)));

    connect(
        dataStore,
        SIGNAL(tweetDraftEdited(const TweetDraft &)),
        tweetDraftsWidget,
        SLOT(onTweetDraftEdited(const TweetDraft &)));

    connect(
        dataStore,
        SIGNAL(tweetDraftDeleted(int)),
        tweetDraftsWidget,
        SLOT(onTweetDraftDeleted(int)));

    tweetTemplatesWidget = new TweetTemplatesWidget();
    tweetTemplatesWidget->setVisible(false);
    mainLayout->addWidget(tweetTemplatesWidget);

    connect(
        dataStore,
        SIGNAL(tweetTemplateAdded(const TweetTemplate &)),
        tweetTemplatesWidget,
        SLOT(onTweetTemplateAdded(const TweetTemplate &)));

    connect(
        dataStore,
        SIGNAL(tweetTemplateEdited(const TweetTemplate &)),
        tweetTemplatesWidget,
        SLOT(onTweetTemplateEdited(const TweetTemplate &)));

    connect(
        dataStore,
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
    bool success;
    QString json = jsonSerializer->tweetDraftsJson(success);

    static QString lastSelectedImportDir;
    lastSelectedImportDir =
        QFileDialog::getExistingDirectory(
            this,
            "Select export directory",
            lastSelectedImportDir,
            QFileDialog::ShowDirsOnly);

    QFile exportFile(QString("%1/tweetdrafts.json").arg(lastSelectedImportDir));
    if (exportFile.open(QFile::ReadWrite | QFile::Truncate))
    {
        exportFile.write(json.toUtf8());
    }
}

void MainWindow::exportTemplatesToJsonTriggered()
{
    bool success;
    QString json = jsonSerializer->tweetTemplatesJson(success);

    static QString lastSelectedImportDir;
    lastSelectedImportDir =
        QFileDialog::getExistingDirectory(
            this,
            "Select export directory",
            lastSelectedImportDir,
            QFileDialog::ShowDirsOnly);

    QFile exportFile(QString("%1/tweettemplates.json").arg(lastSelectedImportDir));
    if (exportFile.open(QFile::ReadWrite | QFile::Truncate))
    {
        exportFile.write(json.toUtf8());
    }
}

void MainWindow::importDraftsFromJsonTriggered()
{
    static QString lastSelectedImportDir;
    QString filename =
        QFileDialog::getOpenFileName(
            this,
            "Select import directory",
            lastSelectedImportDir);

    QFile selectedFile(filename);
    if (!selectedFile.open(QFile::ReadOnly))
    {
        QMessageBox::warning(
            this,
            "Could not open file",
            "Could not open file for reading, check that you have the appropriate permissions.");
        return;
    }

    lastSelectedImportDir = QFileInfo(filename).absoluteFilePath();
    QString json = selectedFile.readAll();

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
    static QString lastSelectedImportDir;
    QString filename =
        QFileDialog::getOpenFileName(
            this,
            "Select import directory",
            lastSelectedImportDir);

    QFile selectedFile(filename);
    if (!selectedFile.open(QFile::ReadOnly))
    {
        QMessageBox::warning(
            this,
            "Could not open file",
            "Could not open file for reading, check that you have the appropriate permissions.");
        return;
    }

    lastSelectedImportDir = QFileInfo(filename).absoluteFilePath();
    QString json = selectedFile.readAll();

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
    setWindowTitle("TweetComposer");
}

void MainWindow::showTweetDraftsWidget()
{
    composeWidget->setVisible(false);
    tweetDraftsWidget->setVisible(true);
    tweetTemplatesWidget->setVisible(false);
    setWindowTitle("TweetComposer - Drafts");
}

void MainWindow::showTweetTemplatesWidget()
{
    composeWidget->setVisible(false);
    tweetDraftsWidget->setVisible(false);
    tweetTemplatesWidget->setVisible(true);
    setWindowTitle("TweetComposer - Templates");
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

void MainWindow::onToastRequested(const Toast &toast)
{
    ToastWidget *toastWidget = new ToastWidget(toast, this);
    connect(toastWidget, SIGNAL(toastWidgetExpired(int)), this, SLOT(onToastWidgetExpired(int)));
    topToastHeight += TOAST_MARGIN_PX + toastWidget->height();
    int toastX = width() - toastWidget->width() - TOAST_MARGIN_PX;
    int toastY = height() - topToastHeight;
    toastWidget->move(toastX, toastY);
    toastWidget->setVisible(true);
}

void MainWindow::onToastWidgetExpired(int height)
{
    topToastHeight -= height + TOAST_MARGIN_PX;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (Settings::persistWindowState)
    {
        settingsManager->saveWindowGeometry(saveGeometry());
    }

    QMainWindow::closeEvent(event);
}
