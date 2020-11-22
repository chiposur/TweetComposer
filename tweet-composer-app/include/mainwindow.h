#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QVBoxLayout>

#include "composewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void createMenuBar();
    void createMainLayout();

    QVBoxLayout *mainLayout;
    ComposeWidget *composeWidget;

    const QIcon APP_ICON = QIcon(QPixmap(":/images/green-twitter-logo.ico"));
};
#endif // MAINWINDOW_H
