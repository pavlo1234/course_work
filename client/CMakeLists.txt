cmake_minimum_required(VERSION 3.26)

project(ClientApp)

#must be specified
set(Qt6_DIR "C:\\Qt\\6.5.1\\msvc2019_64\\lib\\cmake\\Qt6")
set(Qt6_SHARED_LIB_DIR "C:\\Qt\\6.5.1\\msvc2019_64\\bin")

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup()

qt_add_executable(appproject_qml2
    src/main.cpp
)

qt_add_qml_module(appproject_qml2
    URI project_qml2
    VERSION 1.0
    QML_FILES
    ui/LoginWindow.qml
    ui/MainWindow.qml
    ui/main_window/Header.qml
    ui/main_window/header/Info.qml
    ui/main_window/header/info/Logo.qml
    ui/main_window/header/info/Profile.qml
    ui/main_window/header/info/SwitchButton.qml
    ui/main_window/header/ConfigLine.qml
    ui/main_window/header/HMenu.qml
    ui/main_window/header/menu/CategoryItem.qml
    ui/main_window/SideBar.qml
)

qt_add_resources(appproject_qml2 "app_images"
    PREFIX "/"
    FILES
        assets/images/login_window/SH.png
        assets/images/login_window/FB.svg
        assets/images/login_window/Gmail.svg
        assets/images/login_window/x.svg
        assets/images/main_window/header/info/switcher.svg
        assets/images/main_window/header/hmenu/left-arrow.svg
        assets/images/main_window/header/hmenu/left-arrow-active.svg
        assets/images/main_window/header/hmenu/right-arrow-active.svg
        assets/fonts/SF-Pro-Text-Bold.otf
        assets/fonts/Roboto-Medium.ttf
        assets/fonts/Roboto-Bold.ttf
)


target_link_libraries(appproject_qml2
    PRIVATE Qt6::Quick
)
