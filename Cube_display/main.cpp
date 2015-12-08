#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>
#include <string>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
