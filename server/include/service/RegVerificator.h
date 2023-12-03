#pragma once


#include <set>

#include "Poco/Net/SecureSMTPClientSession.h"
#include "Poco/Net/SMTPClientSession.h"
#include "Poco/Net/NetException.h"
#include "Poco/Net/MailMessage.h"
#include "Poco/Net/MailRecipient.h"
#include "Poco/Net/StringPartSource.h"

#include "conf.h"
#include "exception/VerificationException.h"

using Poco::Net::SMTPClientSession;
using Poco::Net::SecureSMTPClientSession;
using Poco::Net::SMTPException;
using Poco::Net::NetException;
using Poco::Net::MailMessage;
using Poco::Net::MailRecipient;
using Poco::Net::StringPartSource;

const std::string HOST = "smtp.gmail.com";
const int PORT = 587;
const std::string USERNAME = "msapp.sysconf@gmail.com";
const std::string PASSWORD = "asww bpkl rplj kfro";


class RegVerificator {
    
public:
    static std::set<unsigned int> keys;
    static bool verify(const std::string& email);
    static bool complete(const int& key);

};