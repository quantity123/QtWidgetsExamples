#include "widget.h"
#include "./ui_widget.h"
#include <QDebug>
#include <QMouseEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //安装事件过滤器
    //ui->label->installEventFilter(this);
}

Widget::~Widget()
{
    delete ui;
}

//bool Widget::eventFilter(QObject *object, QEvent *event)
//{
//    if (object == ui->label)
//    {
//        if (event->type() == QEvent::MouseButtonPress)
//        {
//            QMouseEvent *ev = dynamic_cast<QMouseEvent *>(event);
//            QString str = QString("EventFilter事件过滤器函数中鼠标按下了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
//            qDebug() << str;
//            return true;    //true代表用户自己处理这个事件，不向下分发，由于这个事件比Event事件更上层，所以Event事件不响应
//        }
//    }
//    //其它事件交给父类(默认)处理
//    return QWidget::eventFilter(object, event);
//}
