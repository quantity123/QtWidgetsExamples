#include "widget.h"
#include "ui_widget.h"
#include <QTreeView>
#include <QStandardItemModel>
#include <QHeaderView>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    auto treeView = new QTreeView(this);
    treeView->setFixedSize(400, 300);

    auto model = new QStandardItemModel(this);
    for (int row=0; row<5; ++row)
    {
        QStandardItem *item = new QStandardItem(QString("group%1").arg(row));
        model->appendRow(item);
        for (int subRow=0; subRow<4; ++subRow)
        {
            QStandardItem *subItem = new QStandardItem(QString("sub%1").arg(subRow));
            item->appendRow(subItem);
        }
    }
    treeView->setModel(model);
}

Widget::~Widget()
{
    delete ui;
}

