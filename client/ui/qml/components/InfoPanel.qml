import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services
import data


Rectangle {
    id: chatInfoBlock
    property Item chatItem
    property var chat
    property var user

    width: parent.width;
    height: 40
    anchors.top: parent.top;
    RowLayout {
        id: chatInfoLayout
        anchors.fill: parent
        Text {
            Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            Layout.leftMargin: 15
            id: currChatTitle
            text: String.fromCodePoint(0x1F464) + chat["title"]
            font.family: "Arial"
            font.pixelSize: 12
            font.weight: 600
            color: "black"
        }


        Rectangle {
            id: deleteChatButton
            Layout.preferredWidth: buttonText.contentWidth+35
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            Layout.rightMargin: 15
            height: 25
            border.color: "#6d7c97"
            border.width: 1
            radius: 20

            Text {
                id: buttonText
                text: "Delete"
                font.family: "Arial"
                font.pixelSize: 12
                font.weight: 600
                color: "#6d7c97"
                anchors.centerIn: parent
            }

            RequestManager {
                id: deleteChatRequest
                method: "DELETE"
                onFinished:{
                    console.log("delete chat successed");
                    chatItem.destroy();
                }
                onFailed: (code, msg) => {
                    console.log("user/chats/"+chat["id"]+": Error "+code);
                }
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    console.log("delete chat clicked");
                    if(chat["creator"] === user["login"]) {
                        deleteChatRequest.method = "DELETE";
                        deleteChatRequest.exec(QueryBuilder.resource("user/chats/"+chat["id"]));
                    }
                    else {
                        deleteChatRequest.method = "POST";
                        deleteChatRequest.exec(QueryBuilder.resource("user/chats/"+chat["id"]+"/leave"));
                    }
                }
            }   
        }

    }


    RequestManager {
        id: request
        method: "GET"
        onFinished: {
            chatItem.destroy();
        }
        onFailed: (code) => {
            console.log(code);
        }
    }

}