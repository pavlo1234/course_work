import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services
import data

Window {
    id: addChatForm
    property var user
    property int error: 0
    signal chatAdded(chatData: var)

    width: 400
    height: 350
    color: "white"

    
    x : parent.x + parent.width/2 - addChatForm.width / 2
    y : parent.y + parent.height/2 - addChatForm.height / 2
  
    modality: Qt.ApplicationModal
    flags: Qt.SplashScreen

    Rectangle {
        width: parent.width
        height: 3
        color: "green"
        anchors.top: parent.top
        z:1
    }

    Rectangle {
        id: exitButton
        width: 50
        height: 50
        anchors.right: parent.right
        anchors.top: parent.top

        Text {
            font.family: "Arial"
            font.pixelSize: 12
            font.letterSpacing: 0.8
            color: "green"
            text: "EXIT"
            anchors.centerIn: parent
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                error = 0;
                addChatForm.close();
            }
            
        }

    }

    ColumnLayout {
        id: formLayout
        width: Math.min(300, parent.width*0.8)
        anchors.centerIn: parent

        ColumnLayout {
            id: loginBlock
            Layout.fillWidth: true
            Layout.topMargin: 15
            Item {
                id: titleBlockLine
                Text {
                    text: "Title (same for both users):"
                    color: "#434C5D"
                    lineHeight: 1.1
                    font.family: "Arial"
                    font.pixelSize: 10
                    font.letterSpacing: 0.9
                    font.weight: 800
                    anchors.left: parent.left
                }
            }
            Rectangle {
                id: titleInputBlock
                border.width: 1
                border.color: "#D4D9E2"
                height: 40
                Layout.fillWidth: true
                Layout.topMargin: 12
                TextInput {
                    id: titleInput
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 16
                    rightPadding: 30
                    font.family: "Open Sans"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "black"
                    clip: true
                    text: {
                        if(!addChatForm.visible) return "";
                    }
                    validator: RegularExpressionValidator {
                        regularExpression: /^[^\0]+$/
                    }
                }
            }

            Item {
                id: loginsBlockLine
                Text {
                    text: "User:"
                    color: "#434C5D"
                    lineHeight: 1.1
                    font.family: "Arial"
                    font.pixelSize: 10
                    font.letterSpacing: 0.9
                    font.weight: 800
                    anchors.left: parent.left
                }
            }
            Rectangle {
                id: loginsInputBlock
                border.width: 1
                border.color: "#D4D9E2"
                height: 40
                Layout.fillWidth: true
                Layout.topMargin: 12
                TextInput {
                    id: loginsInput
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 16
                    rightPadding: 30
                    font.family: "Open Sans"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "black"
                    clip: true
                    text: {
                        if(!addChatForm.visible) return "";
                    }
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9a-zA-z\@\.]{8,}$/
                    }
                }
            }

        }

        Text {
            id: userErrorMsg
            Layout.alignment: Qt.AlignHCenter
            font.family: "Arial"
            font.pixelSize: 12
            font.weight: 600
            color: "#d9212c"
            clip: true
            visible: error >= 6 && error !== 0
        }

        Text {
            id: serverErrorMsg
            Layout.alignment: Qt.AlignHCenter
            font.family: "Arial"
            font.pixelSize: 12
            font.weight: 600
            color: "#0d8bf2"
            clip: true
            visible: error < 6 && error !== 0
        }

        Rectangle {
            id: addChatButton
            Layout.fillWidth: true
            Layout.topMargin: 35
            height: 40
            color: "green"

            Text {
                font.family: "Arial"
                font.pixelSize: 12
                font.letterSpacing: 0.8
                color: "white"
                text: "ADD CHAT"
                anchors.centerIn: parent
            }

            DataContainer {
                id: formData
            }

            RequestManager {
                id: createChatRequest
                method: "PUT"
                onFinished: {
                    addChatForm.chatAdded(createChatRequest.reply);
                    titleInput.text = "";
                    loginsInput.text = "";
                    addChatForm.close();

                }
                onFailed: function(code, msg){
                    addChatForm.error = code;
                    if(code >= 6)
                        userErrorMsg.text = msg;
                    else
                        serverErrorMsg.text = msg;  
                    console.log("createChat/ Error: "+code);
                }
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    var logins = loginsInput.text.split(",");
                    logins.push(user["login"]);
                    if(titleInput.acceptableInput && loginsInput.acceptableInput){
                        formData.add("chat", 
                            {"id" : 0,
                            "title" : titleInput.text, 
                            "ulogins" : logins,
                            "creator" : user["login"]});
                        createChatRequest.exec(QueryBuilder.resource("user/chats"), formData.toJSON());
                    }
                    else {
                        userErrorMsg.text = "Incorrect input";
                        error = 6;
                    }
                    
                }
            }

        }

    }


}