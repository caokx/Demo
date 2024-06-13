#include <QtCore/QCoreApplication>
#include <iostream>
#include <QDebug>
#include <QThread>
#include "libxl.h"
#include "QSimpleExcel.h"
#include <QtConcurrent/QtConcurrent>
#include <QMutex>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QSimpleExcel book("test", 0);   //��excel��sheet0
    QFuture<bool> f1 = QtConcurrent::run(&book, &QSimpleExcel::write, 0, 0, QString("hello"));
    QThread::sleep(1);
    if (f1.result() == true) { //д��excel�ɹ�
        qDebug() << "success";
    }
    else {  //д��ʧ��
        //��¼д��ʧ�ܵ�����
        qDebug() << "failure";
    }
    f1.waitForFinished();

    for (int i = 0; i < 10; i++) {
        book.write(0, i, QString::number(i));
    }
    





    return a.exec();

}

#if 0
#include <iostream>
#include <QDebug>
#include <QThread>
#include "libxl.h"
#include "QSimpleExcel.h"

int main()
{
    QSimpleExcel book("test", 0);
    //QSimpleExcel book("test", "sheet0");
    //book.addSheet("sheet2");
    //book.insertSheet(0, "aaaa");
    //book.deleteSheet(0);
    //book.write(2, 0, "hello");
    //book.writeRed(2, 3, "12");
    //book.writeRow(4, 2, { "hello", "world", "jack", "Rose" });
    //book.writeCol(1, 1, { "hello", "world", "jack", "Rose" });
    //qDebug() << book.read(2, 2);
    //qDebug() << book.read(0, 0);
    //qDebug() << book.read(2, 1);
    //QThread thread;
    //QThread::connect(&thread, &QThread::started, &book, &QSimpleExcel::writeCol);
    //book.moveToThread(&thread);
    //thread.start();
}
#endif