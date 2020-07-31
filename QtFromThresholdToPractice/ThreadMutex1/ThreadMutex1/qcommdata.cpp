#include "qcommdata.h"
#include <QDebug>
#include <QThread>

QCommData::QCommData(QObject *parent)
    : QObject(parent)
    , mCommonData(0)
{
}

void QCommData::setCommonData(qint32 aData)
{
    //这里要用读写锁
    mCommonData = aData;
}

qint32 QCommData::commonData() const
{
    qDebug() << "QCommData thread: " << QThread::currentThreadId();
    //这里要用读写锁
    return mCommonData;
}
