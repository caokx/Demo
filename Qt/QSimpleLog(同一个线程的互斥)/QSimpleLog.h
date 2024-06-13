#ifndef LOG_H
#define LOG_H
#include <QDebug>
#include <QDate>
#include <QFile>
#include <QThread>
#include <QList>
#include <QSemaphore>
#include <QMutex>
/***************************************
* 说明：日志功能的单线程实现
* 作者：caokexiang
* 时间：20240522
******************************************/
class QSimpleLog : public QThread
{
    Q_OBJECT
public:
    QSimpleLog(QString const& fileName); //创建对象时指定日志文件的名字
public:
    void write(const QString& msg);     //将msg写入日志文件
    void clear();               //清空日志文件
    virtual void run();
private:
    QString const fileName; // 文件名
    QList<QString> m_msg;   //写入线程的消息队列
    QMutex m_mutex;         //对m_msg进行线程安全保护的互斥信号量
    QSemaphore m_synSem;    //同步信号量，当消息队列未进入时，线程处于阻塞状态，可以避免while一直死循环
};
#endif
