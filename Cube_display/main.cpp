#include "mainwindow.h"
#include <QApplication>
#include "solver.cpp"
#include <string>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //string dataset = "LB DB RU DF LU BU RF RB UF RD DL LF DLB LFU FLD RDB FDR BLU BUR UFR";
    DebugWindow w;
    w.show();
    return a.exec();
}
