cmake_minimum_required(VERSION 3.22)

project(ServerApp)

find_package(Poco REQUIRED COMPONENTS Net Foundation Util)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} BEFORE PRIVATE ${Poco_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} Poco::Net Poco::Foundation Poco::Util)
