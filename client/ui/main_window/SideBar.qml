import QtQuick 2.15

Rectangle {
    id: sideBar
    width: 80
    height: parent.height
    Rectangle {
        id: sideBar_rightBorder
        width: 1
        height: parent.height
        color: "#EDEDED"
        anchors.right: parent.right
    }
}
