import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services 1.0

Window {
    id: defaulWindow
    visible: false
    Loader {
        id: loginWindowL
        source: "LoginWindow.qml"
    }

    Loader {
        id: registerWindowL
    }

    Loader {
        id: mainWindowL
    }

    Connections {
        target: loginWindowL.item
        function onFinish(reply) {
            loginWindowL.item.hide();
            mainWindowL.setSource("MainWindow.qml",{
                "sesData" : reply
            });
        }
        function onRegister() {
            loginWindowL.item.hide();
            registerWindowL.setSource("RegisterWindow.qml");
        }
        function onClosing() {
            Qt.exit(1);
        }
    }

    Connections {
        target: registerWindowL.item
        function onFinish(data) {
            registerWindowL.item.hide();
            mainWindowL.setSource("MainWindow.qml",{
                "sesData" : data
            });
        }
        function onLogin() {
            registerWindowL.item.hide();
            loginWindowL.setSource("LoginWindow.qml");
        }
        function onClosing() {
            Qt.exit(1);
        }
    }

    Connections {
        target: mainWindowL.item
        function onLogout() {
            mainWindowL.item.hide();
            loginWindowL.setSource("LoginWindow.qml");
        }
        function onClosing() {
            Qt.exit(1);
        }
    }

}