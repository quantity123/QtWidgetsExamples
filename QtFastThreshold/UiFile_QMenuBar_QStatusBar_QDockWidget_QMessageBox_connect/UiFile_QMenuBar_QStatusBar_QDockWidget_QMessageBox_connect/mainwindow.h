#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
    void on_action_N_triggered();
    void on_action_O_triggered();

    void on_action_S_triggered();

    void on_action_C_triggered();

private:
    Ui::MainWindow *ui;
    QLabel *mLable;
};
#endif // MAINWINDOW_H
