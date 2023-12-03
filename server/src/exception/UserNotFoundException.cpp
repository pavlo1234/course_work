#include "exception/UserNotFoundException.h"

const char* UserNotFoundException::what() const 
{
    return "User not found";
}