import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services
import data

Window {
    id: loginWindow
    
    property int error: 0
    signal finish(userData: var)
    signal register

    visible: true
    width: 640
    height: 590

    ColumnLayout {
        id: loginWindowDiv

        width: (parent.width <= 390 ? parent.width * 0.9 : 390)
        height: (parent.height <= 405 ? parent.height * 0.9 : 405)
        anchors.centerIn: parent

        Text {
            id: loginWindowTitle
            text: "Log In"
            font.family: "Arial"
            font.pixelSize: 24
            font.weight: 600
            color: "black"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: parent.height * 0.1
        }

        ColumnLayout {
            id: loginBlock
            Layout.fillWidth: true
            Layout.topMargin: 15
            Item {
                id: loginBlockLine
                Text {
                    text: "LOGIN"
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
                id: loginInputBlock
                border.width: 1
                border.color: (error === 401 ? "#d9212c" : "#D4D9E2")
                height: 40
                Layout.fillWidth: true
                Layout.topMargin: 12
                TextInput {
                    id: loginInput
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 16
                    rightPadding: 30
                    font.family: "Open Sans"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "black"
                    clip: true
                }
            }

        }

        ColumnLayout {
            id: passwordBlock
            Layout.fillWidth: true
            Layout.topMargin: 15
            Item {
                id: passwordBlockLine
                Layout.fillWidth: true
                Text {
                    text: "PASSWORD"
                    color: "#434C5D"
                    lineHeight: 1.1
                    font.family: "Arial"
                    font.pixelSize: 10
                    font.letterSpacing: 0.9
                    font.weight: 600
                    anchors.left: parent.left
                }
            }
            Rectangle {
                id: passwordInputBlock
                border.width: 1
                border.color: (error === 401 ? "#d9212c" : "#D4D9E2")
                height: 40
                Layout.fillWidth: true
                Layout.topMargin: 12
                TextInput {
                    id: passwordInput
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 16
                    rightPadding: 30
                    font.family: "Arial"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "black"
                    echoMode: TextInput.Password
                    clip: true
                }

            }

        }

        Text {
            id: errorText
            Layout.alignment: Qt.AlignHCenter
            font.family: "Arial"
            font.pixelSize: 12
            font.weight: 600
            color: "#d9212c"
            text: "Incorrect credentials"
            clip: true
            visible: error >= 6
        }

        Text {
            id: serverError
            Layout.alignment: Qt.AlignHCenter
            font.family: "Arial"
            font.pixelSize: 12
            font.weight: 600
            color: "#0d8bf2"
            clip: true
            visible: error < 6
        }

        Rectangle {
            id: loginButton
            Layout.fillWidth: true
            Layout.topMargin: 35
            height: 40
            color: "green"

            Text {
                font.family: "Arial"
                font.pixelSize: 12
                font.letterSpacing: 0.8
                color: "white"
                text: "LOG IN"
                anchors.centerIn: parent
            }

            RequestManager {
                id: authRequest
                method: "GET"
                onFinished: {
                    loginWindow.finish(authRequest.reply);
                }
                onFailed: (code, msg) => {
                    console.log(code);
                    loginWindow.error = code;
                    if(code < 6)
                        serverError.text = msg;
                    else 
                        userError.text = msg;
                        
                }
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    if(loginInput.text != "" && passwordInput.text != "") {
                        authRequest.setCredentials(loginInput.text, passwordInput.text);
                        authRequest.exec(QueryBuilder.resource("/user"));
                    }
                }
            }

        }

        Text {
            id: registerLink
            Layout.alignment: Qt.AlignHCenter
            text: "Sign Up"
            font.family: "Arial"
            font.pixelSize: 12
            color: "green"
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: register();
            }
        }

    }

}