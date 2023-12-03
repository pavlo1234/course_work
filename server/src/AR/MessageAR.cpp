
#include <mutex>

#include "AR/MessageAR.h"
#include "AR/Connection.h"

#include "Poco/Data/MySQL/MySQLException.h"
#include "Poco/Exception.h"


MessageAR::MessageAR(Message* msg) : _msg(msg) {}


std::unique_ptr<MessageAR> MessageAR::create(Message& msg) 
{
    
    int id;
    Session ses = DBConnection::get()->session();
    Statement stmt(ses);
   
    stmt << "INSERT INTO %s (login, cid, mtext, mtime) VALUES (?, ?, ?, ?)",
        MessageAR::MESSAGES_TABLE,
        bind(msg.getLogin()),
        bind(msg.getCID()),
        bind(msg.getText()),
        bind(msg.getDateTime());
    stmt.execute();

    ses << "SELECT last_insert_id()",
        into(id), now;
    msg.setID(id);
    
    return std::unique_ptr<MessageAR>(new MessageAR(new Message(msg)));
}

std::vector<std::unique_ptr<MessageAR>> MessageAR::getByFilter(Conds& cnds)
{
    
    std::vector<MessageAR::Row> msgs;


    Session ses(DBConnection::get()->session());
    Statement stmt(ses);

    stmt << "SELECT * FROM %s",
        MessageAR::MESSAGES_TABLE, into(msgs);

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

    std::vector<std::unique_ptr<MessageAR>> msgARs;
    for (MessageAR::Row& row : msgs) {
        msgARs.push_back(std::unique_ptr<MessageAR>(new MessageAR(new Message(row.get<0>(), row.get<2>(), row.get<1>(), row.get<3>(), row.get<4>()))));
    }
    return msgARs;

}


std::string MessageAR::MESSAGES_TABLE = "messages";

std::vector<std::string> MessageAR::TABLE_COL = {"id", "cid", "login", "mtext", "mtime"};

std::vector<std::string> MessageAR::ROW_PARAM = {"id", "cid", "login", "dt-from"};
std::vector<std::string> MessageAR::GROUP_PARAM = {};

std::map<std::string, std::string> MessageAR::PARAMS_COL= {
    {"id", MessageAR::MESSAGES_TABLE+"."+TABLE_COL[0]},
    {"cid", MessageAR::MESSAGES_TABLE+"."+TABLE_COL[1]},
    {"login", MessageAR::MESSAGES_TABLE+"."+TABLE_COL[2]},
    {"text", MessageAR::MESSAGES_TABLE+"."+TABLE_COL[3]},
    {"dt-from", MessageAR::MESSAGES_TABLE+"."+TABLE_COL[4]}
};

std::map<std::string, std::string> MessageAR::PARAMS_CNDS = {
    {"id", PARAMS_COL["id"]+"=?"},
    {"cid", PARAMS_COL["cid"]+"=?"},
    {"login", PARAMS_COL["login"]+"=?"},
    {"dt-from", PARAMS_COL["dt-from"]+">?"}
};
