#include <QCoreApplication>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include "qworker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug() << "From main thread:" << QThread::currentThreadId();

    QTimer timer;
    QWorker worker;
    QCoreApplication::connect(&timer, &QTimer::timeout, &worker, &QWorker::onTimeout);
    timer.start(1000);

    //QThread t;
    QThread *t = new QThread;
    worker.moveToThread(t);    //woker从主线程转移到子线程t来响应onTimeout，也就是队列连接，默认是直接连接，槽函数在发送者所在线程执行
    t->start();
    return a.exec();
}
