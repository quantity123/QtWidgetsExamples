#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , model(this)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QStandardItemModel model;
    //设置大小
    model.setColumnCount(3);
    model.setRowCount(5);
    //设置表头
    model.setHeaderData(0, Qt::Horizontal, "ID");
    model.setHeaderData(1, Qt::Horizontal, "Name");
    model.setHeaderData(2, Qt::Horizontal, "Age");
    //添加数据
    for (int i=0; i<5; ++i)
    {
        QStandardItem *itemID = new QStandardItem("Hello");
        model.setItem(i, 0, itemID);    //前面setColumnCount和setRowCount已经设置好所以这里设置数据，而不是append,insert
    }
    //选择这个model
    ui->tableView->setModel(&model);
    //列宽
    ui->tableView->setColumnWidth(0, 30);
    //整行选择
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    //隐藏最左边行序号那列
//    ui->tableView->verticalHeader()->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

