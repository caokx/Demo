#include <QCoreApplication>
#include "a.h"
#include<QThread>
#include<QDebug>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);



    //moveToThread成功
    A* aa = new A;


    aa->begin();

    aa->subThread->start();






    return a.exec();








}
