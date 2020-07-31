#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    //鼠标进入事件
    virtual void enterEvent(QEvent *event) override;    //virtual关键字可写可不写
    //鼠标离开事件
    void leaveEvent(QEvent *event) override;
    //鼠标按下事件
    void mousePressEvent(QMouseEvent *ev) override;
    //鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *ev) override;
    //鼠标移动事件
    void mouseMoveEvent(QMouseEvent *ev) override;
    //事件分发器，在mousePressEvent的事件上层
    bool event(QEvent *e) override;
    //事件过滤器，在event事件上层
    bool eventFilter(QObject *object, QEvent *event) override;
};

#endif // MYLABEL_H
