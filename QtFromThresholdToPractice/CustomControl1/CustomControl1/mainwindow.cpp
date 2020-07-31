#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto lbdGetMyControlPosValue = [&]()
    {
         qDebug() << ui->widget->getPos();
    };
    connect(ui->pushButton, &QPushButton::clicked, lbdGetMyControlPosValue);

    auto lbdSetMyControlPosValue = [&]()
    {
        ui->widget->setPos(50);
    };
    connect(ui->pushButton_2, &QPushButton::clicked, lbdSetMyControlPosValue);
}

MainWindow::~MainWindow()
{
    delete ui;
}

