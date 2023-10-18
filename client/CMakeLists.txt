cmake_minimum_required(VERSION 3.26)

project(ClientApp)

#must be specified
set(Qt6_DIR "C:\\Qt\\6.5.1\\msvc2019_64\\lib\\cmake\\Qt6")
set(Qt6_SHARED_LIB_DIR "C:\\Qt\\6.5.1\\msvc2019_64\\bin")

find_package(Qt6 REQUIRED COMPONENTS Gui Quick)

qt_standard_project_setup()

qt_add_executable(${PROJECT_NAME}
    src/main.cpp
)

qt_add_qml_module(${PROJECT_NAME}
    URI main
    QML_FILES
        ui/qml/main.qml
)

target_link_directories(${PROJECT_NAME}
    PRIVATE ${Qt6_SHARED_LIB_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE Qt6::Quick Qt6::Gui
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE ON
    WIN32_EXECUTABLE ON
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