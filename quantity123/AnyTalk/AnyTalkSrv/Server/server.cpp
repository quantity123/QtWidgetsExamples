#include "server.h"

void CClient::sendDataPacketToClient()
{
    auto self(shared_from_this());
    auto lbdSendDataPacketToClient = [this, self](boost::system::error_code ec, size_t)
    {
        if (!ec)
        {
            mSendDataPacketQueue.pop();
            if (!mSendDataPacketQueue.empty())
                sendDataPacketToClient();
        }
    };
    boost::asio::async_write(mClientSocket, boost::asio::buffer(mSendDataPacketQueue.front().getDataPacket(), mSendDataPacketQueue.front().getDataPacketLength()), mClientStrand.wrap(lbdSendDataPacketToClient));
}

void CClient::pushDataPacketIntoSendQueue(const CDataPacket& aDataPacket)
{
    auto lbdWriteDataPacket = [this, aDataPacket]()
    {
        bool isEmpty = mSendDataPacketQueue.empty();
        mSendDataPacketQueue.push(aDataPacket);
        if (isEmpty)
        {
            sendDataPacketToClient();
        }
    };
    mClientStrand.post(lbdWriteDataPacket);
}

void CClient::processReceiveDataBody()
{
    DataBodyType dataBodyType = mReceiveDataPacket.getDataBodyType();
    switch (dataBodyType)
    {
        case DBT_CLIENT_LOGIN:
        {
            mClientName = mReceiveDataPacket.getClientName();
            mIsLogin = mClientName != "";
            CDataPacket dataPacket;
            dataPacket.buildClientLoginFeedback();
            pushDataPacketIntoSendQueue(dataPacket);
            BOOST_LOG_TRIVIAL(info) << "Client " << mClientName << " Login Success!!";
            break;
        }
        case DBT_TEST_CLIENT_ONLINE:
        {
            bool isOnline = mReceiveDataPacket.getClientIsOnline();
            if (isOnline)
            {
                BOOST_LOG_TRIVIAL(info) << "Client " << mClientName << " Online!!";
            }
            else
            {
                BOOST_LOG_TRIVIAL(info) << "Client " << mClientName << " Not Online!!";
            }
            break;
        }
        default:
        {
            BOOST_LOG_TRIVIAL(error) << dataBodyType << " number is not DataBodyType!";
            break;
        }
    }
}

void CClient::receiveDataBody()
{
    auto self(shared_from_this());
    auto receiveDataBodyCallBack = [this, self](boost::system::error_code ec, size_t)
    {
        if (!ec)
        {
            processReceiveDataBody();
            receiveDataPacketHead();
        }
    };
    boost::asio::async_read(mClientSocket, boost::asio::buffer(mReceiveDataPacket.getDataBody(), mReceiveDataPacket.getDataBodyLength()), mClientStrand.wrap(receiveDataBodyCallBack));
}

void CClient::receiveDataPacketHead()
{
    auto self(shared_from_this());
    auto receiveDataPacketHeadCallBack = [this, self](boost::system::error_code ec, size_t)
    {
        if (!ec && mReceiveDataPacket.decodeDataHead())
        {
            receiveDataBody();
        }
    };
    boost::asio::async_read(mClientSocket, boost::asio::buffer(mReceiveDataPacket.getDataPacket(), DATA_HEAD_LENGTH), mClientStrand.wrap(receiveDataPacketHeadCallBack));
}

CClient::CClient(tcp::socket aSocket, io_service& aIoService)
    : mClientSocket(move(aSocket)), mClientStrand(aIoService), mClientName(""), mIsLogin(false)
{
}

void CClient::startReceiveDataPacket()
{
    receiveDataPacketHead();
}

void CClient::testClientOnline()
{
    CDataPacket dataPacket;
    dataPacket.buildTestClientOnline(false);
    pushDataPacketIntoSendQueue(dataPacket);
}

bool CClient::getClientIsLogin()
{
    return this->mIsLogin;
}

void CListen::acceptClientConnect()
{
    auto acceptClientConnectCallBack = [this](boost::system::error_code ec)
    {
        if (!ec)
        {
            CClientPtr client = make_shared<CClient>(move(mListenSocket), mIOService);
            mClientPtrList.emplace_back(client);
            client->startReceiveDataPacket();
        }
        acceptClientConnect();
    };
    mAcceptor.async_accept(mListenSocket, mListenStrand.wrap(acceptClientConnectCallBack));
}

void CListen::testClientListOnline()
{
    for (auto clientPtr : mClientPtrList)
    {
        if (clientPtr->getClientIsLogin())
            clientPtr->testClientOnline();
    }
    mTestClientOnlineTimer.expires_at(mTestClientOnlineTimer.expires_at() + chrono::seconds(5));
    auto lbdTestClientOnline = [this](const boost::system::error_code& ec)
    {
        if (!ec)
        {
            testClientListOnline();
        }
    };
    mTestClientOnlineTimer.async_wait(mListenStrand.wrap(lbdTestClientOnline));
}

CListen::CListen(io_service& ioService, const tcp::endpoint& endPoint)
    : mIOService(ioService), mListenSocket(ioService), mAcceptor(ioService, endPoint), mListenStrand(ioService), mTestClientOnlineTimer(ioService, chrono::seconds(5))
{
    acceptClientConnect();
    auto lbdTestClientOnline = [this](const boost::system::error_code& ec)
    {
        if (!ec)
        {
            testClientListOnline();
        }
    };
    mTestClientOnlineTimer.async_wait(mListenStrand.wrap(lbdTestClientOnline));
}

CServer::CServer(int& argc, char** argv)
{
    for (int i=1; i<argc; ++i)  //监听端口的数量，几个参数，argc就是几
    {
        tcp::endpoint endpoint(tcp::v4(), atoi(argv[i]));
        mListenList.emplace_back(mIOService, endpoint);
    }
}

void CServer::launch()
{
    try
    {
        for (int i=0; i<5; ++i)
        {
            auto runIoService = [this]()
            {
                mIOService.run();
            };
            mIOServiceThreadList.emplace_back(runIoService);
            //mIOServiceThreadList.emplace_back(bind(&CServer::ioServiceRun, this));    //线程在类方法里运行
        }
        BOOST_LOG_TRIVIAL(info) << "launch success!!";
        for (auto& t : mIOServiceThreadList)
        {
            t.join();   //等待每个线程退出
        }
    } catch (exception& e)
    {
        BOOST_LOG_TRIVIAL(info) << "launch failure, exception: " << e.what() << endl;
    }
}

bool CServer::isStopped() const
{
    return mIOService.stopped();
}

void CServer::stop()
{
    mIOService.stop();
}
