#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDirModel>
#include <QTreeView>
#include <QHeaderView>
//#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QTreeWidget>
#include <QWidget>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto *model = new QDirModel(this);
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

    QTreeView *treeView = new QTreeView(this);
//    treeView->setFixedSize(300, 400);
    treeView->header()->setStretchLastSection(true);
    treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    treeView->header()->setSortIndicatorShown(true);
    QModelIndex index = model->index(QDir::currentPath());
    treeView->expand(index);
    treeView->scrollTo(index);
    treeView->resizeColumnToContents(0);

    treeView->setModel(model);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(treeView);

    QWidget *widget = new QWidget(this);    //主窗口必须创建widget，否则setlayout无效，如果是widget就不用了
    widget->setLayout(mainLayout);
    setCentralWidget(widget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

