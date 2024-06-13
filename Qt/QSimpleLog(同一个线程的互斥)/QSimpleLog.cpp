#include "QSimpleLog.h"


QSimpleLog::QSimpleLog(QString const &fileName) : m_synSem(0), fileName(fileName){//初始化信号量，初始资源为0
} 

void QSimpleLog::write(const QString& msg)
{
    m_mutex.lock();
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString message = QString("[%1]: %2").arg(currentDateTime).arg(msg);
    m_msg.push_back(message);
    m_mutex.unlock();
    m_synSem.release(); //资源数增加1
}

void QSimpleLog::clear() {
    QFile file(fileName);
    file.open(QIODevice::WriteOnly); //覆盖形式重写文件
    file.close();
}

void QSimpleLog::run()
{
    while (true){
        m_synSem.acquire(); //申请消息队列中的一个资源，否则阻塞
        m_mutex.lock();
        if (m_msg.isEmpty()){
            continue;
        }
        QString message = m_msg.takeFirst();
        QFile file(fileName);
        file.open(QIODevice::WriteOnly | QIODevice::Append);
        QTextStream text_stream(&file);
        text_stream << message << "\r\n";
        file.flush();   //清空缓冲区
        file.close();   //关闭文件
        m_mutex.unlock();
    }
}