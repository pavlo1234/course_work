

#include "Poco/Util/Application.h"
#include "Poco/Exception.h"

#include "handler/RegisterRequestHandler.h"
#include "AR/UserAR.h"
#include "service/RegVerificator.h"


using Poco::Util::Application;

std::string RegisterRequestHandler::PATH = "/register";

void RegisterRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
    Application& app = Application::instance();
    app.logger().information(PATH + ": Request from %s",
        request.clientAddress().toString());

    Poco::URI uri(request.getURI());
    std::string path = uri.getPath();

    path.erase(path.find("/register"), 9);
    if(path == "") {
        Data data = getJSONData(request); 
        std::cout << "Data extracted." << std::endl;

        User user = User::fromJSON(data["user"]);

        std::cout << user.toJSON() << std::endl;

        std::string res = "";
        try {
            response.sendContinue();
            
            UserAR::Conds cnds;
            cnds.insert("email", user.getEmail());

            std::vector<std::unique_ptr<UserAR>> users = UserAR::getByFilter(cnds);

            if (users.size() > 0) throw UserDuplicateException();

            RegVerificator::verify(data["user"]["email"].convert<std::string>());
            UserAR::create(user);

            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            res = prepareResponse({{"user", {&user}}});
            response.send() << res;
        }
        catch(const VerificationException& ex) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.send() << "{ \"error\" : \"" << ex.what() << "\"}";
        } 
        catch (const UserDuplicateException& ex) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            response.send() << "{ \"error\" : \"" << ex.what() << "\"}";
        }
    }
    else if(path == "/complete")
    {
        Data prms = getQueryParameters(request);
        std::string res = "";
        if(RegVerificator::complete(prms["key"].convert<int>())){
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            res = "<h1>Account is successfully verified</h1>";
        }
        else 
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
        response.send() << res;
    }

    

}
