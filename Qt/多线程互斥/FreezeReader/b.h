#pragma once

#include<QObject>
#include<QMutex>
#include<QtSerialPort/QSerialPort>
#include<QtSerialPort/QSerialPortInfo>

extern QMutex gMutex;

class B: public QObject
{
public:
    B();
public:
    void test();
public:
    QSerialPort* port;
    QMutex bMutex;
};

