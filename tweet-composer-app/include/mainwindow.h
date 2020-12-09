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
#include "settingsmanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void resized(QResizeEvent *event);

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
    void onToastWidgetExpired(int height);

protected:
    void resizeEvent(QResizeEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    void createMenuBar();
    void createMainLayout();
    void initAndConnectSingletons();
    void loadEntitiesFromDisk();

    DataStore *dataStore;
    JsonSerializer *jsonSerializer;
    SettingsManager *settingsManager;

    QVBoxLayout *mainLayout;
    ComposeWidget *composeWidget;
    TweetDraftsWidget *tweetDraftsWidget;
    TweetTemplatesWidget *tweetTemplatesWidget;

    int topToastHeight = 0;

    static const int TOAST_MARGIN_PX = 8;

    const QIcon APP_ICON = QIcon(QPixmap(":/images/green-twitter-logo.ico"));
};
#endif // MAINWINDOW_H
