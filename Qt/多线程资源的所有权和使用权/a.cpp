//a.cpp
#include "a.h"
#include <QThread>
#include <QDebug>
#include <QTimer>


A::A():subThread(new QThread)
  ,c(new C)
{
    qDebug() << QString::fromLocal8Bit("1-当前调用线程=") << QThread::currentThread();
    qDebug() << "1-a->thread=" << this->thread();
    qDebug() << "1-a->c->thread=" << c->thread();
    this->moveToThread(subThread);
    qDebug()<<"";
    qDebug() << QString::fromLocal8Bit("执行this->moveToThread(subThread)");
    qDebug()<<"";
    qDebug() << QString::fromLocal8Bit("2-当前调用线程=") << QThread::currentThread();
    qDebug() << "2-a->thread=" << this->thread();
    qDebug() << "2-a->c->thread=" << c->thread();
    qDebug() << "";
    connect(subThread, &QThread::started, this, &A::begin);
}
void A::begin(){
    qDebug() << "A::begin()";
    qDebug() << QString::fromLocal8Bit("当前调用线程=") << QThread::currentThread();
    qDebug() << "A::begin() this->thread=" << this->thread();
    qDebug() << "A::begin() this->c->thread=" << this->c->thread();
    QTimer* timer = new QTimer(c);
    qDebug() << "A::begin() timer->thread=" << timer->thread();
}
