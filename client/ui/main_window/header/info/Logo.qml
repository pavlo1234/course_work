import QtQuick 2.15

Rectangle {
    id: logo
    width: (parent.width <= 626 ? parent.width * 0.26 : 252)
    height: parent.height
    color: "#D72130"
    Text {
        text: "Sports Hub"
        color: "#FFFBFB"
        font.family: "Open Sans"
        font.weight: 600
        font.pixelSize: 22
        anchors.centerIn: parent
    }
}
