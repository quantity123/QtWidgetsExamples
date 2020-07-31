#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QStandardItemModel>

class QStandardItemMgr
{
public:
    QStandardItemMgr(QIcon icon, QString ItemName);
    ~QStandardItemMgr();
    void setCheckable(bool checked);
    QStandardItem* standardItem();
    void setTreeItemIconList(QMap<QString, QIcon> *treeItemIconList);
    QStandardItemMgr* appendChild(QString itemText, bool isCheckable);
private:
    QList<QStandardItemMgr*> mChildItemList;
    QList<QStandardItem*> mColumnList;
    QStandardItem mStandardItem;
    QMap<QString, QIcon> *mTreeItemIconList;
};

class QStandardItemModelMgr
{
public:
    QStandardItemModelMgr();
    ~QStandardItemModelMgr();
    QStandardItemModel* standardItemModel();
    QMap<QString, QIcon>* treeItemIconList();
    QStandardItemMgr* appendRoot(QString rootText, bool isCheckable);
    void removeRoot(quint8 rowIndex);
    void appendRootColumn(quint8 rowIndex, QString columnText, quint8 columnIndex);
    void deleteRootColumnItem(quint8 rowIndex, quint8 columnIndex);
private:
    QList<QStandardItemMgr*> mChildItemList;
    QList<QStandardItem*> mColumnList;
    QStandardItemModel mStandardItemModel;
    QMap<QString, QIcon> mTreeItemIconList;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    QStandardItemModelMgr mStandardItemModelMgr;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
