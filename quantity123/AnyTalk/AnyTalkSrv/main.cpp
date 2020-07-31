#include "../DataPacket/DataPackageStruct/Protocal.pb.h"
#include "Server/server.h"

using namespace std;

void initLogLevel()
{
    auto corePtr = boost::log::core::get();
    corePtr->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
}

static function<void()> lbd_serverSafeQuit;

void serverSafeQuit(int sig)
{
    BOOST_LOG_TRIVIAL(info) << "handle system signal " << sig;
    if (lbd_serverSafeQuit)
    {
        lbd_serverSafeQuit();
        lbd_serverSafeQuit = nullptr;
    }
}

int main(int argc, char* argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    initLogLevel();
    if (argc < 2)
    {
        BOOST_LOG_TRIVIAL(info) << "Usage: ChatServer [<port>...]";
        return 1;
    }
    BOOST_LOG_TRIVIAL(info) << "Server Starting.....";
    signal(SIGINT, serverSafeQuit);
    CServerPtr serverPtr = make_unique<CServer>(argc, argv);
    lbd_serverSafeQuit = [&serverPtr]()
    {
        if (!serverPtr->isStopped())
            serverPtr->stop();
        return 1;
    };
    serverPtr->launch();
    google::protobuf::ShutdownProtobufLibrary();
    BOOST_LOG_TRIVIAL(info) << "Server Stoped.....";
    return 0;
}
