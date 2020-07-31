#include "qoperatecommdata.h"
#include <QDebug>
#include <QThread>

QOperateCommData::QOperateCommData(QObject *parent)
    : QObject(parent)
{

}

void QOperateCommData::setCommonDataPointVariable(QCommData *aCommData)
{
    mCommData = aCommData;
}

void QOperateCommData::setMainWindowPointer(QMainWindow *aMainWindow)
{
    mMainWindow = aMainWindow;
}

void QOperateCommData::incCommData()
{
    qDebug() << "QOperateCommData thread: " << QThread::currentThreadId();
    mMutex.lock();
    auto data = emit commonData();  //信号可以有返回值
//    auto data = mCommData->commonData();
    ++data;
    emit setCommonData(data);
//    mCommData->setCommonData(data);

    emit addCommDataToEditText(data);
//    static_cast<MainWindow*>(mMainWindow)->addCommDataToEditText(data);
    mMutex.unlock();
}
