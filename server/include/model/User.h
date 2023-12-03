#pragma once

#include "Poco/Dynamic/Var.h"

#include "interface/Serializable.h"
#include "model/Chat.h"

class User : public Serializable
{
private:
    std::string _login, _password, _email;
    std::vector<Chat> _chats;           
    std::set<std::string> _blocked_users;

public:
    User() {}
    
    User(const std::string& login, const std::string& password);
    User(const std::string& login, const std::string& password, const std::string& email);
    User(const std::string& login, const std::string& password, const std::string& email,
        const std::vector<Chat>& chats);
    User(const std::string& login, const std::string& password, const std::string& email,
        const std::vector<Chat>& chats, const std::set<std::string>& blocked_users);
    
    void setLogin(const std::string& login)
    {
        this->_login = login;
    }
    std::string& getLogin() 
    {
        return this->_login;
    }
    
    void setPassword(const std::string& password) 
    {
        this->_password = password;
    }
    std::string& getPassword() 
    {
        return this->_password;
    }

    void setEmail(const std::string& email)
    {
        _email = email;
    }
    
    std::string& getEmail()
    {
        return _email;
    }

    void setChats(const std::vector<Chat>& chats)
    {
        _chats = chats;
    }
    std::vector<Chat>& getChats()
    {
        return _chats;
    }

    void setBlockedUsers(const std::set<std::string>& logins)
    {
        _blocked_users = logins;
    }
    std::set<std::string>& getBlockedUsers()
    {
        return _blocked_users;
    }

    std::string toJSON();
    static User fromJSON(const Poco::Dynamic::Var& data);

};