#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QVBoxLayout>

#include "composewidget.h"
#include "tweetdraftswidget.h"
#include "tweettemplateswidget.h"

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

private:
    void createMenuBar();
    void createMainLayout();

    QVBoxLayout *mainLayout;
    ComposeWidget *composeWidget;
    TweetDraftsWidget *tweetDraftsWidget;
    TweetTemplatesWidget *tweetTemplatesWidget;

    const QIcon APP_ICON = QIcon(QPixmap(":/images/green-twitter-logo.ico"));
};
#endif // MAINWINDOW_H
