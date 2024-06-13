#include "a.h"
#include "b.h"
#include <QThread>
#include <QDebug>


A::A():b(new B)
  ,subThread(new QThread)
{

}


void A::begin(){



//  qDebug() << "ThreadId=" << QThread::currentThreadId();
    b->moveToThread(subThread);
    QThread::connect(subThread, &QThread::started, b, &B::test);
    subThread->start();
    QThread::sleep(1);
    QString qs = "68 17 00 43 45 AA AA AA AA AA AA 00 5B 4F 05 01 D0 40 01 02 00 00 2E 46 16";
    QStringList qsl = qs.split(" ");
    char tmp[512];
    int len = qsl.length();
    for(int i=0; i<len; i++){
        tmp[i] = qsl[i].toInt(nullptr, 16);
    }
//    aMutex.lock();
    gMutex.lock();
    b->port->write(tmp, len);
    QByteArray res;
    res.clear();
    qDebug() << "main thread is waiting";
    if(b->port->waitForReadyRead(3000)){
        res = b->port->readAll();
        while(b->port->waitForReadyRead(300)){
            res += b->port->readAll();
        }
    }
    qDebug() << res;
    qDebug() << "main thread is over";
//    aMutex.unlock();
    gMutex.lock();


}



