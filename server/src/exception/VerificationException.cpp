#include "exception/VerificationException.h"

const char* VerificationException::what() const {
    return "Cannot verify email";
}