#pragma once

#include "RequestHandler.h"


class RegisterRequestHandler: public RequestHandler
{
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);

    void handleGET(HTTPServerRequest& request, HTTPServerResponse& response);
    void handlePOST(HTTPServerRequest& request, HTTPServerResponse& response);
    
    static std::string PATH;
};