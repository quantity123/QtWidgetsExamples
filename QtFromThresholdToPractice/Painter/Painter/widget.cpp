#include "widget.h"
#include "./ui_widget.h"
#include <QPainter>
#include <QPixmap>
#include <QPicture>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //pixmap绘图设备，专门为了平台做了显示优化
    QPixmap pixmap(300, 300);
    //填充颜色
    pixmap.fill(Qt::red);
    //声明画家
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::green));
    painter.drawEllipse(QPoint(150,150), 100, 100);
    //保存到存储设备
    pixmap.save("/home/quantity123/QTWorkspace/FromThresholdToPractice/Painter/pixmap.png");

    //QImage 绘图设备，可以对像素进行访问
    QImage img(300, 300, QImage::Format_RGB32);
    img.fill(Qt::blue);
    QPainter painter2(&img);
    painter2.setPen(QPen(Qt::green));
    painter2.drawEllipse(QPoint(150,150), 100, 100);
    //保存到存储设备，后面在paintEvent事件里用QImage对象装载
    img.save("/home/quantity123/QTWorkspace/FromThresholdToPractice/Painter/image.png");

    //QPicture 绘图设备，可以记录和重现绘图指令
    QPicture pic;
    QPainter painter3;
    painter3.begin(&pic);
    painter3.setPen(QPen(Qt::green));
    painter3.drawEllipse(QPoint(150,150), 100, 100);
    painter3.end();
    //保存到存储设备，后面在paintEvent事件里用QPicture对象装载
    pic.save("/home/quantity123/QTWorkspace/FromThresholdToPractice/Painter/picture.pic");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
//    //实例画家对象，this指定的是绘图设备
//    QPainter painter(this);
//    //设置画笔
//    QPen pen(QColor(255, 0, 0));
//    //设置画笔宽度
//    pen.setWidth(3);
//    //设置画笔风格
//    pen.setStyle(Qt::DotLine);
//    //设置画家使用这个笔
//    painter.setPen(pen);
//    //设置画刷
//    QBrush brush(Qt::cyan);
//    //设置花刷风格
//    brush.setStyle(Qt::Dense2Pattern);
//    //设置画家使用这个画刷
//    painter.setBrush(brush);

//    //画线
//    painter.drawLine(QPoint(0,0), QPoint(100,100));
//    //画圆与椭圆
//    painter.drawEllipse(QPoint(100,100), 50, 50);
//    //画矩形
//    painter.drawRect(QRect(20, 20, 50, 50));
//    //画文字
//    painter.drawText(QRect(10, 200, 150, 50), "好好学习，天天向上");

//    //////////////////////////////////////////////////高级设置/////////////////////////////////////////////
//    QPainter painter(this);
//    painter.drawEllipse(QPoint(100,50), 50, 50);
//    //设置抗锯齿能力，效率较低
//    painter.setRenderHint(QPainter::Antialiasing);
//    painter.drawEllipse(QPoint(220,50), 50, 50);

//    //移动画家位置，每次移动都是根据前面的移动位置的
//    painter.translate(0, 100);
//    //画矩形
//    painter.drawRect(QRect(20, 20, 50, 50));
//    painter.save();//保存当前画家状态
//    painter.translate(100, 0);
//    painter.drawRect(QRect(20, 20, 50, 50));
//    painter.translate(100, 0);
//    painter.restore();//还原前面保存时候画家状态
//    painter.drawRect(QRect(30, 30, 50, 50));    //这个矩形相当于画到和第一个矩形X,Y重叠位置+10

    //////////////////////////////////////////////////使用label画资源图片/////////////////////////////////////////////
    //QPixmap pixmap;
    //pixmap.load(":/images/copy.png");
    //ui->label->setPixmap(pixmap);
    ui->label->setPixmap(QPixmap(":/images/copy.png"));
    //ui->label->setEnabled(false);

    //////////////////////////////////////////////////使用画家画资源图片/////////////////////////////////////////////
    QPainter painter(this);
    painter.drawPixmap(20, 20, QPixmap(":/images/new.png"));

    ///////////////////////////////////利用QImage对像素进行修改
    //QImage img(":/images/save.png");
    QImage img;
    img.load(":/images/save.png");
    //修改像素点
    for (int i=10; i<30; ++i)
    {
        for (int j=10; j<30; ++j)
        {
            QRgb rgb = qRgb(255, 0, 0);
            img.setPixel(i, j, rgb);
        }
    }
    painter.drawImage(100, 0, img);
    //painter.drawImage(100, 0, QImage(":/images/save.png"));

    ///////////////////////////////重现保存在磁盘中QPicture的绘图指令与数据
    QPicture pic;
    pic.load("/home/quantity123/QTWorkspace/FromThresholdToPractice/Painter/picture.pic");
    painter.drawPicture(150, -45, pic);
}
