#pragma once

#include <exception>

class UserNotFoundException: std::exception
{
public:
    const char* what() const;
};