#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>

class QWorkThread : public QThread
{
    Q_OBJECT
public:
    QWorkThread();
    ~QWorkThread();
signals:
    void done();
protected:
    void run() override;
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

private:
    int mSec;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
