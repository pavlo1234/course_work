import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services
import data

Rectangle {
    id: chatBlock
    property bool active: false
    property var chat
    signal selected(chat: Item)
    signal updated(msgs: var)
    signal deleted()

    Timer {
        id: updating
        interval: 1000
        repeat: true
        running: false
        onTriggered: refresh()
        
    }

    Component.onCompleted: {
        updating.start();
    }

    Component.onDestruction: {
        updating.stop();
        delete chat;
        deleted();
        destroy();
    }

    function refresh() {
        updateChatRequest.exec(QueryBuilder.resource("user/chats/"+chat["id"]));

    }
    function add(msgData) {
        chat["messages"].push(msgData);
    }
    
    width: parent.width
    height: 90
    color: "white";

    Rectangle {
        width: 3
        height: parent.height
        color: active ? "#9763f6" : "green"
        anchors.left: parent.left
    }
    
    Text {
        id: title
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 5
        anchors.leftMargin: 10
        text: chat["title"]
        font.family: "Arial"
        font.pixelSize: 14
        font.weight: 600
        color: "black"
        clip: true
    }
    Text {
        id: messageAuthor
        anchors.top: title.bottom
        anchors.left: parent.left
        anchors.topMargin: 5
        anchors.leftMargin: 20
        text: chat["messages"].length  ? chat["messages"][chat["messages"].length-1]["login"] : ""
        font.family: "Arial"
        font.pixelSize: 14
        font.weight: 600
        color: "#88898c"
        clip: true
        elide: Text.ElideRight
    }
    Text {
        id: messageText
        anchors.top: messageAuthor.bottom
        anchors.left: parent.left
        anchors.topMargin: 5
        anchors.leftMargin: 20
        width: parent.width*0.9;
        height: 20
        text: chat["messages"].length ? chat["messages"][chat["messages"].length-1]["text"] : "No messages."
        font.family: "Arial"
        font.pixelSize: 12
        font.weight: 600
        color: "black"
        clip: true
        elide: Text.ElideRight
    }
    Text {
        id: messageTime
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 5
        anchors.rightMargin: 5
        text: {
            if(chat["messages"].length) {
                let time = chat["messages"][chat["messages"].length-1]["datetime"];
                return `${time.getFullYear()}-${time.getMonth()+1}-${time.getDate()} ${time.getHours()}:${time.getMinutes()}:${time.getSeconds()}`; 
            }
            else return ""
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
            console.log("chat block clicked");
            selected(chatBlock);
        }
    }

    RequestManager {
        id: updateChatRequest
        method: "GET"
        onFinished: {
            updated(updateChatRequest.reply["chat"]["messages"]);
            chatBlock.chat = updateChatRequest.reply["chat"];
        }
        onFailed: (code, msg) => {
            if(code === 404)
                chatBlock.destroy();
        }
    }

                
}