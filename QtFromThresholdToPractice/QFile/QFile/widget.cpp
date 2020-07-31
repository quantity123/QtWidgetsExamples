#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QFileInfo>
#include <QDebug>
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    auto lbdPushButtonClicked = [=]()
    {
        QString path = QFileDialog::getOpenFileName(this, "打开文件", "/home/quantity123/QTWorkspace/FromThresholdToPractice/QFile/content.txt");
        //将路径放入lineEdit中
        ui->lineEdit->setText(path);
        //编码格式类
//        QTextCodec *codec = QTextCodec::codecForName("gbk");
        //读取内容，放入到textEdit中
        QFile file(path);

        //////////////////////////////////写入数据到文件///////////////////////////
        file.open(QIODevice::Append);   //用追加方式进行写
        file.write("点点点点点");
        file.close();

        //////////////////////////////////读取文件的数据///////////////////////////
        //设置打开文件的方式
        file.open(QIODevice::ReadOnly);

        //读取文件所有内容
        //QByteArray array = file.readAll();

        //循环方式一次读取一行来读取所有内容
        QByteArray array;
        while (!file.atEnd())
        {
            array += file.readLine();
        }

        //将读取到的数据放入textEdit中
        ui->textEdit->setText(array); //默认读取utf-8格式

//        QString content = codec->toUnicode(array);  //将gbk格式转换成
//        ui->textEdit->setText(content);
        //前面open打开文件，这里关闭文件
        file.close();

        //QFileInfo文件信息类
        QFileInfo fileInfo(path);
        qDebug() << "大小：" << fileInfo.size() << ", 后缀名：" << fileInfo.suffix() << "文件路径：" << fileInfo.filePath() << "文件名：" << fileInfo.fileName();
        qDebug() << "创建日期：" << fileInfo.created().toString("yyyy/MM/dd hh:mm:ss");
        qDebug() << "元日期修改时间：" << fileInfo.metadataChangeTime().toString("yyyy-MM-dd hh:mm:ss");
        qDebug() << "最后修改日期：" << fileInfo.lastModified().toString("yyyy-MM-dd hh:mm:ss");
    };
    connect(ui->pushButton, &QPushButton::clicked, lbdPushButtonClicked);
}

Widget::~Widget()
{
    delete ui;
}

