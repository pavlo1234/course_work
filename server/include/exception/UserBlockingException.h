#pragma once

#include <exception>

class UserBlockingException: std::exception
{
public:
    const char* what() const;
};