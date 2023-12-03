

#include <regex>

#include "Poco/Exception.h"

#include "AR/ChatAR.h"
#include "AR/UserAR.h"


ChatAR::ChatAR(Chat* chat): _chat(chat) {}

void ChatAR::retrieveMessages()
{
    Conds cnds;
    cnds.insert("cid", getChat()->getID());
    
    _msgARs = MessageAR::getByFilter(cnds);

    std::vector<Message> msgs;
    for(auto& msgAR : _msgARs){
        if(msgAR.get() != nullptr)
            msgs.push_back(*msgAR->getMessage());
    }
    
    _chat->setMessages(msgs);
}

bool ChatAR::remove()
{

    Session ses(DBConnection::get()->session());
    Statement stmt(ses);
   
    stmt << "DELETE FROM %s WHERE id=?",
        ChatAR::CHAT_INFO_TABLE,
        bind(getChat()->getID());
    stmt.execute();
    

    return stmt.done();
}

std::unique_ptr<ChatAR> ChatAR::create(Chat& chat)
{

    std::vector<std::unique_ptr<UserAR>> usersAR;
    std::set<std::string> logins;
    for(const std::string& login : chat.getLogins()){
        UserAR* userAR = UserAR::getByLogin(login);
        if(userAR == nullptr) throw UserNotFoundException();

        usersAR.push_back(std::unique_ptr<UserAR>(userAR));
        userAR->blocked_users();
        logins.insert(userAR->getUser()->getBlockedUsers().begin(), userAR->getUser()->getBlockedUsers().end());
    }
    
    if(logins.find(chat.getCreator()) != logins.end()) 
        throw UserBlockingException();

    int cid;
    Session ses(DBConnection::get()->session());
    Statement stmt(ses);
   
    stmt << "INSERT INTO %s (title, creator) VALUES (?, ?)",
        ChatAR::CHAT_INFO_TABLE,
        bind(chat.getTitle()), 
        bind(chat.getCreator());
    stmt.execute();
    ses << "SELECT last_insert_id()", into(cid), now;

    chat.setID(cid);
    ses << "INSERT INTO %s (cid, login) VALUES (%d, ?)", 
        ChatAR::CHAT_REL_TABLE, 
        cid,
        use(chat.getLogins()), now;    
    return std::unique_ptr<ChatAR>(new ChatAR(new Chat(chat)));
}

bool ChatAR::update(Chat& chat) 
{

    Session ses(DBConnection::get()->session());
    Statement stmt(ses);

    stmt << "UPDATE TABLE %s SET title = ? WHERE id = ?",
        ChatAR::CHAT_INFO_TABLE,
        bind(chat.getTitle()), 
        bind(getChat()->getID());
    stmt.execute();

    bool res = updateUsers(chat.getLogins());  
    if(res) _chat = std::make_unique<Chat>(chat);

    return res;
}

bool ChatAR::updateUsers(const std::set<std::string>& logins)
{
    std::set<std::string> chat_logins = getChat()->getLogins();
    bool res = true;
    for(std::string login : logins){
        if(!res) return false;
        if(chat_logins.find(login) == chat_logins.end())
            res = deleteUser(login);
        else 
            res = addUser(login);
    }

    return true;

}

bool ChatAR::addUser(const std::string& login)
{

    Session ses(DBConnection::get()->session());
    Statement stmt(ses);

    stmt << "INSERT INTO %s (cid, login) VALUES (%d, ?)",
        ChatAR::CHAT_REL_TABLE,
        getChat()->getID(),
        bind(login);
    stmt.execute();

    return stmt.done();
}

bool ChatAR::deleteUser(const std::string& login)
{

    Session ses(DBConnection::get()->session());
    Statement stmt(ses);

    try{
    stmt << "DELETE FROM %s WHERE login = ? AND cid = ?", 
        ChatAR::CHAT_REL_TABLE,
        bind(login), 
        bind(getChat()->getID());
    stmt.execute();
    }
    catch(const Poco::Exception& ex) {
        return false;
    }

    return true;

}


std::vector<std::unique_ptr<ChatAR>> ChatAR::getByFilter(DynamicStruct& cnds) 
{

    std::vector<ChatAR::Row> chats;
    std::vector<std::string> logins;

    Session ses(DBConnection::get()->session());
    Statement stmt(ses);

    stmt << "SELECT %s.*, GROUP_CONCAT(%s SEPARATOR ',') AS \"login\" FROM %s INNER JOIN %s ON %s.%s=%s.%s",
        ChatAR::CHAT_INFO_TABLE, ChatAR::REL_TABLE_COL[2],
        ChatAR::CHAT_INFO_TABLE, ChatAR::CHAT_REL_TABLE,
        ChatAR::CHAT_INFO_TABLE, ChatAR::INFO_TABLE_COL[0],
        ChatAR::CHAT_REL_TABLE, ChatAR::REL_TABLE_COL[1],
        ChatAR::CHAT_INFO_TABLE, ChatAR::INFO_TABLE_COL[0];

    std::vector<std::string> row_param, group_param;
    for(auto& param : ROW_PARAM) 
        if(cnds.find(param) != cnds.end()) 
            row_param.push_back(param);

    for(int i = 0; i < row_param.size(); i++) {
        if(i == 0) stmt << " WHERE ";
        stmt << PARAMS_CNDS[row_param[i]],
            bind(cnds[row_param[i]]);
        if(i != row_param.size()-1) stmt << " AND ";
    }
  
    stmt << " GROUP BY %s.%s ",
        ChatAR::CHAT_INFO_TABLE, ChatAR::INFO_TABLE_COL[0];

    for(auto& param : GROUP_PARAM) 
        if(cnds.find(param) != cnds.end()) 
            group_param.push_back(param);
        

    for(int i = 0; i < group_param.size(); i++){
        if(i == 0) stmt << " HAVING ";
        stmt << PARAMS_CNDS[group_param[i]],
            bind(cnds[group_param[i]]);
        if(i != group_param.size()-1) stmt << " AND ";
    }
  
    stmt,
        into(chats),
        into(logins);
        
    stmt.execute();

    std::vector<std::unique_ptr<ChatAR>> chatARs;
    for(int i = 0; i < logins.size(); i++){
        std::smatch sm;
        std::regex reg("[^,]+");
        std::set<std::string> l;
        while(std::regex_search(logins[i], sm, reg)){
            for(int j = 0; j < sm.size(); j++) l.insert(sm.str(j));
            logins[i] = sm.suffix().str();
        }

        chatARs.push_back(std::unique_ptr<ChatAR>(new ChatAR(new Chat(chats[i].get<0>(), chats[i].get<1>(), chats[i].get<2>(), l))));
    }

    return chatARs;

}

std::string ChatAR::CHAT_INFO_TABLE = "chats", ChatAR::CHAT_REL_TABLE = "users_chats";

std::vector<std::string> ChatAR::INFO_TABLE_COL = {"id", "title"};
std::vector<std::string> ChatAR::REL_TABLE_COL = {"id", "cid", "login"};

std::vector<std::string> ChatAR::ROW_PARAM = {"id", "title", "id-from"};
std::vector<std::string> ChatAR::GROUP_PARAM = {"login"};

std::map<std::string, std::string> ChatAR::PARAMS_COL= {
    {"id", ChatAR::CHAT_INFO_TABLE+"."+INFO_TABLE_COL[0]},
    {"title", ChatAR::CHAT_INFO_TABLE+"."+INFO_TABLE_COL[1]},
    {"login", ChatAR::CHAT_REL_TABLE+"."+REL_TABLE_COL[2]},
    {"id-from", ChatAR::CHAT_INFO_TABLE+"."+INFO_TABLE_COL[0]}
};

std::map<std::string, std::string> ChatAR::PARAMS_CNDS = {
    {"id", PARAMS_COL["id"]+"=?"},
    {"title", PARAMS_COL["title"]+"=?"},
    {"login", "FIND_IN_SET(?, login)"},
    {"id-from", PARAMS_COL["id-from"]+">?"}
};
