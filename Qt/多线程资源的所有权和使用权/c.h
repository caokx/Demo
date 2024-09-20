//c.h
#pragma once
#include <QObject>
class C:public QObject{
    Q_OBJECT
public:
    C();
    void print();
};
