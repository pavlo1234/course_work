#pragma once

#include <QtCore>

#include "model/Chat.h"

class User
{
private:
    QString _login, _password;
    std::vector<Chat> _chats;           

public:
    User() {}
    User(const User&) = default;
    User(const QString& login, const QString& password);
    User(const QString& login, const QString& password, 
        const std::vector<Chat>& chats);
    
    void setLogin(const QString& login)
    {
        this->_login = login;
    }
    QString& getLogin() 
    {
        return this->_login;
    }
    
    void setPassword(const QString& password) 
    {
        this->_password = password;
    }
    QString& getPassword() 
    {
        return this->_password;
    }

    void setChats(const std::vector<Chat>& chats)
    {
        _chats = chats;
    }
    std::vector<Chat>& getChats()
    {
        return _chats;
    }

    QString toJSON();
    static User fromJSON(const QJsonValue& obj);

};

