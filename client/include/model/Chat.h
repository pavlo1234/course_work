#pragma once

#include <vector>

#include "model/Message.h"

class Chat
{
private:
    int _id;
    QString _title;
    std::vector<QString> _ulogins;
    std::vector<Message> _msgs;

public:
    Chat() {}
    Chat(const Chat& chat) = default; 

    Chat(int& id, const QString& title, const std::vector<QString>& ulogins);
    Chat(const QString& title, const std::vector<QString>& ulogins);
    Chat(const QString& title, const std::vector<QString>& ulogins, std::vector<Message>& msgs);

   
    int getID() 
    {
        return _id;
    }
    void setID(const int& id)
    {
        _id = id;
    }

    void setTitle(const QString& title)
    {
        _title = title;
    }
    QString& getTitle()
    {
        return _title;
    }

    std::vector<QString>& getLogins() 
    {
        return _ulogins;
    }
    void setLogins(std::vector<QString>& ulogins)
    {
        _ulogins = ulogins;
    }

    std::vector<Message> getMessages() 
    {
        return _msgs;
    }
    void setMessages(std::vector<Message>& msgs)
    {
        _msgs = msgs;
    }

    QString toJSON();
    static Chat fromJSON(const QJsonObject& obj);

};

