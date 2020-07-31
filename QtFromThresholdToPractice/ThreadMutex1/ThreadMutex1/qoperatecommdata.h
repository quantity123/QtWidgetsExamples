#ifndef QOPERATECOMMDATA_H
#define QOPERATECOMMDATA_H

#include <QObject>
#include <QMutex>
#include "qcommdata.h"
#include "mainwindow.h"

//类型定义一个函数指针
//typedef void(*TeacherHungry2)(QString);

class QOperateCommData : public QObject
{
    Q_OBJECT
public:
    explicit QOperateCommData(QObject *parent = nullptr);
    void setCommonDataPointVariable(QCommData *aCommData);
    void setMainWindowPointer(QMainWindow *aMainWindow);
    //void(*teacherHungry3)(QString);   //直接声明定义一个函数指针teacherHungry3，可以把函数指针传入
    //TeacherHungry2 teacherHungry2;      //通过上面定义TeacherHungry2函数指针，这里可以直接声明定义
public slots:
    void incCommData();
signals:
    void setCommonData(qint32 aData);
    qint32 commonData();
    void addCommDataToEditText(quint32 aData);
private:
    QMainWindow *mMainWindow;
    QCommData *mCommData;
    QMutex mMutex;
};

#endif // QOPERATECOMMDATA_H
