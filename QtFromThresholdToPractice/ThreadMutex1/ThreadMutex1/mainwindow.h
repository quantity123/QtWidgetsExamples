#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcommdata.h"
#include "qoperatecommdata.h"
#include <QObjectList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void addCommDataToEditText(quint32 aData);

private slots:
    void addCommDataToEditText(quint32 aData);    //想其它线程发到main线程执行，就可设置槽函数

signals:
    qint32 incCommData();
private:
    QObjectList mObjectlist;
    QCommData *mCommData;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
