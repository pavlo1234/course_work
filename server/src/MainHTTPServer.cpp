#include "MainHTTPServer.h"

#include "AR/Connection.h"


void MainHTTPServer::initialize(Application& self)
{
    loadConfiguration();
    ServerApplication::initialize(self);

    Poco::Data::MySQL::Connector::registerConnector();
    DBConnection::init(KEY, CONN_STR);

    DBConnection::get()->session();

    Poco::Crypto::OpenSSLInitializer::initialize();

    Poco::SharedPtr<Poco::Net::PrivateKeyPassphraseHandler> pConsoleHandler = new Poco::Net::KeyConsoleHandler(false);
    Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pInvalidCertHandler = new Poco::Net::AcceptCertificateHandler(false);
    Context::Ptr pContext = new Context(Context::CLIENT_USE, PRIVATE_KEY_FILE, CERTIFICATE_FILE, "", Context::VERIFY_RELAXED, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    Poco::Net::SSLManager::instance().initializeClient(pConsoleHandler, pInvalidCertHandler, pContext);

}

int MainHTTPServer::main(const std::vector<std::string>& args)
{
    ServerSocket svs(SERVER_PORT);
    HTTPServerParams* prms = new HTTPServerParams();
    prms->setKeepAlive(false);

    ThreadPool pool(2, 3000);

    HTTPServer srv(new RequestHandlerFactory(), pool, svs, prms);

    try {
        srv.start();
        waitForTerminationRequest();
        srv.stop();
    }
    catch (const Poco::Exception& ex) {
        std::cout << ex.what() << " -- " << ex.message() << std::endl;
    }

    return Application::EXIT_OK;
}