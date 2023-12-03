import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services
import data

Rectangle {
    id: messageBlock
    property var message

    width: Math.min(Math.max(senderLogin.contentWidth, messageTime.contentWidth, messageText.contentWidth) + 30, parent.width-50)
    height: senderLogin.contentHeight + messageText.contentHeight + messageTime.contentHeight + 30
    radius: 20
    color: "white"

    Text {
        id: senderLogin
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 5
        anchors.leftMargin: 20
        text: message["login"]
        font.family: "Arial"
        font.pixelSize: 12
        font.weight: 600
        color: "#88898c"
    }
    Text {
        id: messageText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: senderLogin.bottom
        anchors.topMargin: 5
        width: messageBlock.parent.width-50
        text: message["text"]
        font.family: "Arial"
        font.pixelSize: 12
        font.weight: 600
        color: "black"
        wrapMode: Text.WordWrap
        padding: 5
    }
    Text {
        id: messageTime
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.bottomMargin: 5
        anchors.leftMargin: 20
        text: {
            let time = new Date(message["datetime"] + " UTC");
            return `${time.getFullYear()}-${time.getMonth()+1}-${time.getDate()} ${time.getHours()}:${time.getMinutes()}:${time.getSeconds()}`;
        }
        font.family: "Arial"
        font.pixelSize: 12
        font.weight: 600
        color: "#88898c"
    }

    MouseArea {
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            console.log("message block clicked");
        }
    }
 

}
