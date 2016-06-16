#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    return a.exec();
}
