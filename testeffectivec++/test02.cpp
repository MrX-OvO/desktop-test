#include <iostream>
#include <string>

class CompanyA
{
public:
    void sendCleartext(const std::string &msg);
    void sendEncrypted(const std::string &msg);
};

class CompanyB
{
public:
    void sendCleartext(const std::string &msg);
    void sendEncrypted(const std::string &msg);
};

class MsgInfo
{
public:
    std::string createCleartext() const;
    std::string createEncryptedtext() const;
};

template <typename Company>
class MsgSender
{
public:
    void sendClear(const MsgInfo &info)
    {
        std::string msg;
        msg = info.createCleartext();
        Company c;
        c.sendCleartext(msg);
    }
    void sendSecret(const MsgInfo &info)
    {
        std::string msg;
        msg = info.createEncryptedtext();
        Company c;
        c.sendEncrypted(msg);
    }
};

template <typename Company>
class LoggingMsgSender : public MsgSender<Company>
{
public:
    //using MsgSender<Company>::sendClear;
    void sendClearMsg(const MsgInfo &info)
    {
        // MsgSender<Company>::sendClear(info);
        this->sendClear(info);
    }
};

int main(int argc, char const *argv[])
{

    return 0;
}
