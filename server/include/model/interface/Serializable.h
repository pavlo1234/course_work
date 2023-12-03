#pragma once

#include <string>

class Serializable 
{
public:
    virtual std::string toJSON() = 0;
};