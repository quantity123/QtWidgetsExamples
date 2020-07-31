//#include "mainwindow.h"

#include <QApplication>
#include <QMap>
#include <QTableView>
#include "qcurrencymodel.h"
#include <QSplitter>
#include "qcitymodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    QSplitter splitter;
    splitter.setWindowTitle(QObject::tr("Test QAbstractTableModel"));

    //给模型创造数据
    QMap<QString, double> currencyMapData;
    currencyMapData.insert("AUD", 1.3259);
    currencyMapData.insert("CHF", 1.2980);
    currencyMapData.insert("CZK", 6.4810);
    currencyMapData.insert("DKK", 2.6597);
    //自定义表模型1
    QCurrencyModel currencyModel;
    currencyModel.setCurrencyMap(currencyMapData);
    //表视图
    QTableView tableView(&splitter);
    //设置视图模型
    tableView.setModel(&currencyModel);
    //设置交替颜色
    tableView.setAlternatingRowColors(true);

///////////////////////////////////////////////////

    //给模型创造数据
    QStringList cities;
    cities << "杭州" << "上海" << "南京" << "北京" << "武汉";
    //自定义表模型1
    QCityModel cityModel;
    cityModel.setCities(cities);
    //表视图
    QTableView tableView_2(&splitter);
    //设置视图模型
    tableView_2.setModel(&cityModel);
    //设置交替颜色
    tableView_2.setAlternatingRowColors(true);

    splitter.show();

    return a.exec();
}
