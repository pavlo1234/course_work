#pragma once

#include <mutex>

#include "Poco/Data/Session.h"
#include "Poco/DateTime.h"
#include "Poco/Tuple.h"

#include "Poco/Dynamic/Struct.h"

#include "model/Message.h"

#include "AR/Connection.h"


using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Tuple;
using Poco::DateTime;
using Poco::DynamicStruct;


class MessageAR 
{   

private:
    std::unique_ptr<Message> _msg;
public:

    using Row = Tuple<int, int, std::string, std::string, DateTime>;
    using Conds = DynamicStruct;

    MessageAR(Message* msg);
    Message* getMessage()
    {
        return _msg.get();
    }

    static std::unique_ptr<MessageAR> create(Message& msg);

    static std::vector<std::unique_ptr<MessageAR>> getByFilter(Conds& cnds);

    static std::vector<std::string> TABLE_COL, ROW_PARAM, GROUP_PARAM;
    static std::map<std::string, std::string> PARAMS_CNDS, PARAMS_COL;
    static std::string MESSAGES_TABLE;
    
};