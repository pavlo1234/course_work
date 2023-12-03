#pragma once

#include <sstream>

#include "Poco/URI.h"

#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPBasicCredentials.h"

#include "Poco/Dynamic/Var.h"
#include "Poco/Dynamic/Struct.h"

#include "Poco/JSON/Object.h"
#include "Poco/JSON/Parser.h"

#include "model/interface/Serializable.h"
#include "AR/Connection.h"

using Poco::Net::HTTPRequestHandler;
using Poco::Net::HTTPServerRequest;
using Poco::Net::HTTPServerResponse;
using Poco::Net::HTTPBasicCredentials;

using Poco::URI;

using Poco::Dynamic::Var;
using Poco::Dynamic::Array;

using Poco::JSON::Parser;
using Poco::JSON::Object;

using Data = Poco::DynamicStruct;
using SerializableList = std::vector<Serializable*>;
using SerializableData = std::vector<std::pair<std::string, SerializableList>>;

class RequestHandler: public HTTPRequestHandler
{
public:
    Data getQueryParameters(HTTPServerRequest& request) 
    {
        Data prms;
        for(std::pair<std::string, std::string> p : URI(request.getURI()).getQueryParameters())
            prms.insert(p.first, p.second);
        return prms;
    }

    Data getJSONData(HTTPServerRequest& request) 
    {
        std::stringbuf buff;
        request.stream().get(buff);
        Var obj = Parser().parse(buff.str());
        return Object::makeStruct(obj.extract<Object::Ptr>());
    }

    virtual std::string prepareResponse(const SerializableData& data)
    {
        std::string json = "{";
        int N = data.size();
        for(int i = 0; i < N; i++) {
            auto& part = data[i];
            auto& items = part.second;
            int k = items.size();

            json += "\""+part.first+"\":";
            if(k == 0) json += "{}";
            else if(k == 1) json += items[0]->toJSON();
            else {
                json += "[";
                for(int j = 0; j < items.size(); j++) {
                    json += items[j]->toJSON();
                    if(j != items.size()-1) json += ",";
                }
                json += "]";
            }
            if(i != N-1) json += ",";
        }
        json += "}";

        return json;
    }

};