#include "RequestHandlerFactory.h"

#include "Poco/URI.h"

HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    Poco::URI uri(request.getURI());
    std::string path = uri.getPath();
    
    if(path.find(UserRequestHandler::PATH) != std::string::npos) 
        return new UserRequestHandler();

    if(path.find(RegisterRequestHandler::PATH) != std::string::npos)
        return new RegisterRequestHandler();
    
    return nullptr;
}