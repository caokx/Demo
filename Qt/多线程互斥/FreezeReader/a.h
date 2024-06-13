#pragma once

#include <QMutex>

extern QMutex gMutex;

class B;
class QThread;



class A
{
public:
    A();
public:
    void begin();
private:
    B* b;
    QThread* subThread;
    QMutex aMutex;
};

