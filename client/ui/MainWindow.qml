import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import "main_window/"

Window {
    id: mainWindow
    width: 1100
    height: 750
    visible: true
    title: qsTr("Sports Hub")

    Header {
        id: header
        anchors.top: parent.top
        Rectangle {
            id: headerShadow
            anchors.top: parent.bottom
            width: parent.width
            height: 20
            opacity: 0.09
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#000000" }
                GradientStop { position: 1.0; color: "white" }
            }
        }
        z:1
    }

    SideBar {
        id: sideBar
        anchors.left: parent.left
        anchors.top: header.bottom

    }



}



