#pragma once

#include <exception>

class UserDuplicateException: std::exception
{
public:
    const char* what() const;
};