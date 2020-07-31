#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmyitemmodel.h"
#include <QTreeView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QMyItemModel *myItemModel = new QMyItemModel(this);
    QTreeView *treeView = new QTreeView(this);
    treeView->setModel(myItemModel);
    treeView->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

