#include "exception/UserDuplicateException.h"

const char* UserDuplicateException::what() const
{
    return "User with this credentials already exists";
}