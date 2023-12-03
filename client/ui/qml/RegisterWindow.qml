import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services
import data

Window {
    id: registerForm
    
    property int error: 0
    signal finish(userData: var)
    signal login

    visible: true
    width: 640
    height: 590

    ColumnLayout {
        id: registerFormDiv

        width: (parent.width <= 390 ? parent.width * 0.9 : 390)
        height: (parent.height <= 405 ? parent.height * 0.9 : 405)
        anchors.centerIn: parent

        Text {
            id: registerFormTitle
            text: "Sign Up"
            font.family: "Arial"
            font.pixelSize: 24
            font.weight: 600
            color: "black"
            Layout.alignment: Qt.AlignHCenter
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
                border.color: (error === 400 || error === 8 ? "#d9212c" : "#D4D9E2")
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
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9a-zA-z\@\.]{8,}$/
                    }
                }
                Text {
                    id: loginInputPlaceholder
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 16
                    anchors.left: parent.left
                    font.family: "Arial"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "#C6CCD7"
                    text: "unique nickname (8+, only letters, numbers, @ and .)"
                    visible: loginInput.text === ""
                    clip: true
                }
            }

        }

        ColumnLayout {
            id: emailBlock
            Layout.fillWidth: true
            Layout.topMargin: 15
            Item {
                id: emailBlockLine
                Text {
                    text: "EMAIL"
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
                id: emailInputBlock
                border.width: 1
                border.color: (error === 400 || error === 9 || error === 8 ? "#d9212c" : "#D4D9E2")
                height: 40
                Layout.fillWidth: true
                Layout.topMargin: 12
                TextInput {
                    id: emailInput
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 16
                    rightPadding: 30
                    font.family: "Open Sans"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "black"
                    clip: true
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9a-zA-z\@\.]+$/
                    }
                }
                Text {
                    id: emailInputPlaceholder
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 16
                    anchors.left: parent.left
                    font.family: "Arial"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "#C6CCD7"
                    text: "sample@email.com"
                    visible: emailInput.text === ""
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
                border.color: (error === 7 || error === 8  ? "#d9212c" : "#D4D9E2")
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
                    validator: RegularExpressionValidator {
                        regularExpression: /^[0-9a-zA-z]{8,}$/
                    }
                }
                Text {
                    id: passwordInputPlaceholder
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 16
                    anchors.left: parent.left
                    font.family: "Arial"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "#C6CCD7"
                    text: "8+ characters (letters and numbers)"
                    visible: passwordInput.text === ""
                    clip: true
                }

            }

        }

        ColumnLayout {
            id: confirmPasswordBlock
            Layout.fillWidth: true
            Layout.topMargin: 15
            Item {
                id: confirmPasswordBlockLine
                Layout.fillWidth: true
                Text {
                    text: "CONFIRM PASSWORD"
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
                id: confirmPasswordInputBlock
                border.width: 1
                border.color: (error === 7  ? "#d9212c" : "#D4D9E2")
                height: 40
                Layout.fillWidth: true
                Layout.topMargin: 12
                TextInput {
                    id: confirmPasswordInput
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
            id: infoMsg
            Layout.alignment: Qt.AlignHCenter
            font.family: "Arial"
            font.pixelSize: 12
            font.weight: 600
            color: "green"
            clip: true
            visible: error === 0
        }

        Text {
            id: userErrorMsg
            Layout.alignment: Qt.AlignHCenter
            font.family: "Arial"
            font.pixelSize: 12
            font.weight: 600
            color: "#d9212c"
            clip: true
            visible: error >= 6
        }

        Text {
            id: serverErrorMsg
            Layout.alignment: Qt.AlignHCenter
            font.family: "Arial"
            font.pixelSize: 12
            font.weight: 600
            color: "#0d8bf2"
            clip: true
            visible: error < 6
        }

        Rectangle {
            id: registerButton
            Layout.fillWidth: true
            Layout.topMargin: 10
            height: 40
            color: "green"

            Text {
                font.family: "Arial"
                font.pixelSize: 12
                font.letterSpacing: 0.8
                color: "white"
                text: "SIGN UP"
                anchors.centerIn: parent
            }

            DataContainer {
                id: formData;
            }

            RequestManager {
                id: regRequest
                method: "POST"
                onFinished: {
                    regRequest.setCredentials(loginInput.text, passwordInput.text);
                    console.log(JSON.stringify(regRequest.reply));
                    registerForm.finish(regRequest.reply);
                }
                onFailed: (code, msg) => {
                    registerForm.error = code;
                    if(code < 6) 
                        serverErrorMsg.text = msg;
                    else 
                        userErrorMsg.text = msg;
                    
                }
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    if(!passwordInput.acceptableInput || !loginInput.acceptableInput || !emailInput.acceptableInput) {
                        error = 8;
                        userErrorMsg.text = "Input error: not allowed text patterns";
                    }
                    else if(emailInput.text.search(/^[0-9A-Za-z\.]+@[0-9A-Za-z\.]+$/) === -1) {
                        error = 9;
                        userErrorMsg.text = "Incorrect email";
                    }
                    else if(confirmPasswordInput.text !== passwordInput.text) {
                        error = 7;
                        userErrorMsg.text = "Passwords are different";
                    }
                    else if(passwordInput.text && loginInput.text && emailInput.text) {
                        formData.add("user", {
                            "login": loginInput.text,
                            "password" : passwordInput.text,
                            "email" : emailInput.text
                        });
                        regRequest.exec(QueryBuilder.resource("/register"), formData.toJSON());

                        error = 0;
                        infoMsg.text = "Check your email for incoming verification message";
                    } 
                }
            }

        }

         Text {
            id: loginLink
            Layout.alignment: Qt.AlignHCenter
            text: "Log In"
            font.family: "Arial"
            font.pixelSize: 12
            color: "green"
            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: login();
            }
        }

    }

}