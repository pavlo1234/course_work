#include "service/RegVerificator.h"

#include <algorithm>
#include <mutex>

std::mutex KEYS_mtx;

std::set<unsigned int> RegVerificator::keys;

bool RegVerificator::complete(const int& key)
{
    std::unique_lock<std::mutex> lck(KEYS_mtx);
    if (keys.find(key) != keys.end()) {
        keys.erase(key);
        return true;
    }
    return false;
}

bool RegVerificator::verify(const std::string& email)
{

    try {
   
    std::hash<std::string> key_hash;
    unsigned int key = key_hash(email);

    std::string link = "http://"+SERVER_HOST+":"+std::to_string(SERVER_PORT)+"/register/complete?key="+std::to_string(key);

    MailMessage msg;
    msg.setSender(USERNAME);
    msg.setSubject("Account Verification");
    msg.addRecipient(MailRecipient(MailRecipient::PRIMARY_RECIPIENT, email));
    msg.addContent(new StringPartSource("Link to complete account creation: "+link));

    SecureSMTPClientSession ses(HOST);
    ses.login();
    ses.startTLS();
    ses.login(SMTPClientSession::AUTH_LOGIN, USERNAME, PASSWORD);
    ses.sendMessage(msg);
    ses.close();

    KEYS_mtx.lock();
    keys.insert(key);
    KEYS_mtx.unlock();

    bool res = true;
    while(res) {
        KEYS_mtx.lock();
        res = keys.find(key) != keys.end();
        KEYS_mtx.unlock();
    }

    return true;

    }
    catch (const SMTPException& ex) {
        throw VerificationException();
    }
    catch (const NetException& ex) {
        throw VerificationException();
    }
}