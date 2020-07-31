#include "widget.h"
#include "ui_widget.h"
#include <QThread>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << "widget thread:" << QThread::currentThreadId();

    mWork = new QWork;
    auto onDrawImageDone = [=](QImage image)
    {
        qDebug() << "qwork thread:" << QThread::currentThreadId();
        this->mImage = image;
        update();
    };
    connect(mWork, &QWork::signalDrawImageDone, onDrawImageDone);
    connect(ui->pushButton, &QPushButton::clicked, mWork, &QWork::slotDrawImage);

    QThread *thread = new QThread(this);
    mWork->moveToThread(thread);	//相当于work中slotDrawImage在线程中运行
    thread->start();
}

Widget::~Widget()
{

    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0, 0, this->mImage);
}
