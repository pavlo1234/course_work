
#include <regex>

#include "Poco/Util/Application.h"
using Poco::Util::Application;


#include "handler/UserRequestHandler.h"

std::string UserRequestHandler::PATH = "/user";

UserAR* UserRequestHandler::verify(HTTPServerRequest& request) 
{
    if (!request.hasCredentials())
        throw UserNotFoundException();

    std::string scheme, auth_info;
    request.getCredentials(scheme, auth_info);
    if(scheme == "Basic") 
    {
        HTTPBasicCredentials crd(auth_info);
        return UserAR::getByCredentials(crd.getUsername(), crd.getPassword());
    }
    else return nullptr;
}

void UserRequestHandler::act(HTTPServerRequest& request, HTTPServerResponse& response)
{
    Poco::URI uri(request.getURI());
    std::string path = uri.getPath(), method = request.getMethod();
    path.erase(path.find("/user"), 5);
    if(path == "") {
        if(method == "GET") {
            user->chats();
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.send() << prepareResponse({{"user", {dynamic_cast<Serializable*>(user->getUser())}}});
        }
    }
    else if(path == "/block") {
        Data data = getJSONData(request);

        std::set<std::string> ulogins;
        for(Var& login : data["logins"])
        {
            std::string ulogin = login.convert<std::string>();
            try {
                std::unique_ptr<UserAR> userAR(UserAR::getByLogin(ulogin));
            }
            catch(const UserNotFoundException& ex) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                std::string json = std::string("{\"error\":\"") + ex.what() + std::string("\"}");
                response.send() << json;
                return;
            }
            ulogins.insert(ulogin);
        }
        
        user->chats();
        if(user->block(ulogins)) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.send();
        }
        else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            std::string json = std::string("{\"error\":\"") + "User exists in black list" + std::string("\"}");
            response.send() << json;
        }
    }
    else if(path == "/unblock") {
        Data data = getJSONData(request);

        std::set<std::string> ulogins;
        for(Var& login : data["logins"])
        {
            std::string ulogin = login.convert<std::string>();
            try {
                std::unique_ptr<UserAR> userAR(UserAR::getByLogin(ulogin));
            }
            catch(const UserNotFoundException& ex) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                response.send() << std::string("{\"error\":\"") + ex.what() + std::string("\"}");
                return;
            }
            ulogins.insert(ulogin);
        }
        
        user->chats();
        if(user->unblock(ulogins)) {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            response.send();
        }
        else response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
    }
    else if(path.find("/chats") != std::string::npos) {

        path.erase(path.find("/chats"), 6);
        if(path == "") {
            if(method == "GET") {
                ChatAR::Conds filter_prms = getQueryParameters(request);

                filter_prms.insert({"login", user->getUser()->getLogin()});

                std::vector<std::unique_ptr<ChatAR>> chatARs = ChatAR::getByFilter(filter_prms);
                
                if(chatARs.size() > 0){
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

                    std::vector<Serializable*> chats;
                    for(auto& chatAR : chatARs) {
                        if(chatAR.get() != nullptr) {
                            chatAR->retrieveMessages();
                            chats.push_back(dynamic_cast<Serializable*>(chatAR->getChat()));
                        }
                    }
                    response.send() << prepareResponse({{(chats.size() > 1 ? "chats" : "chat"), chats}});
                }
                else {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NO_CONTENT);
                    response.send();
                }
               
            }
            else if(method == "POST") {
                Data data = getJSONData(request);

                Chat chat = Chat::fromJSON(data["chat"]);
                
                ChatAR::Conds cnds;
                cnds.insert("id", chat.getID());

                std::vector<std::unique_ptr<ChatAR>> chatARs = ChatAR::getByFilter(cnds);
                
                if(chatARs[0]->update(chat))
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                else 
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                response.send();

            }
            else if(method == "PUT") {
                Data data = getJSONData(request);
                
                Chat chat = Chat::fromJSON(data["chat"]);
                std::string json = "";
                try {
                    std::unique_ptr<ChatAR> chatAR = ChatAR::create(chat);
                    json = prepareResponse({{"chat", {chatAR->getChat()}}});
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                }
                catch(const UserNotFoundException& ex) {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                    json = std::string("{\"error\":\"") + ex.what() + std::string("\"}");
                }
                catch(const UserBlockingException& ex) {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                    json = std::string("{\"error\":\"") + ex.what() + std::string("\"}");
                }
               
                response.send() << json;
            }
        }
        else {
            std::regex r("[^\\/]*[0-9]+[^\\/]*");
            std::smatch sm;
            std::regex_search(path, sm, r);
            int cid = std::stoi(sm.str(0));

            path = std::regex_replace(path, std::regex("\\/*[0-9]+"), "");

            user->chats();
            ChatAR* curr_chat = nullptr;
            for(auto& chat : user->getChats()){
                if(chat.get()->getChat()->getID() == cid) {
                    curr_chat = chat.get();
                    break;
                }
            }
            if(curr_chat == nullptr){
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                response.send();
                return;
            }

            if(path == "") {
                if(method == "GET"){
                    std::string json = prepareResponse({{"chat", {curr_chat->getChat()}}});
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    response.send() << json;
                }
                else if(method == "DELETE") {
                    curr_chat->remove();
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    response.send();
                }
            }
            else if(path == "/leave") {
                if(method == "POST"){
                    curr_chat->deleteUser(user->getUser()->getLogin());
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    response.send();
                }
            }
            else if(path == "/messages") {
                if(method == "GET") {
                    std::vector<Serializable*> data;
                    for(Message& msg : curr_chat->getChat()->getMessages())
                        data.push_back(&msg);

                    std::string json = prepareResponse({{"messages", data}});
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    response.send() << json;
                }
                else if(method == "PUT") {
                    Data data = getJSONData(request);

                    std::string login = user->getUser()->getLogin(),
                        text = data["message"]["text"].convert<std::string>();

                    DateTime dt = data["message"]["datetime"].convert<DateTime>();

                    Message msg(login, cid, text, dt);
                    MessageAR::create(msg);
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

                    std::string res = prepareResponse({{"message", {&msg}}});
                    response.send() << res;
                }
            }

        }
       
    }

}


void UserRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
   /* Application& app = Application::instance();
    app.logger().information(PATH+": Request from %s",
        request.clientAddress().toString());
    */
    
    response.setChunkedTransferEncoding(true);
    response.setContentType("text/json");

    try {
        user = verify(request);
        act(request, response);
        delete user;
    }
    catch(const UserNotFoundException& ex){
        response.requireAuthentication(request.getURI());
        response.send();
        return;
    }
}
