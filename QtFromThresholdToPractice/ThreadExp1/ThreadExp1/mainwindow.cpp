#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QPushButton>
#include <QTimer>
#include <chrono>

QWorkThread::QWorkThread()
{

}

QWorkThread::~QWorkThread()
{

}

void QWorkThread::run()
{
    for (quint32 i=0; i<1000000000; ++i)
    {
    }
    emit done();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , mSec(0)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *widget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout;
    widget->setLayout(layout);
    auto lcdNumber = new QLCDNumber(this);
    layout->addWidget(lcdNumber);
    auto button = new QPushButton(tr("start"), this);
    layout->addWidget(button);
    setCentralWidget(widget);

    QTimer *timer = new QTimer(this);
    auto onTimeout = [=]()
    {
        lcdNumber->display(mSec++);
    };
    connect(timer, &QTimer::timeout, onTimeout);

    QWorkThread *thread = new QWorkThread;
    thread->setParent(this);
    auto onDone = [=]()
    {
        timer->stop();
    };
    connect(thread, &QWorkThread::done, timer, onDone);
    auto onFinished = [=]()
    {
        thread->deleteLater();
    };
    connect(thread, &QWorkThread::finished, onFinished);
    
    auto onClicked = [=]()
    {
        timer->start(1);    //1毫秒
        thread->start();
        button->setEnabled(false);
    };
    connect(button, &QPushButton::clicked, onClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

