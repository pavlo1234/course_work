
#include <iostream>

#include "Poco/Exception.h"

#include "AR/UserAR.h"
#include "AR/ChatAR.h"



UserAR::UserAR(User* user): _user(user) {}

bool UserAR::create(User& user)
{
    Session ses(DBConnection::get()->session());
    Statement stmt(ses);
    try {
        stmt << "INSERT INTO %s (login, pswd, email) VALUES(?,MD5(?),?)", 
        bind(user.getLogin()),
        bind(user.getPassword()), 
        bind(user.getEmail()),
        USERS_TABLE;

        stmt.execute();
    }
    catch(const Poco::Exception& ex) {
        throw UserDuplicateException();
    }
    return true;

}

UserAR* UserAR::getByLogin(const std::string& login)
{
    UserAR::Row user;

    Session ses(DBConnection::get()->session());
    Statement stmt(ses);
    stmt << "SELECT * FROM %s WHERE login=?", 
        bind(login), 
        into(user),
        USERS_TABLE;
    
    stmt.execute();
    if(stmt.rowsExtracted() == 1) {
        return new UserAR(new User(user.get<0>(), user.get<1>()));
    }
    else throw UserNotFoundException();
    return nullptr;
}

UserAR* UserAR::getByCredentials(const std::string& login, const std::string& password) 
{    
    UserAR::Row user;
    
    Session ses(DBConnection::get()->session());
    Statement stmt(ses);
    stmt << "SELECT * FROM %s WHERE login=? AND pswd=MD5(?)", 
        USERS_TABLE,
        bind(login), 
        bind(password),
        into(user);
    stmt.execute();

    if(stmt.rowsExtracted() == 1) 
        return new UserAR(new User(user.get<0>(), user.get<1>()));
    else throw UserNotFoundException();
    
}

std::vector<std::unique_ptr<UserAR>> UserAR::getByFilter(Conds& cnds)
{
    std::vector<UserAR::Row> users;
    Session ses(DBConnection::get()->session());
    Statement stmt(ses);

    stmt << "SELECT * FROM %s",
        UserAR::USERS_TABLE, into(users);

    std::vector<std::string> row_param;
    for(auto& param : ROW_PARAM) {
        if(cnds.find(param) != cnds.end()) {
            row_param.push_back(param);
        }
    }
    for (int i = 0; i < row_param.size(); i++) {
        if (i == 0) stmt << " WHERE ";
        stmt << PARAMS_CNDS[row_param[i]],
            bind(cnds[row_param[i]]);
        if (i != row_param.size() - 1) stmt << " AND ";
    }

    stmt.execute();

    std::vector<std::unique_ptr<UserAR>> userARs;
    for (UserAR::Row& row : users) {
        userARs.push_back(std::unique_ptr<UserAR>(new UserAR(new User(row.get<0>(), row.get<1>(), row.get<2>()))));
    }

    return userARs;

}

std::set<std::string>& UserAR::blocked_users()
{
    
    std::set<std::string> logins;
    Session ses(DBConnection::get()->session());
    Statement stmt(ses);
    stmt << "SELECT login_blocked FROM %s where login_blocker=?",
        USERS_BLACKLIST_TABLE,
        bind(getUser()->getLogin()),
        into(logins);
    stmt.execute();

    getUser()->setBlockedUsers(logins);
    return getUser()->getBlockedUsers();
}

std::vector<std::unique_ptr<ChatAR>>& UserAR::chats(ChatAR::Conds& cnds) 
{
    cnds.insert("login", getUser()->getLogin());
    _chatARs = ChatAR::getByFilter(cnds);
    std::vector<Chat> chats;
    for(auto& chatAR : _chatARs) {
        if(chatAR.get() != nullptr){
            chatAR.get()->retrieveMessages();
            chats.push_back(*chatAR->getChat());
        }
    }
    _user->setChats(chats);
    return _chatARs;
}

bool UserAR::block(std::set<std::string>& logins)
{
    
    try {
    Session ses(DBConnection::get()->session());
    Statement stmt(ses);
    stmt << "INSERT INTO %s (login_blocker, login_blocked) VALUES ('%s', ?)", 
        USERS_BLACKLIST_TABLE,
        getUser()->getLogin(), 
        bind(logins);
    stmt.execute();
    }
    catch(const Poco::Exception& ex) {
        return false;
    }
   
    for(auto& chatAR: _chatARs) {
        for(auto login = logins.begin(); login != logins.end(); login++){
            std::set<std::string>& chat_logins = chatAR->getChat()->getLogins();
            std::string l = *login;
            if(chat_logins.find(l) != chat_logins.end()) {
                chatAR->deleteUser(getUser()->getLogin());
                break;
            }
        }
    }
    
    return true;
}

bool UserAR::unblock(std::set<std::string>& logins)
{
    
    Session ses(DBConnection::get()->session());
    Statement stmt(ses);
    stmt << "DELETE FROM %s WHERE login_blocker='%s' AND login_blocked=?", 
        USERS_BLACKLIST_TABLE,
        getUser()->getLogin(), 
        bind(logins);
    stmt.execute();
    
    return true;
}

std::string UserAR::USERS_TABLE = "users", UserAR::USERS_BLACKLIST_TABLE = "users_bl";


std::vector<std::string> UserAR::TABLE_COL = {"login", "email", "pswd"};

std::vector<std::string> UserAR::ROW_PARAM = {"login", "email", "pswd"};
std::vector<std::string> UserAR::GROUP_PARAM = {};

std::map<std::string, std::string> UserAR::PARAMS_COL= {
    {"login", UserAR::USERS_TABLE+"."+TABLE_COL[0]},
    {"password", UserAR::USERS_TABLE+"."+TABLE_COL[2]},
    {"email", UserAR::USERS_TABLE+"."+TABLE_COL[1]}
};

std::map<std::string, std::string> UserAR::PARAMS_CNDS = {
    {"login", PARAMS_COL["login"]+"=?"},
    {"password", PARAMS_COL["password"]+"=?"},
    {"email", PARAMS_COL["email"]+"=?"}
};