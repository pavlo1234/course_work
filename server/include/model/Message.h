#pragma once

#include "Poco/DateTime.h"
#include "interface/Serializable.h"

using Poco::DateTime;

class Message: public Serializable
{
private:
    int _id, _cid;
    std::string _login, _text;
    DateTime _dt;

public:
    Message() {}
    
    Message(int id, const std::string& login, int cid, const std::string& text, const DateTime& dt);
    Message(const std::string& login, int cid, const std::string& text, const DateTime& dt);

    int getID() {
        return _id;
    }
    void setID(const int& id) {
        _id = id;
    }

    std::string& getLogin(){
        return _login;
    }
    void setLogin(const std::string& login)
    {
        _login = login;
    }

    int getCID() {
        return _cid;
    }
    void setCID(const int& cid) {
        _cid = cid;
    }

    std::string& getText(){
        return _text;
    }
    void setText(const std::string& text)
    {
        _text = text;
    }

    DateTime& getDateTime()
    {
        return _dt;
    }
    void setDateTime(const DateTime& dt)
    {
        _dt = dt;
    }

    std::string toJSON();

    static std::string DATETIME_FORMAT;

};