#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rect(10, 10, 50, 100);
    painter.fillRect(rect, Qt::red);
    painter.save(); //绘制状态的保存，保存是一个栈结构，所以后入先出
    painter.translate(100, 0);  //向右平移100px
    painter.fillRect(rect, Qt::yellow);
    painter.restore();  //载入前面保存的绘制状态
    painter.save();
    painter.translate(300, 0);  //向右平移300px
    painter.rotate(30);  //顺时针旋转30度
    painter.fillRect(rect, Qt::green);
    painter.restore();  //相当于把rotate过滤掉了
    painter.save();
    painter.translate(400, 0);
    painter.scale(2, 3);    //横坐标单位放大2倍，纵坐标放大3倍
    painter.fillRect(rect, Qt::blue);
    painter.restore();
    painter.save();
    painter.translate(600, 0);
    painter.shear(0, 1);    //横向不变，纵向扭曲1倍
    painter.fillRect(rect, Qt::cyan);
    painter.restore();
    painter.save();
    QTransform tf;
    tf.translate(850, 0);
    tf.rotate(30);
    tf.scale(0.5, 1.5);
    tf.shear(2, 3);
    painter.setTransform(tf);
    painter.fillRect(rect, Qt::black);
    painter.restore();
}
