#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    // Encode QString text in UTF-8 (default is UTF-16)
    QTextCodec *utf8Codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(utf8Codec);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
