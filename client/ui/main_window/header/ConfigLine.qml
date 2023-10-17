import QtQuick 2.15

Rectangle {
    id: configLine
    width: parent.width
    height: 70
    Text {
        id: currentPageTitle
        text: "Some page"
        color: "black"
        font.family: "Open Sans"
        font.weight: 700
        font.pixelSize: 30
        anchors.left: parent.left
        anchors.leftMargin: parent.width * 0.07
        anchors.verticalCenter: parent.verticalCenter
    }
    Rectangle {
        id: configLine_border
        width: parent.width
        height: 1
        color: "#D4D9E2"
        anchors.bottom: parent.bottom
    }


}
