#include "qstudent.h"
#include <QDebug>

QStudent::QStudent(QObject *parent) : QObject(parent)
{

}

void QStudent::treat()
{
    qDebug() << "请老师吃饭";
}

void QStudent::treat(QString foodName)
{
    qDebug() << "请老师吃" << foodName.toUtf8().constData();
}

void QStudent::treat(QString foodName, int foodNum)
{
    qDebug() << "请老师吃" << foodNum << foodName.toUtf8().constData();
}
