
#include "model/Chat.h"

Chat::Chat(int& id, const std::string& title, const std::string& creator, const std::set<std::string>& ulogins) :
    _id(id), _title(title), _creator(creator), _ulogins(ulogins) {}
Chat::Chat(const std::string& title, const std::string& creator, const std::set<std::string>& ulogins) : 
    _title(title), _creator(creator), _ulogins(ulogins) {}
Chat::Chat(const std::string& title, const std::string& creator, const std::set<std::string>& ulogins, std::vector<Message>& msgs) : 
    _title(title), _creator(creator), _ulogins(ulogins), _msgs(msgs) {}

std::string Chat::toJSON() 
{
    std::string json = "{";
    
    json += "\"id\":" + std::to_string(_id) + ",";
    json += "\"title\":\"" + _title + "\",";
    json += "\"creator\":\"" + _creator + "\",";
    json += "\"ulogins\":[";
    for(auto it = _ulogins.begin(); it != _ulogins.end(); it++) {
        json += "\"" + *it +  "\"";
        if(it != --_ulogins.end()) json += ",";
    }
    json += "], ";
    json += "\"messages\": [";
    for(int i = 0; i < _msgs.size(); i++) {
        json += _msgs[i].toJSON();
        if(i != _msgs.size()-1) json += ",";
    }
    json += "]";

    json += "}";
    return json;
}

Chat Chat::fromJSON(const Poco::Dynamic::Var& data)
{
    Chat chat;
    try {
        chat.setID(data["id"].convert<int>());
        chat.setTitle(data["title"].convert<std::string>());
        chat.setCreator(data["creator"].convert<std::string>());
        for(Poco::Dynamic::Var& login : data["ulogins"])
            chat.getLogins().insert(login.convert<std::string>());
    }
    catch(const Poco::Exception& ex){}
    
    return chat;

}