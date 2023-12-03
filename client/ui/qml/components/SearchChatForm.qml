import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls


Rectangle {
    id: searchChatBlock
    signal titleEdited(title: string)

    height: 25
    radius: 20
    color: "#e4e7ec"
       
    TextInput {
        id: chatInput
        width: parent.width
        anchors.verticalCenter: parent.verticalCenter
        leftPadding: 16
        font.family: "Arial"
        font.pixelSize: 12
        font.weight: 600
        color: "#57647a"
        clip: true
        onTextEdited: titleEdited(chatInput.text)
    }
    
    Text {
        id: сhatInputPlaceholder
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 16
        anchors.left: parent.left
        font.family: "Arial"
        font.pixelSize: 12
        font.weight: 600
        color: "#C6CCD7"
        text: "Search chat by title..."
        visible: chatInput.text === ""
        clip: true
    }

    

}