import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: loginWindow
    width: 640
    height: 590
    visible: true
    title: qsTr("Sports Hub")
    signal loginFinished()

    FontLoader {
        id: fSFProBold
        source: "qrc:/assets/fonts/SF-Pro-Text-Bold.otf"
    }

    FontLoader {
        id: fRobotoMedium
        source: "qrc:/assets/fonts/Roboto-Medium.ttf"
    }

    FontLoader {
        id: fRobotoBold
        source: "qrc:/assets/fonts/Roboto-Bold.ttf"
    }

    Rectangle {
        id: loginWindowHeader
        width: parent.width
        height: 40
        color: "#2B2F43"
        anchors.top: parent.top

        Text {
            color: "white"
            text: "Log in | Sports Hub"
            font.family: fSFProBold.font.family
            font.pixelSize: 13
            font.weight: fSFProBold.font.weight
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
        id: loginWindowDiv
        width: (parent.width <= 390 ? parent.width * 0.9 : 390)
        height: (parent.height <= 405 ? parent.height * 0.9 : 405)
        anchors.centerIn: parent

        Image {
            id: sportHubIcon
            source: "qrc:/assets/images/login_window/SH.png"
            Layout.alignment: Qt.AlignHCenter
        }

        Text {
            id: loginWindowTitle
            text: "Log in to Sports Hub"
            font.family: "Open Sans"
            font.pixelSize: 24
            font.weight: 600
            color: "black"
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: parent.height * 0.1
        }

        Item {
            id: regViaButtons
            width: 80
            height: 32
            Layout.alignment: Qt.AlignHCenter
            Layout.topMargin: parent.height * 0.05
            Layout.bottomMargin: parent.height * 0.05
            Image {
                id: facebookButton
                source: "qrc:/assets/images/login_window/FB.svg"
                anchors.left: parent.left
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor

                }
            }
            Image {
                id: gmailButton
                source: "qrc:/assets/images/login_window/Gmail.svg"
                anchors.right: parent.right
                MouseArea {
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor

                }
            }
        }
        Text {
            id: incorrectInfoLabel
            font.family: "Open Sans"
            font.weight: 600
            font.pixelSize: 14
            text: "Incorrect user ID or password. Try again."
            color: "#D72130"
            visible: false
        }

        ColumnLayout {
            id: emailBlock
            Layout.fillWidth: true
            Layout.topMargin: 15
            Item {
                id: emailBlockLine
                Text {
                    text: "EMAIL ADDRESS"
                    color: "#434C5D"
                    lineHeight: 1.1
                    font.family: fRobotoMedium.font.family
                    font.pixelSize: 10
                    font.letterSpacing: 0.9
                    font.weight: fRobotoMedium.font.weight
                    anchors.left: parent.left
                }
            }
            Rectangle {
                id: emailInputBlock
                border.width: 1
                border.color: "#D4D9E2"
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
                }
                Text {
                    id: emailInputPlaceholder
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.leftMargin: 16
                    font.family: "Open Sans"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "#C6CCD7"
                    text: "Email@gmail.com"
                    visible: emailInput.text === ""
                }
                Image {
                    id: incorrectEmailIcon
                    source: "qrc:/assets/images/login_window/x.svg"
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
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
                    font.family: fRobotoMedium.font.family
                    font.pixelSize: 10
                    font.letterSpacing: 0.9
                    font.weight: fRobotoMedium.font.weight
                    anchors.left: parent.left
                }
                Text {
                    text: "Forgot password ?"
                    color: "#4A90E2"
                    font.family: "Open Sans"
                    font.pixelSize: 10
                    font.weight: 600
                    anchors.right: parent.right
                    MouseArea {
                        anchors.fill: parent;
                        cursorShape: Qt.PointingHandCursor
                    }
                }
            }
            Rectangle {
                id: passwordInputBlock
                border.width: 1
                border.color: "#D4D9E2"
                height: 40
                Layout.fillWidth: true
                Layout.topMargin: 12
                TextInput {
                    id: passwordInput
                    width: parent.width
                    anchors.verticalCenter: parent.verticalCenter
                    leftPadding: 16
                    rightPadding: 30
                    font.family: "Open Sans"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "black"
                    echoMode: TextInput.Password
                    clip: true
                }
                Text {
                    id: passwordInputPlaceholder
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.leftMargin: 16
                    anchors.left: parent.left
                    font.family: "Open Sans"
                    font.pixelSize: 12
                    font.weight: 600
                    color: "#C6CCD7"
                    text: "8+ characters (letters and numbers)"
                    visible: passwordInput.text === ""
                    clip: true
                }
                Image {
                    id: incorrectPasswordIcon
                    source: "qrc:/assets/images/login_window/x.svg"
                    visible: false
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                }

            }
        }

        Rectangle {
            id: loginButton
            Layout.fillWidth: true
            Layout.topMargin: 35
            height: 40
            color: "#D72130"

            Text {
                font.family: fRobotoBold.font.family
                font.weight: fRobotoBold.font.weight
                font.pixelSize: 12
                font.letterSpacing: 0.8
                color: "white"
                text: "LOG IN"
                anchors.centerIn: parent
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    passwordInputBlock.border.color = "#D72130"
                    emailInputBlock.border.color = "#D72130"
                    incorrectEmailIcon.visible = true
                    incorrectPasswordIcon.visible = true
                    incorrectInfoLabel.visible = true
                    loginWindow.loginFinished()
                }
            }

        }

    }

    onLoginFinished: Qt.exit(1)


}



