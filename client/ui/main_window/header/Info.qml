import QtQuick 2.15
import QtQuick.Layouts 1.0

import "info/"

Rectangle {
    id: info
    width: parent.width
    height: 70
    Logo {
        id: logo
        anchors.left: parent.left
    }
    Item {
        id: infoBlock
        anchors.right: parent.right
        width: (parent.width <= 626 ? parent.width * 0.74 : 374)
        height: parent.height
        SwitchButton {
            id: switchButton
            anchors.left: parent.left
        }
        Profile {
            id: profile
            anchors.right: parent.right
        }

        Rectangle {
            id: profile_leftBorder
            width: 1
            height: parent.height
            color: "#EDEDED"
            anchors.left: parent.left
        }
    }

    Rectangle {
        id: info_bottomBorder
        width: parent.width
        height: 1
        color: "#EDEDED"
        anchors.bottom: parent.bottom
    }




}
