//a.h
#pragma once
#include "c.h"

class A: public QObject
{
    Q_OBJECT
public:
    A();
public:
    void begin();

public:
    QThread* subThread;
    int x;
    C* c;
};
