cmake_minimum_required(VERSION 3.22)

project(ServerApp)

find_package(Poco REQUIRED COMPONENTS Data DataMySQL JSON NetSSL Foundation Util Crypto)
find_package(OpenSSL REQUIRED SSL CRYPTO)

add_executable(${PROJECT_NAME} 
     src/main.cpp
     src/MainHTTPServer.cpp
     src/RequestHandlerFactory.cpp
     src/handler/RegisterRequestHandler.cpp
     src/handler/UserRequestHandler.cpp
     src/AR/Connection.cpp
     src/AR/UserAR.cpp
     src/model/User.cpp
     src/AR/ChatAR.cpp
     src/model/Chat.cpp
     src/AR/MessageAR.cpp
     src/model/Message.cpp
     src/service/RegVerificator.cpp
     src/exception/UserNotFoundException.cpp
     src/exception/UserBlockingException.cpp
     src/exception/UserDuplicateException.cpp
     src/exception/VerificationException.cpp
     res/cert.crt
     res/key.key
)
     
target_link_libraries(${PROJECT_NAME} 
     Poco::Net Poco::JSON Poco::DataMySQL Poco::Data Poco::NetSSL Poco::Foundation Poco::Util Poco::Crypto OpenSSL::SSL OpenSSL::Crypto
)

target_include_directories(${PROJECT_NAME} AFTER
     PRIVATE ${Poco_INCLUDE_DIR}
     PRIVATE ${PROJECT_SOURCE_DIR}/include
     PRIVATE "C:/Users/admin/.conan2/p/libmyd14b0efeeab77/p/include"
     PRIVATE "C:/Users/admin/.conan2/p/opens107f548f2a0c1/p/include"
)

target_link_directories(${PROJECT_NAME}
     PRIVATE "C:/Users/admin/.conan2/p/opens107f548f2a0c1/p/lib"
)