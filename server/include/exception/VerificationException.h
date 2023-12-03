#pragma once

#include <exception>

class VerificationException: std::exception
{
public:
    const char* what() const;
};