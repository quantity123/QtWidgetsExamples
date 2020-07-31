#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

QStandardItemMgr::QStandardItemMgr(QIcon icon, QString ItemName)
{
    mStandardItem.setIcon(icon);
    mStandardItem.setText(ItemName);
}

QStandardItemMgr::~QStandardItemMgr()
{
    while (mColumnList.count() > 0)
    {
        QStandardItem *columnItem = mColumnList.takeAt(0);
        delete columnItem;
    }
    while (mChildItemList.count() > 0)
    {
        QStandardItemMgr *childItem = mChildItemList.takeAt(0);
        delete childItem;
    }
}

void QStandardItemMgr::setCheckable(bool checked)
{
    mStandardItem.setCheckable(checked);
}

QStandardItem* QStandardItemMgr::standardItem()
{
    return &mStandardItem;
}

void QStandardItemMgr::setTreeItemIconList(QMap<QString, QIcon> *treeItemIconList)
{
    mTreeItemIconList = treeItemIconList;
}

QStandardItemMgr* QStandardItemMgr::appendChild(QString itemText, bool isCheckable)
{
    QStandardItemMgr *childItem = new QStandardItemMgr(mTreeItemIconList->value("projectName"), itemText);
    childItem->setCheckable(isCheckable);
    mStandardItem.appendRow(childItem->standardItem());
    mChildItemList.append(childItem);
    return childItem;
}

/////////////////////////////QStandardItemModelMgr////////////////////////////////////////////////////////////////////////////////

QStandardItemModelMgr::QStandardItemModelMgr()
{
    mTreeItemIconList.insert("projectName", QIcon(":/Icons/4kong.com-0001.png"));
    mTreeItemIconList.insert("info_1", QIcon(":/Icons/4kong.com-0002.png"));
    mTreeItemIconList.insert("info_2", QIcon(":/Icons/4kong.com-0003.png"));
    QStringList column;
    column.append("项目名称");
    column.append("信息0");
    column.append("信息1");
    mStandardItemModel.setHorizontalHeaderLabels(column);
}

QStandardItemModelMgr::~QStandardItemModelMgr()
{
//    mTreeItemIconList.clear();
}

QStandardItemModel* QStandardItemModelMgr::standardItemModel()
{
    return &mStandardItemModel;
}

QMap<QString, QIcon>* QStandardItemModelMgr::treeItemIconList()
{
    return &mTreeItemIconList;
}

QStandardItemMgr* QStandardItemModelMgr::appendRoot(QString rootText, bool isCheckable)
{
    QStandardItemMgr *rootItem = new QStandardItemMgr(mTreeItemIconList["projectName"], rootText);
    rootItem->setCheckable(isCheckable);
    mStandardItemModel.appendRow(rootItem->standardItem());
    mStandardItemModel.item
    mChildItemList.append(rootItem);
    return rootItem;
}

void QStandardItemModelMgr::removeRoot(quint8 rowIndex)
{
    mStandardItemModel.takeRow(rowIndex);
    QStandardItemMgr *standardItemMgr = mChildItemList.takeAt(rowIndex);
    delete standardItemMgr;
}

void QStandardItemModelMgr::appendRootColumn(quint8 rowIndex, QString columnText, quint8 columnIndex)
{
    QString iconName = QString("info_%1").arg(columnIndex);
    QStandardItem *columnItem = new QStandardItem(mTreeItemIconList[iconName], columnText);
    QStandardItemMgr *rootItem = mChildItemList.at(rowIndex);
    mStandardItemModel.setItem(rootItem->standardItem()->row(), columnIndex, columnItem);
    mColumnList.append(columnItem);
    qDebug() << "appendRootColumn ColumnListCount:" << mColumnList.count();
}

void QStandardItemModelMgr::deleteRootColumnItem(quint8 rowIndex, quint8 columnIndex)
{
    qDebug() << "deleteRootColumnItem ColumnListCount:" << mColumnList.count();
    mStandardItemModel.takeItem(rowIndex, columnIndex);
    QStandardItem *columnItem = mColumnList.takeAt(0);
    delete columnItem;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QString ItemName;
//    QStandardItem *rootItem;
//    QString columnItemName;
//    QString iconName;
//    QStandardItem *ColumnItem;
//    ItemName = "项目";
//    rootItem = new QStandardItem(mTreeItemIconList["Icon_0"], ItemName);
//    rootItem->setCheckable(true);
//    model->appendRow(rootItem);
//    for (int var = 1; var < 3; ++var)
//    {
//        columnItemName = QString("%1信息%2").arg(ItemName).arg(var);
//        iconName = QString("Icon_%1").arg(var);
//        ColumnItem = new QStandardItem(mTreeItemIconList[iconName], columnItemName);
//        model->setItem(rootItem->row(), var, ColumnItem);
//    }

//    QStandardItem *rootItem_sub;
//    for (int var = 1; var < 3; ++var)
//    {
//        ItemName = QString("文件夹%1").arg(var);
//        subItem = new QStandardItem(mTreeItemIconList["Icon_0"], ItemName);
//        rootItem->appendRow(subItem);
//        for (int var = 1; var < 3; ++var)
//        {
//            treeItemText = QString("%1信息%2").arg(ItemName).arg(var);
//            subColumnItem = new QStandardItem(treeItemText);
//            rootItem->setChild(subItem->row(), var, subColumnItem);
//        }
//    }

    QString itemText;
    QString columnText;
    auto treeItemIconList = mStandardItemModelMgr.treeItemIconList();
    for (int i = 0; i < 1; ++i)
    {
        //根项目
        itemText = QString("项目%1").arg(i);
        QStandardItemMgr *rootItem = mStandardItemModelMgr.appendRoot(itemText, true);
        rootItem->setTreeItemIconList(treeItemIconList);
        for (int j = 0; j < 2; ++j)
        {
            columnText = QString("%1信息%2").arg(itemText).arg(j);
            mStandardItemModelMgr.appendRootColumn(i, columnText, j+1);
        }
        //一级子项
        for (int k = 0; k < 3; ++k)
        {
            itemText = QString("文件夹%1").arg(k);
            QStandardItemMgr *childItem = rootItem->appendChild(itemText, true);
            for (int l = 0; l < 2; ++l)
            {
                columnText = QString("%1信息%2").arg(itemText).arg(l);
//                rootItem->appendChildColumn(k, columnText, l+1);
            }
        }
    }

//    mStandardItemModelMgr.deleteRootColumnItem(0, 1);
//    mStandardItemModelMgr.deleteRootColumnItem(0, 2);

    ui->treeView->setModel(mStandardItemModelMgr.standardItemModel());
//    ui->treeView->resizeColumnToContents(0);
    ui->treeView->setColumnWidth(0, 150);
    ui->treeView->setColumnWidth(1, 250);
    ui->treeView->expandAll();
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < 1; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            mStandardItemModelMgr.deleteRootColumnItem(0, j+1);
        }
        mStandardItemModelMgr.removeRoot(0);
    }

    delete ui;
}

void MainWindow::on_treeView_clicked(const QModelIndex &/*index*/)
{
//    qDebug() << index.siblingAtColumn(0).data().toString(); //查找点击任何一行的第0列的索引数据项

//    qDebug() << index.siblingAtRow(0).data().toString();    //查找点击任何一列的第0行的索引数据项
}
