#pragma once 

#include <mutex> 

#include "Poco/Data/Session.h"
#include "Poco/Tuple.h"

#include "Poco/Dynamic/Struct.h"

#include "model/Chat.h"

#include "AR/Connection.h"
#include "AR/MessageAR.h"

#include "exception/UserNotFoundException.h"
#include "exception/UserBlockingException.h"

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Tuple;

using Poco::DynamicStruct;


class ChatAR 
{
    
private:
    std::vector<std::unique_ptr<MessageAR>> _msgARs;
    std::unique_ptr<Chat> _chat;

public:

    using Row = Tuple<int, std::string, std::string>;
    using Conds = DynamicStruct;

    ChatAR(Chat* chat);
    Chat* getChat() 
    {
        return _chat.get();
    }

    bool remove();
    bool update(Chat& chat);
    bool updateUsers(const std::set<std::string>& logins);
    bool addUser(const std::string& login);
    bool deleteUser(const std::string& login);

    void retrieveMessages();

    static std::vector<std::unique_ptr<ChatAR>> getByFilter(Conds& cnds);
    static std::unique_ptr<ChatAR> create(Chat& chat);

    static std::vector<std::string> INFO_TABLE_COL, REL_TABLE_COL, ROW_PARAM, GROUP_PARAM;
    static std::map<std::string, std::string> PARAMS_CNDS, PARAMS_COL;

    static std::string CHAT_REL_TABLE, CHAT_INFO_TABLE;

};