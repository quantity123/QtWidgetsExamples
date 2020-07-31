#ifndef QSTUDENT_H
#define QSTUDENT_H

#include <QObject>

class QStudent : public QObject
{
    Q_OBJECT
public:
    explicit QStudent(QObject *parent = nullptr);

signals:

public slots:
//public:
    //早期老QT版本，要写到public slots，新版本可写在public或者全局下
    //返回值 void, 需要声明，也需要实现
    //可以有参数，可以发生重载
    void treat();
    void treat(QString foodName);
    void treat(QString foodName, int foodNum);
};

#endif // QSTUDENT_H
