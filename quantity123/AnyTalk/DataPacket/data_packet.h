#ifndef MESSAGE_H
#define MESSAGE_H
#include <cstddef>
#include <cstring>
#include <string>
#include <string.h>
#include <boost/log/trivial.hpp>
#include "../DataPacket/DataPackageStruct/Protocal.pb.h"

using namespace std;

enum DataBodyType
{
    DBT_CLIENT_LOGIN,
    DBT_CLIENT_LOGIN_FEED_BACK,
    DBT_TEST_CLIENT_ONLINE,
};

struct DataHead
{
    DataBodyType dataBodyType;   //body数据类型，比如客户端登陆，服务器测试客户端是否在线
    unsigned int dataBodyLength;
};

const unsigned short DATA_HEAD_LENGTH(sizeof(DataHead));
const unsigned short MAX_DATA_BODY_LENGTH(512);

class CDataPacket
{
private:
    DataHead mDataHead;
    char mDataPacket[DATA_HEAD_LENGTH+MAX_DATA_BODY_LENGTH];
    void ParseMessageFromProtobuf(::google::protobuf::Message* aProtobufMSG);
    void setDataPacket(DataBodyType aDataBodyType, const void* aBuffer, size_t aBufferLength);
    void setDataPacket(DataBodyType aDataBodyType, const string& aBuffer);
public:
    CDataPacket();
    bool decodeDataHead();
    DataBodyType getDataBodyType() const;
    size_t getDataBodyLength() const;
    char* getDataBody();
    size_t getDataPacketLength() const;
    char* getDataPacket();

    string getClientName();
    void buildClientLoginFeedback();
    bool getClientIsOnline();
    bool buildClientLogin(string& input);
    bool getClientLoginFeedback();
    void buildTestClientOnline(bool aOnline);
};

#endif // MESSAGE_H
