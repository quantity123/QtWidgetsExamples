#include "widget.h"
#include "ui_widget.h"
#include "qqtttreenode.h"
#include <QMenu>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , mQttTreeModel(new QQttTreeModel(this))
    , mTreeView(new QTreeView(this))
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    mVBoxLayout.addWidget(mTreeView);
    this->setLayout(&mVBoxLayout);
    mTreeView->setModel(mQttTreeModel);
    mTreeView->expandAll();
    mTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    mTreeView->setColumnWidth(0, 200);
    connect(mTreeView, &QTreeView::customContextMenuRequested, this, &Widget::onTreeViewMenuRequested);

//    loadQSS();
}

Widget::~Widget()
{
    delete mQttTreeModel;
    delete mTreeView;
    delete ui;
}

void Widget::onTreeViewMenuRequested(const QPoint &aPos)
{
    QModelIndex currIndex = mTreeView->indexAt(aPos);   //获取位置能让菜单不在其它没有treeNode的地方弹出菜单，因为会判断isValid()是否有效
    if (currIndex.isValid())
    {
        QIcon msgBoxInfoIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation);
        QIcon msgBoxWarningIcon = QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning);
        QMenu menu;
        menu.addAction(msgBoxInfoIcon, "信息消息框", this, &Widget::onShowMessageBoxInformation);
        menu.addAction(msgBoxWarningIcon, "警告消息框", this, &Widget::onShowMessageBoxWarning);
        menu.exec(QCursor::pos());
    }
}

void Widget::onShowMessageBoxInformation()
{
    QModelIndex currIndex = mTreeView->currentIndex();
    QModelIndex index = currIndex.siblingAtColumn(0);   //获取当前行的第0列的索引
    if (index.isValid())
    {
        QMessageBox::information(this, "信息", index.data().toString());  //显示第0列的数据
    }
}

void Widget::onShowMessageBoxWarning()
{
    QMessageBox::warning(this, "警告", "警告的信息。。。。。");
}

void Widget::loadQSS()
{
//    qDebug() << QApplication::applicationDirPath();
//    qDebug() << QApplication::applicationFilePath();
    QFile file("D:/qtt/QtWorkSpace/QTreeView_QAbstractItemModel_1/QTreeView_QAbstractItemModel_1/style1.qss");
    if (file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
}
