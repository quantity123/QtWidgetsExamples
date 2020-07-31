#include "loginwindow.h"
#include "./ui_loginwindow.h"
#include <QDesktopWidget>
#include <fstream>
#include <QFile>
#include <QHostAddress>
#include <QDebug>

using namespace std;

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
    , mTcpSocket(new QTcpSocket(this))
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

	this->setFixedSize(this->width(), this->height());
	
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width()-this->width())/2, (desktop->height()-this->height())/2);
    
    setWindowTitle("欢迎登陆任意聊");

    setUiLoginState(false);

    connectTcpSocketSignalAndSlot();

    connectServer();
}

LoginWindow::~LoginWindow()
{
    delete mTcpSocket;
    delete ui;
}

void LoginWindow::setUiLoginState(bool aIsLogin) const
{
    ui->wigtInputInfo->setEnabled(aIsLogin);
    ui->wigtLogin->setEnabled(aIsLogin);
    if (aIsLogin)
        ui->lblShowInfo->setText("服务器已经开启，可以登陆！");
    else
        ui->lblShowInfo->setText("服务器未开启，不能登陆！");
}

void LoginWindow::connectTcpSocketSignalAndSlot()
{
    auto lbdConnected = [&]()
    {
        setUiLoginState(true);
    };
    connect(mTcpSocket, &QTcpSocket::connected, lbdConnected);

    auto lbdReadDataPacket = [&]()
    {
        mTcpSocket->read(mReceiveDataPacket.getDataPacket(), DATA_HEAD_LENGTH);
        if (!mReceiveDataPacket.decodeDataHead())
        {
            qDebug() << "解包失败！";
            return;
        }
        mTcpSocket->read(mReceiveDataPacket.getDataBody(), mReceiveDataPacket.getDataBodyLength());
        DataBodyType dataBodyType = mReceiveDataPacket.getDataBodyType();
        switch (dataBodyType)
        {
            case DBT_CLIENT_LOGIN_FEED_BACK:
            {
                bool loginFeedback = mReceiveDataPacket.getClientLoginFeedback();
                if (loginFeedback)
                    qDebug() << "Login Success!!";
                else
                    qDebug() << "Login failure!!";
                break;
            }
            case DBT_TEST_CLIENT_ONLINE:
            {
                bool isOnline = mReceiveDataPacket.getClientIsOnline();
                qDebug() << "Get Server Test Client Online DataPacket: " << isOnline;
                if (!isOnline)
                {
                    CDataPacket dataPacket;
                    dataPacket.buildTestClientOnline(true);
                    //发送数据包
                }
                break;
            }
            default:
            {
                qDebug() << dataBodyType << " number is not DataBodyType!";
                break;
            }
        }
    };
    connect(mTcpSocket, &QTcpSocket::readyRead, lbdReadDataPacket);
}

void LoginWindow::connectServer() const
{
    QFile file("Config.txt");
    file.open(QIODevice::ReadOnly);
    QByteArray byteArr;
    byteArr = file.readLine();
    QString ip = byteArr;
    byteArr = file.readLine();
    quint16 port = byteArr.toUShort();
    file.close();
    mTcpSocket->connectToHost(QHostAddress(ip), port);
}

void LoginWindow::on_pbLogin_clicked()
{
    CDataPacket dataPacket;
    string input = "LoginName:quantity123";
    if (dataPacket.buildClientLogin(input))
    {
        mTcpSocket->write(dataPacket.getDataPacket(), dataPacket.getDataPacketLength());
    }
}

void LoginWindow::on_pbExit_clicked()
{
    mTcpSocket->disconnectFromHost();
    this->close();
}
