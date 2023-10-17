cmake_minimum_required(VERSION 3.26)

project(ServerApp)

set(CMAKE_PREFIX_PATH "build")
find_package(Poco REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} Poco::Net)
