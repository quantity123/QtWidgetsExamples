//#include "mainwindow.h"

#include <QApplication>
#include <QStringListModel>
#include <QListView>
#include <QSplitter>
#include <QTableView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;

    QSplitter splitter;
    splitter.setWindowTitle("两个视图使用一个QStringListModel模型");

    QStringList numbers;
    numbers << "aaa" << "bbb" << "ccc" << "ddd";
    QStringListModel model;
    model.setStringList(numbers);

    QListView listView(&splitter);
    listView.setModel(&model);
//    listView.show();  //如果不指定parent为splitter，就可以show自己显示

    QTableView tableView(&splitter);
    tableView.setModel(&model);
    //    tableView.show();  //如果不指定parent为splitter，就可以show自己显示

    splitter.show();

//    w.show();
    return a.exec();
}
