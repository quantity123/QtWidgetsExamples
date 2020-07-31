#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , mTimerId1(0)
    , mTimerId2(0)
    , mTimerId1Num(0)
    , mTimerId2Num(0)
    , mTimer(new QTimer(this))
    , mTimerId3Num(0)
{
    ui->setupUi(this);
    mTimerId1 = startTimer(1000);   //Widget内部封装了定时器，所以可以直接开始启动并响应timerEvent事件
    mTimerId2 = startTimer(2000);

    auto lbdTimeout = [&]()
    {
        ui->label3->setText(QString("%1").arg(mTimerId3Num++));
    };
    connect(mTimer, &QTimer::timeout, lbdTimeout);
    mTimer->start(500);
}

Widget::~Widget()
{
    delete mTimer;
    delete ui;
}

void Widget::timerEvent(QTimerEvent *timeEvent)
{
    if (timeEvent->timerId() == mTimerId1)
    {
        ui->label1->setNum(mTimerId1Num++);
    }
    else if (timeEvent->timerId() == mTimerId2)
    {
        ui->label2->setText(QString::number(mTimerId2Num++));
    }
}
