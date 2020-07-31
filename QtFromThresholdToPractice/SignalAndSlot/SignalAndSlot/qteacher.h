#ifndef QTEACHER_H
#define QTEACHER_H

#include <QObject>

class QTeacher : public QObject
{
    Q_OBJECT
public:
    explicit QTeacher(QObject *parent = nullptr);

signals:
    //自定义信号，必须写到signals下
    //返回值是void，只需要声明，不需要实现
    //可以有参数，信号参数与槽参数可以对应传值，可以重载
    void hungry();
    void hungry(QString foodName);
    void hungry(QString foodName, int foodNum);
};

#endif // QTEACHER_H
