#include "mainwindow.h"
#include "a.h"
#include <QApplication>
#include<QMutex>

QMutex gMutex;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    A* a_ = new A;
    a_->begin();
    return a.exec();
}
