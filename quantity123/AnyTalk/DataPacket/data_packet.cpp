#include "data_packet.h"

void CDataPacket::ParseMessageFromProtobuf(::google::protobuf::Message* aProtobufMSG)
{
    string s(mDataPacket+DATA_HEAD_LENGTH, mDataPacket+DATA_HEAD_LENGTH+mDataHead.dataBodyLength);   //数据包(字节数组)中取body部分赋值给初始化的字符串
    aProtobufMSG->ParseFromString(s);
}

void CDataPacket::setDataPacket(DataBodyType aDataBodyType, const void* aBuffer, size_t aBufferLength)
{
    assert(aBufferLength <= MAX_DATA_BODY_LENGTH);
    mDataHead.dataBodyType = aDataBodyType;
    mDataHead.dataBodyLength = aBufferLength;
    memcpy(mDataPacket, &mDataHead, sizeof(mDataHead));
    memcpy(mDataPacket+DATA_HEAD_LENGTH, aBuffer, aBufferLength);
}

void CDataPacket::setDataPacket(DataBodyType aDataBodyType, const string& aBuffer)
{
    setDataPacket(aDataBodyType, aBuffer.data(), aBuffer.size());
}

CDataPacket::CDataPacket()
{
}

bool CDataPacket::decodeDataHead()
{
    memcpy(&mDataHead, getDataPacket(), DATA_HEAD_LENGTH);
    if (mDataHead.dataBodyLength > MAX_DATA_BODY_LENGTH)
    {
        BOOST_LOG_TRIVIAL(fatal) << "body size " << mDataHead.dataBodyLength << " " << mDataHead.dataBodyType;
        return false;
    }
    return true;
}

DataBodyType CDataPacket::getDataBodyType() const
{
    return mDataHead.dataBodyType;
}

size_t CDataPacket::getDataBodyLength() const
{
    return mDataHead.dataBodyLength;
}

char* CDataPacket::getDataBody()
{
    return mDataPacket + DATA_HEAD_LENGTH;
}

size_t CDataPacket::getDataPacketLength() const
{
    return DATA_HEAD_LENGTH + mDataHead.dataBodyLength;
}

char* CDataPacket::getDataPacket()
{
    return mDataPacket;
}

string CDataPacket::getClientName()
{
    PClientLogin clientLogin;
    ParseMessageFromProtobuf(&clientLogin);
    return clientLogin.loginname();
}

void CDataPacket::buildClientLoginFeedback()
{
    PClientLoginFeedback clientLoginFeedBack;
    clientLoginFeedBack.set_success(true);
    string buf;
    clientLoginFeedBack.SerializeToString(&buf);
    setDataPacket(DBT_CLIENT_LOGIN_FEED_BACK, buf);
}

bool CDataPacket::getClientIsOnline()
{
    PClientIsOnline clientIsOnline;
    ParseMessageFromProtobuf(&clientIsOnline);
    return clientIsOnline.online();
}

bool CDataPacket::buildClientLogin(string& input)
{
    auto pos = input.find_first_of(":");    //返回字符串中第一个 冒号 的位置
    if (pos == string::npos)    //npos表示没找到
        return false;
    if (pos == 0)
        return false;
    auto command = input.substr(0, pos);    //取出从0位置到pos位置之间的字符赋值给command
    if (command == "LoginName")
    {
        string loginName = input.substr(pos + 1);    //取出pos+1位置到结尾之间的字符
        if (loginName.size() > 32)   //登陆名不能超过32个字节大小
            return false;
        PClientLogin clientLogin;
        clientLogin.set_loginname(loginName);
        string buf;
        auto ok = clientLogin.SerializeToString(&buf);
        if (ok)
        {
            this->setDataPacket(DBT_CLIENT_LOGIN, buf);
            return ok;
        }
    }
    return false;
}

bool CDataPacket::getClientLoginFeedback()
{
    PClientLoginFeedback clientLoginFeedback;
    ParseMessageFromProtobuf(&clientLoginFeedback);
    return clientLoginFeedback.success();
}

void CDataPacket::buildTestClientOnline(bool aOnline)
{
    PClientIsOnline clientIsOnline;
    clientIsOnline.set_online(aOnline);
    string buf;
    clientIsOnline.SerializeToString(&buf);
    setDataPacket(DBT_TEST_CLIENT_ONLINE, buf);
}
