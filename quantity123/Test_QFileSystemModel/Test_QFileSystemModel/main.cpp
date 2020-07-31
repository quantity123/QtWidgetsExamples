//#include "mainwindow.h"

#include <QApplication>
#include <QSplitter>
#include <QFileSystemModel>
#include <QTreeView>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QSplitter splitter;
    splitter.setWindowTitle("两个视图使用一个QFileSystemModel模型");

    QFileSystemModel model;
    model.setRootPath(QDir::currentPath());

    QTreeView treeView(&splitter);
    treeView.setModel(&model);
    treeView.setRootIndex(model.index(QDir::currentPath()));

    QListView listView_1(&splitter);
    listView_1.setModel(&model);
    listView_1.setRootIndex(model.index(QDir::currentPath()));

    splitter.show();

    return a.exec();
}
