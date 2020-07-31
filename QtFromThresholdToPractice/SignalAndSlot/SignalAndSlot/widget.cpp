#include "widget.h"
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    resize(600, 400);
    move(300, 150);

    mTeacher = new QTeacher(this);
    mStudent = new QStudent(this);

	//直接声明与定义类函数(无参数)
    //重载的信号与槽需要定义函数指针名称来给connect使用，信号函数参数与槽函数参数必须一一对应
    void(QTeacher:: *teacherHungry1)() = &QTeacher::hungry;
    void(QStudent:: *studentTreat1)() = &QStudent::treat;
    connect(mTeacher, teacherHungry1, mStudent, studentTreat1);
    callTeacharHungry1();

	//直接声明与定义类函数(有QString参数)
    void(QTeacher:: *teacherHungry2)(QString) = &QTeacher::hungry;
    void(QStudent:: *studentTreat2)(QString) = &QStudent::treat;
    connect(mTeacher, teacherHungry2, mStudent, studentTreat2);
    callTeacharHungry2();

    QPushButton *pushButton = new QPushButton("下课", this);
    //信号可以连接信号，就像callTeacharHungry1函数直接emit调用了hungry信号
    connect(pushButton, &QPushButton::clicked, mTeacher, teacherHungry1);

    connect(pushButton, &QPushButton::clicked, this, &Widget::callTeacharHungry2);

    //断开信号，把callTeacharHungry2函数断开
    //disconnect(pushButton, &QPushButton::clicked, this, &Widget::callTeacharHungry2);

    //一个clicked信号可连接多个槽函数

    //多个信号可以连接同一个槽函数

    //信号参数可以多于槽函数参数，但是类型要对应
}

Widget::~Widget()
{
    delete mStudent;
    delete mTeacher;
}

void Widget::callTeacharHungry1()
{
    emit mTeacher->hungry();
}

void Widget::callTeacharHungry2()
{
    emit mTeacher->hungry("汉堡");
}
