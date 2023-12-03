
#include "AR/Connection.h"

#include "Poco/Data/SessionFactory.h"

using Poco::Data::SessionFactory;


DBConnection* DBConnection::instance = nullptr;

DBConnection::DBConnection(const std::string& key, const std::string& conn)
    : _pool(SessionPool(key, conn)), _session(key, conn) {}

void DBConnection::init(const std::string& key, const std::string& conn)
{
    instance = new DBConnection(key, conn);
}

DBConnection* DBConnection::get()
{
    return DBConnection::instance;
}

Session DBConnection::session() 
{
    return _pool.get(); // Session(KEY, CONN_STR);//  _session;//
}