#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPushButton *pushButton1 = new QPushButton(this);
    QPushButton *pushButton2 = new QPushButton(this);
    pushButton2->move(200, 100);
    //传所有值
    [=]()
    {
        pushButton1->setText("aaa");
    }();
    //传所有引用
    [&]()
    {
        pushButton2->setText("bbb");
    }();

    int i = 10;

    auto lbd1 = [=]()
    {
        qDebug() << i;
    };
    connect(pushButton1, &QPushButton::clicked, this, lbd1);    //connect还可以把信号和lambda函数关联

    auto lbd2 = [this, i]()mutable    //mutable能让传值i进来能修改,或者传 &i 也可以修改i的值
    {
        i = 100 + 10;
        qDebug() << i;
        this->close();
    };
    connect(pushButton2, &QPushButton::clicked, lbd2);  //connect函数使用lambda表达式时候可以省略第三个参数
    //connect(pushButton2, &QPushButton::clicked, this, lbd2);

    //lambda函数返回值
    int ret = []()->int
    {
        return 1000;
    }();
    qDebug() << ret;
}

MainWindow::~MainWindow()
{
    delete ui;
}

