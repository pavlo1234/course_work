#pragma once

#include <vector>
#include <set>

#include "Poco/Dynamic/Struct.h"
#include "Poco/Dynamic/Var.h"

#include "interface/Serializable.h"
#include "model/Message.h"


class Chat : public Serializable
{
private:
    int _id;
    std::string _title, _creator;
    std::set<std::string> _ulogins;
    std::vector<Message> _msgs;

public:
    Chat() {}

    Chat(int& id, const std::string& title, const std::string& creator, const std::set<std::string>& ulogins);
    Chat(const std::string& title, const std::string& creator, const std::set<std::string>& ulogins);
    Chat(const std::string& title, const std::string& creator, const std::set<std::string>& ulogins, std::vector<Message>& msgs);

   
    int getID() 
    {
        return _id;
    }
    void setID(const int& id)
    {
        _id = id;
    }

    void setTitle(const std::string& title)
    {
        _title = title;
    }
    std::string& getTitle()
    {
        return _title;
    }

    void setCreator(const std::string& creator)
    {
        _creator = creator;
    }
    std::string& getCreator()
    {
        return _creator;
    }

    std::set<std::string>& getLogins() 
    {
        return _ulogins;
    }
    void setLogins(const std::set<std::string>& ulogins)
    {
        _ulogins = ulogins;
    }

    std::vector<Message>& getMessages() 
    {
        return _msgs;
    }
    void setMessages(const std::vector<Message>& msgs)
    {
        _msgs = msgs;
    }


    std::string toJSON();
    static Chat fromJSON(const Poco::Dynamic::Var& data);
    

};