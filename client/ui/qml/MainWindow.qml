import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import "components/"

import data
import services

Window {
    id: mainWindow

    required property var sesData
    signal logout

    visible: true
    width: 640
    height: 590

    AddChatForm {
        id: addChatForm
        user: mainWindow.sesData["user"]
        visible: false
        x: mainWindow.x + mainWindow.width/2 - addChatForm.width / 2
        y: mainWindow.y + mainWindow.height/2 - addChatForm.height / 2
    }

    BlockListForm {
        id: blockListForm
        user: mainWindow.sesData["user"]
        visible: false
        x: mainWindow.x + mainWindow.width/2 - blockListForm.width / 2
        y: mainWindow.y + mainWindow.height/2 - blockListForm.height / 2
    }

    Rectangle {
        id: sideBlock
        width: Math.min(300, parent.width * 0.4)
        height: parent.height
        anchors.left: parent.left
        color: "#e4e7ec"

        Rectangle {
            id: controlWidget
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter

            width: parent.width
            height: 40
            color: "white"
    
            SearchChatForm {
                id: searchChatForm
                anchors.left: parent.left
                anchors.leftMargin: 15
                anchors.right: addChatButton.left
                anchors.rightMargin: 15
                anchors.verticalCenter: parent.verticalCenter
                onTitleEdited: (title) => {
                    chatsList.filter(title);
                }
            }
            
            Rectangle {
                id: addChatButton
                width: 50
                height: parent.height
                anchors.right: parent.right
                color: "green"

                Text {
                    text: "+"
                    font.family: "Arial"
                    font.pixelSize: 20
                    font.weight: 600
                    color: "white"
                    anchors.centerIn: parent
                }
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        addChatForm.visible = true;
                    }
                }
                            
            }
            
        }

        ChatsList {
            id: chatsList
            user: mainWindow.sesData["user"]
            chats: mainWindow.sesData["user"]["chats"]
                    
            width: parent.width*0.95-20
            height: parent.height
            anchors.top: controlWidget.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 5
            anchors.bottomMargin: 20
            onChatSelected: (chat) => {
                messages.load();
            }
        }

        
        Rectangle {
            id: logoutButton
            height: 30
            width: logoutLink.contentWidth+20
            radius: 20
            border.color: "#6d7c97"
            border.width: 1
            z: 1
            color: "white"
            anchors.left: parent.left
            anchors.leftMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            Text {
                id: logoutLink
                text: "Log out"
                font.family: "Arial"
                font.pixelSize: 12
                font.weight: 700
                color: "#6d7c97"
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: logout();
            }
                            
        }

        Rectangle {
            id: blockButton
            height: 30
            width: blockLink.contentWidth+20
            radius: 20
            border.color: "#6d7c97"
            border.width: 1
            z: 1
            color: "white"
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            Text {
                id: blockLink
                text: "Block\\Unblock"
                font.family: "Arial"
                font.pixelSize: 12
                font.weight: 700
                color: "#6d7c97"
                anchors.centerIn: parent
            }
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    blockListForm.visible = true;
                }
            }
                            
        }

    }

    

    Rectangle {
        id: chatWidget

        width: parent.width - sideBlock.width
        height: parent.height
        anchors.right: parent.right

        color: "#e4e7ec"
    
        InfoPanel {
            id: infoPanel
            chatItem: chatsList.activeChat
            user: sesData["user"]
            chat: chatsList.activeChat ? chatsList.activeChat.chat : {"title" : ""}
            visible: chatsList.activeChat !== null
        }

        Rectangle {
            width: 2
            height: parent.height
            color: "white";
            anchors.left: parent.left
        }

        MessageHistory {
            id: messages
            chatItem: chatsList.activeChat
            user: sesData["user"]
            anchors.top: infoPanel.bottom
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: sendMessageForm.top
        
        }
            
        SendMessageForm {
            id: sendMessageForm
            cid: chatsList.activeChat !== null ? chatsList.activeChat.chat["id"] : -1;
            login: chatsList.activeChat !== null ? sesData["user"]["login"] : ""
            width: parent.width
            available: chatsList.activeChat !== null
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter

            onSended: (msg) => {
                messages.add(msg);
            }
        }

    }
    
    

}