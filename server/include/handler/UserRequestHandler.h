#pragma once

#include "handler/RequestHandler.h"
#include "AR/UserAR.h"


class UserRequestHandler: public RequestHandler
{
private:
    UserAR* user;
    UserAR* verify(HTTPServerRequest& request);
    void act(HTTPServerRequest& request, HTTPServerResponse& response);
public:
    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);

    static std::string PATH;

};