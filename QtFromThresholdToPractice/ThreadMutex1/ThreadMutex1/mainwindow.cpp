#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QThread>
#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mCommData(new QCommData)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //解决报错：QObject::connect: Cannot queue arguments of type 'QTextCursor'(Make sure 'QTextCursor' is registered using qRegisterMetaType().)
    //也可以使用信号槽，让QOperateCommData子线程发信号由主线程执行ui->textEdit->append(s)代码也不会报错
    qRegisterMetaType<QTextCursor>("QTextCursor");

    qDebug() << "MainWindow thread:" << QThread::currentThreadId();

    for (quint32 i=0; i<200; ++i)
    {
        QOperateCommData *mOperateCommData = new QOperateCommData;
        mObjectlist.append(mOperateCommData);
        mOperateCommData->setCommonDataPointVariable(mCommData);    //也可以这种做法，在线程类里直接调用mCommData对象代码封装的好
        mOperateCommData->setMainWindowPointer(this);



        //相当于把onCommonData函数绑定到信号所在的那个线程对象里去了，那么onCommonData函数执行也是在信号所在的那个线程对象里，
        //和setCommonDataPointVariable(mCommData)传对象指针进取调用方式差不多
        //不建议用lambda函数运行mOperateCommData对象里的代码，不符合代码封装性规则
//        auto onCommonData = [=]()->qint32
//        {
//            return mCommData->commonData();
//        };
//        connect(mOperateCommData, &QOperateCommData::commonData, onCommonData);

        connect(mOperateCommData, &QOperateCommData::commonData, mCommData, &QCommData::commonData, Qt::DirectConnection);

//        auto onSetCommonData = [=](quint32 aData)
//        {
//            mCommData->setCommonData(aData);
//            //QString s = QString("0x%1").arg(quintptr(t->currentThreadId()));  //查看线程ID
//        };
//        connect(mOperateCommData, &QOperateCommData::setCommonData, onSetCommonData);

        connect(mOperateCommData, &QOperateCommData::setCommonData, mCommData, &QCommData::setCommonData, Qt::DirectConnection);

        //默认Qt::AutoConnection：和Qt::QueuedConnection一样
        //Qt::DirectConnection：无论是否moveToThread都由emit发出信号的线程执行槽函数。（这样的方式不用传QCommData和QMainWindow对象指针到mOperateCommData对象里）
        //Qt::QueuedConnection：moveToThread(t)后由t线程执行槽函数，否则由emit发出线程执行槽函数
        //Qt::BlockingQueuedConnection：moveToThread后和Qt::QueuedConnection一样，否则死锁
        //Qt::UniqueConnection：moveToThread后和Qt::QueuedConnection一样，否则和Qt::DirectConnection一样
        connect(this, &MainWindow::incCommData, mOperateCommData, &QOperateCommData::incCommData, Qt::AutoConnection);

        connect(mOperateCommData, &QOperateCommData::addCommDataToEditText, this, &MainWindow::addCommDataToEditText, Qt::DirectConnection);

        QThread *t = new QThread(this); //关闭窗口线程报错，找出如何销毁线程
        mOperateCommData->moveToThread(t);
        //mCommData->moveToThread(t);   //一个类只能在一个线程里跑，如果重复设置给不同的线程会失败
        t->start();

//        emit mOperateCommData->addCommDataToEditText(5);

        //调用永远是哪个线程调用函数，函数就由哪个线程执行
        //mOperateCommData->incCommData();
    }

    //如果想要跨线程执行，先把目标类对象通过moveToThread移动给子线程，然后在原来的类对象建立信号并与目标的类对象的槽函数关联(connect函数使用Qt::QueuedConnection参数)
    //然后原来的类用emit调用信号，如果不详跨线程执行，要么不用moveToThread函数移动给子线程，要么connect函数使用Qt::DirectConnection参数
    //incCommData信号绑定多个槽函数，只用emit调用一次该信号，所有与该信号绑定的槽函数都执行
    emit this->incCommData();
}

MainWindow::~MainWindow()
{
    while (mObjectlist.count() > 0)
    {
        auto obj = mObjectlist.takeFirst();

        auto objThread = obj->thread();
        objThread->quit();
        objThread->wait();
        objThread->deleteLater();
        //delete objThread;

        obj->deleteLater();
        //delete obj;
    }

    delete mCommData;
    delete ui;
}

void MainWindow::addCommDataToEditText(quint32 aData)
{
   qDebug() << "MainWindow addCommDataToEditText thread:" << QThread::currentThreadId();
   auto s = QString("%1").arg(aData);
   ui->textEdit->append(s);
}
