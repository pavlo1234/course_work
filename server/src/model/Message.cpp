
#include "Poco/DateTimeFormatter.h"

#include "model/Message.h"



Message::Message(int id, const std::string& login, int cid, const std::string& text, const DateTime& dt)
    : _id(id), _login(login), _cid(cid), _text(text), _dt(dt) {}

Message::Message(const std::string& login, int cid, const std::string& text, const DateTime& dt)
    : _login(login), _cid(cid), _text(text), _dt(dt) {}

std::string Message::toJSON()
{
    std::string json = "{";
    json += "\"id\":" + std::to_string(_id) + ",";
    json += "\"login\":\"" + _login + "\",";
    json += "\"cid\":" + std::to_string(_cid) + ",";
    json += "\"text\":\"" + _text + "\",";
    json += "\"datetime\":\"" + Poco::DateTimeFormatter::format(_dt, DATETIME_FORMAT, 0) + "\"";
    json += "}";
    return json;
}

std::string Message::DATETIME_FORMAT = "%Y-%m-%d %H:%M:%S";