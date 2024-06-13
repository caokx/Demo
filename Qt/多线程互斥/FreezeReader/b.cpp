#include "b.h"
#include <QDebug>
#include <QThread>
#include <QLabel>


B::B()
{
    port = new QSerialPort;
}

void B::test(){
//    qDebug() << "ThreadId=" << QThread::currentThreadId();
//    for(int i = 0; i<20; i++){
//        printf("%d ", i);
//    }




    /**************************************/
    port->setPortName("COM7");
    port->setBaudRate(9600);
    port->setDataBits(QSerialPort::DataBits::Data8);
    port->setParity(QSerialPort::Parity::EvenParity);
    port->setStopBits(QSerialPort::StopBits::OneStop);
    port->open(QIODevice::ReadWrite);
    QString qs = "16";
    QStringList qsl = qs.split(" ");
    char tmp[512];
    int len = qsl.length();
    for(int i=0; i<len; i++){
        tmp[i] = qsl[i].toInt(nullptr, 16);
    }
//    bMutex.lock();
    gMutex.lock();
    port->write(tmp, len);
    QByteArray res;
    res.clear();
    qDebug() << "subThread is waiting";
    if(port->waitForReadyRead(5000)){
        res = port->readAll();
        while(port->waitForReadyRead(300)){
            res += port->readAll();
        }
    }
    qDebug() << res;
    qDebug() << "subThread is over";
//    bMutex.unlock();
    gMutex.unlock();


}
