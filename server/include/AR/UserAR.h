#pragma once

#include "Poco/Data/Session.h"
#include "Poco/Tuple.h"

#include "model/User.h"

#include "AR/Connection.h"
#include "AR/ChatAR.h"
#include "exception/UserNotFoundException.h"
#include "exception/UserDuplicateException.h"


using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Tuple;


class UserAR 
{
   
private:
    std::vector<std::unique_ptr<ChatAR>> _chatARs;
    std::unique_ptr<User> _user;
public:

    using Row = Tuple<std::string, std::string, std::string>;
    using Conds = DynamicStruct;

    UserAR(User* user);
    User* getUser() 
    {
        return _user.get();
    }
    std::vector<std::unique_ptr<ChatAR>>& getChats() 
    {
        return _chatARs;
    }

    std::vector<std::unique_ptr<ChatAR>>& chats(ChatAR::Conds& cnds = ChatAR::Conds());
    bool block(std::set<std::string>& logins);
    bool unblock(std::set<std::string>& logins);
    std::set<std::string>& blocked_users();
    
    static bool create(User& user);
    static UserAR* getByLogin(const std::string& login);
    static UserAR* getByCredentials(const std::string& login, const std::string& password);
    static std::vector<std::unique_ptr<UserAR>> getByFilter(Conds& cnds);

    static std::vector<std::string>  TABLE_COL, ROW_PARAM, GROUP_PARAM;
    static std::map<std::string, std::string> PARAMS_CNDS, PARAMS_COL;
    static std::string USERS_TABLE, USERS_BLACKLIST_TABLE;


};