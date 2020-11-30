#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QVBoxLayout>

#include "composewidget.h"
#include "tweetdraftswidget.h"
#include "tweettemplateswidget.h"
#include "settingsdialog.h"
#include "toast.h"
#include "datastore.h"
#include "jsonserializer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void showComposeWidget();
    void showTweetDraftsWidget();
    void showTweetTemplatesWidget();
    void exitAppTriggered();
    void showAboutDialogTriggered();
    void showSettingsDialogTriggered();
    void exportDraftsToJsonTriggered();
    void exportTemplatesToJsonTriggered();
    void importDraftsFromJsonTriggered();
    void importTemplatesFromJsonTriggered();
    void onToastRequested(const Toast &toast);
    void onEditDraftRequested(int draftId);
    void onEditTemplateRequested(int templateId);

private:
    void createMenuBar();
    void createMainLayout();

    DataStore *dataStore;
    JsonSerializer *jsonSerializer;

    QVBoxLayout *mainLayout;
    ComposeWidget *composeWidget;
    TweetDraftsWidget *tweetDraftsWidget;
    TweetTemplatesWidget *tweetTemplatesWidget;

    const QIcon APP_ICON = QIcon(QPixmap(":/images/green-twitter-logo.ico"));
};
#endif // MAINWINDOW_H
