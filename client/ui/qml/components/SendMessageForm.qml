import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services
import data

Rectangle {
    id: sendMessageFormBlock
    property string login
    property int cid
    property bool available
    readonly property int max_chars_count: 255

    signal sended(msg: var)

    height: 100
    Rectangle {
        id: messageTextBlock
        width: parent.width*0.65
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        height: 0.8*parent.height
        ScrollView {
            id: messageInputView
            anchors.fill: parent
            TextArea {
                id: messageInput
                readOnly: !available
                placeholderText: "Enter message (<256 symbols)"
            }
        }

    }

    Rectangle {
        id: sendChatButton
        width: Math.min(150, parent.width * 0.3)
        anchors.right: parent.right
        anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        height: 40
        color: "green"

        Text {
            text: "Send"
            font.family: "Arial"
            font.pixelSize: 12
            font.weight: 600
            color: "white"
            anchors.centerIn: parent
        }

        DataContainer {
            id: formData
        }
        RequestManager {
            id: sendMessageRequest
            method: "PUT"
            onFinished:{
                console.log("send request executed");
                messageInput.text = "";
                console.log(JSON.stringify(sendMessageRequest.reply["message"]));
                sended(sendMessageRequest.reply["message"]);
            }
            onFailed: (code) => {
                console.log("/sendMessage: Error "+code);
            }
        }

        MouseArea {
            anchors.fill: parent
            enabled: available
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                if(!messageInput.text)
                    return;
                var time = new Date();
                time = `${time.getUTCFullYear()}-${time.getUTCMonth()+1}-${time.getUTCDate()} ${time.getUTCHours()}:${time.getUTCMinutes()}:${time.getUTCSeconds()}`;

                var message = {
                    "login" : login,
                    "cid" : cid,
                    "text" : messageInput.text.slice(0, max_chars_count),
                    "datetime" : time
                }
                formData.add("message", message);
                sendMessageRequest.exec(QueryBuilder.resource("user/chats/"+cid+"/messages"), formData.toJSON());
                
            }
        }
    }
}