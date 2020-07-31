#include "mylabel.h"
#include <QDebug>
#include <QMouseEvent>

MyLabel::MyLabel(QWidget *parent)
    : QLabel(parent)
{
    //设置鼠标追踪状态，只要在控件范围内直接捕获信息
    //setMouseTracking(true);

    //安装事件过滤器
    installEventFilter(this);   //this是过滤的对象，对象里有eventFilter事件处理函数
}

void MyLabel::enterEvent(QEvent *event)
{
    //qDebug() << "鼠标进入了";
}

void MyLabel::leaveEvent(QEvent *event)
{
    //qDebug() << "鼠标离开了";
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
//    if (ev->button() == Qt::LeftButton)
//    {
        //globalX 是整个屏幕的X位置
        QString str = QString("鼠标按下了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug() << str;
//    }
}

void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
//    if (ev->button() == Qt::LeftButton)
//    {
        QString str = QString("鼠标释放了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug() << str;
//    }
}

void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
//    if (ev->buttons() & Qt::LeftButton)
//    {
        QString str = QString("鼠标移动了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug() << str;
//    }
}

bool MyLabel::event(QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *ev = dynamic_cast<QMouseEvent *>(e);
        QString str = QString("Event事件分发器函数中鼠标按下了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
        qDebug() << str;
        return true;    //true代表用户自己处理这个事件，不向下分发，由于这个事件比mousePressEvent事件更上层，所以mousePressEvent事件不响应
    }
    //其它事件交给父类(默认)处理
    return QLabel::event(e);
}

bool MyLabel::eventFilter(QObject *object, QEvent *event)
{
//    if (object == this)
//    {
        if (event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *ev = dynamic_cast<QMouseEvent *>(event);
            QString str = QString("EventFilter事件过滤器函数中鼠标按下了 x = %1, y = %2, globalX = %3, globalY = %4").arg(ev->x()).arg(ev->y()).arg(ev->globalX()).arg(ev->globalY());
            qDebug() << str;
            return true;    //true代表用户自己处理这个事件，不向下分发，由于这个事件比Event事件更上层，所以Event事件不响应
        }
//    }
    //其它事件交给父类(默认)处理
    return QLabel::eventFilter(object, event);
}
