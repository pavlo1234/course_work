#pragma once

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"

#include "Poco/Net/PrivateKeyPassphraseHandler.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/InvalidCertificateHandler.h"
#include "Poco/Net/AcceptCertificateHandler.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/SSLManager.h"


#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Crypto/OpenSSLInitializer.h"
#include "Poco/Util/ServerApplication.h"


#include "conf.h"
#include "RequestHandlerFactory.h"


using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::Net::ServerSocket;

using Poco::Net::Context;

using Poco::ThreadPool;

using Poco::Util::ServerApplication;
using Poco::Util::Application;


class MainHTTPServer: public Poco::Util::ServerApplication
{
protected:
    void initialize(Application& self);
    int main(const std::vector<std::string>& args);
};