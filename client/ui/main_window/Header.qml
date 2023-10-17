import QtQuick 2.15

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import "header/"

Rectangle {
    id: header
    width: parent.width
    height: headerLayout.height
    ColumnLayout {
        id: headerLayout
        width: parent.width
        spacing: 0
        Info {
            id: info
            Layout.fillWidth: true
        }
        ConfigLine {
            id: configLine
            Layout.fillWidth: true
        }
        HMenu {
            id: menu
            Layout.fillWidth: true
        }
    }



}
