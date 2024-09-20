//c.cpp
#include "c.h"
#include <QThread>
#include <QDebug>
C::C(){}
void C::print(){
    qDebug() << "C::当前调用线程=" <<QThread::currentThread();
    qDebug() << "C::所属线程=" <<this->thread();
}
