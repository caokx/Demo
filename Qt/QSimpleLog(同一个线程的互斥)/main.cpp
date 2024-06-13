#include <QtCore/QCoreApplication>
#include "QSimpleLog.h"




int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSimpleLog* log = new QSimpleLog("log1.log");
    log->clear();   
    log->start(); 
    log->write("hello world");
    log->write("hello 1");
    log->write("hello 2");
    log->write("hello 3");
    return a.exec();
}
