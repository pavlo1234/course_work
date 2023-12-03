cmake_minimum_required(VERSION 3.26)

project(MessageApp)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#must be specified
set(Qt6_DIR "C:\\Qt\\6.5.1\\msvc2019_64\\lib\\cmake\\Qt6")
set(Qt6_SHARED_LIB_DIR "C:\\Qt\\6.5.1\\msvc2019_64\\bin")

find_package(Qt6 REQUIRED COMPONENTS Quick Core Gui Network)

qt_standard_project_setup()

file(GLOB SOURCES src/*.cpp src/model/*.cpp)
file(GLOB HEADERS include/*.h include/model/*.h include/model/interface/*.h )

qt_add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

qt_add_qml_module(${PROJECT_NAME}
    URI main
    QML_FILES
        ui/qml/default.qml
        ui/qml/LoginWindow.qml
        ui/qml/RegisterWindow.qml
        ui/qml/MainWindow.qml
        ui/qml/components/BlockListForm.qml
        ui/qml/components/AddChatForm.qml
        ui/qml/components/ChatsList.qml
        ui/qml/components/ChatBlock.qml
        ui/qml/components/SearchChatForm.qml
        ui/qml/components/MessageHistory.qml
        ui/qml/components/MessageBlock.qml
        ui/qml/components/SendMessageForm.qml
        ui/qml/components/InfoPanel.qml
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_directories(${PROJECT_NAME}
    PUBLIC ${Qt6_SHARED_LIB_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC Qt6::Quick Qt6::Core Qt6::Gui Qt6::Network
)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/bin)

INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
)

qt_generate_deploy_qml_app_script(
    TARGET ${PROJECT_NAME}
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})