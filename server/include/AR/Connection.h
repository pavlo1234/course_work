#pragma once

#include <mutex>

#include "Poco/Data/Session.h"
#include "Poco/Data/SessionPool.h"
#include "Poco/Data/MySQL/Connector.h"

using Poco::Data::Session;
using Poco::Data::SessionPool;

const std::string host = "localhost";
const std::string port = "3306";
const std::string db = "messageapp";
const std::string user = "root";
const std::string pswd = "wasertyt111";

const std::string KEY = "MySQL";

const std::string CONN_STR = "host=" + host + ";" + \
                   "port=" + port + ";" + \
                   "db=" + db + ";" + \
                   "user=" + user + ";" + \
                   "password=" + pswd;


class DBConnection {
private:
    SessionPool _pool;
    Session _session;
    static DBConnection* instance;
    DBConnection(const std::string& key, const std::string& conn);
public:
    Session session();
    static void init(const std::string& key, const std::string& conn);
    static DBConnection* get();
   
};