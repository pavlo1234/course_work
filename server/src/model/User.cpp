#include "model/User.h"

User::User(const std::string& login, const std::string& password) : 
    _login(login), _password(password) {}

User::User(const std::string& login, const std::string& password, const std::string& email) : 
    _login(login), _password(password), _email(email) {}

User::User(const std::string& login, const std::string& password, const std::string& email,
    const std::vector<Chat>& chats) : 
        _login(login), _password(password), _email(email), _chats(chats) {}

User::User(const std::string& login, const std::string& password, const std::string& email,
    const std::vector<Chat>& chats, const std::set<std::string>& logins) : 
        _login(login), _password(password), _chats(chats), _email(email), _blocked_users(logins) {}

std::string User::toJSON() 
{
    std::string json = "{";

    json += "\"login\":\"" + _login + "\",";
    json += "\"password\":\"" + _password + "\",";
    json += "\"email\":\"" + _email + "\",";
    json += "\"chats\": [";
    for(int i = 0; i < _chats.size(); i++){
        json += _chats[i].toJSON(); 
        if(i != _chats.size()-1) json += ',';
    }
    json += "],";
    json += "\"blocked_users\": [";
    for(auto it = _blocked_users.begin(); it != _blocked_users.end(); it++){
        json += *it; 
        if(it != (--_blocked_users.end())) json += ',';
    }
    json += ']';

    json += "}";
    return json;
    
}

User User::fromJSON(const Poco::Dynamic::Var& data)
{
    std::string login, password, email;
    std::vector<Chat> chats;
    std::set<std::string> blocked_users;
    try {
        login = data["login"].convert<std::string>();
        password = data["password"].convert<std::string>();
        email = data["email"].convert<std::string>();
        for(auto& i : data["chats"])
            chats.push_back(Chat::fromJSON(i));
        for(auto& i : data["blocked_users"])
            blocked_users.insert(i.convert<std::string>());
    }
    catch(const Poco::Exception& ex) {}

    return User(login, password, email, chats, blocked_users);
}