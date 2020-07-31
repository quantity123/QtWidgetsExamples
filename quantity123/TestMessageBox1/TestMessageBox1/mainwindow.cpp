#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMessageBox::information(this, "信息", "信息消息框内容");

    QMessageBox::question(this, "问题", "问题消息框内容");

    QMessageBox::warning(this, "警告", "警告消息框内容");

    QMessageBox::critical(this, "严重", "严重消息框内容");
}

MainWindow::~MainWindow()
{
    delete ui;
}

