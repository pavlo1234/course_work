#pragma once

#include <string>
#include <QJsonObject>

class Serializable 
{
public:
    virtual std::string toJSON() = 0;
};