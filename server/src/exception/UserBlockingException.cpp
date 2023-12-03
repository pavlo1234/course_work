#include "exception/UserBlockingException.h"

const char* UserBlockingException::what() const
{
    return "User blocked this chat creator";
}