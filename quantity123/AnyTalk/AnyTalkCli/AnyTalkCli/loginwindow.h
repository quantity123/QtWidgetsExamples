#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include "../DataPacket/data_packet.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
    void setUiLoginState(bool aIsLogin) const;
    void connectTcpSocketSignalAndSlot();
    void connectServer() const;

private slots:
    void on_pbExit_clicked();
    void on_pbLogin_clicked();
private:
    CDataPacket mReceiveDataPacket;
    QTcpSocket *mTcpSocket;
    Ui::LoginWindow *ui;
};
#endif // MAINWINDOW_H
