#include "qworker.h"

QWorker::QWorker(QObject *parent) : QObject(parent)
{

}

void QWorker::onTimeout()
{
    qDebug() << "onTimeout get called from thread: " << QThread::currentThreadId();
}
