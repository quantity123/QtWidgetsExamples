#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>
#include <signal.h>
#include <iostream>
#include <list>
#include <queue>
#include <memory>
#include <utility>
#include <string>
#include <functional>
#include <boost/asio.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include "../../DataPacket/data_packet.h"

using namespace std;
using boost::asio::ip::tcp;
using boost::asio::io_service;
using boost::asio::steady_timer;

using CSendDataPacketQueue = queue<CDataPacket>;

class CClient : public enable_shared_from_this<CClient>
{
private:
    tcp::socket mClientSocket;
    CDataPacket mReceiveDataPacket;
    CSendDataPacketQueue mSendDataPacketQueue;
    io_service::strand mClientStrand;
    string mClientName;
    bool mIsLogin;
    void sendDataPacketToClient();
    void pushDataPacketIntoSendQueue(const CDataPacket& aDataPacket);
    void processReceiveDataBody();
    void receiveDataBody();
    void receiveDataPacketHead();
public:
    CClient(tcp::socket aSocket, io_service& aIoService);
    void startReceiveDataPacket();
    void testClientOnline();
    bool getClientIsLogin();
};
using CClientPtr = shared_ptr<CClient>;

class CListen
{
private:
    io_service &mIOService;
    tcp::socket mListenSocket;
    tcp::acceptor mAcceptor;
    list<CClientPtr> mClientPtrList;
    io_service::strand mListenStrand;
    steady_timer mTestClientOnlineTimer;
    void acceptClientConnect();
    void testClientListOnline();
public:
    CListen(io_service& ioService, const tcp::endpoint& endPoint);
};

class CServer
{
private:
    io_service mIOService;
    list<CListen> mListenList;
    list<thread> mIOServiceThreadList; //创建多线程的vector容器，每个线程都跑io_service
public:
    CServer(int& argc, char** argv);
    void launch();
    bool isStopped() const;
    void stop();
};
using CServerPtr = unique_ptr<CServer>;

#endif // SERVER_H
