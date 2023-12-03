import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services
import data

ScrollView {
    id: messagesBlockView
    property var user
    property Item chatItem

    ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
    contentWidth: parent.width-20
     
    Column {
        id: messagesBlock
        anchors.fill: parent
        spacing: 5
        padding: 20
    }

    Connections {
        target: chatItem
        function onUpdated(msgs) {
            var N = messagesBlock.children.length;
            var id_lst = N > 0? messagesBlock.children[N-1].message["id"] : 0;
            msgs.forEach((msg) => {
                if(msg["id"] > id_lst) add(msg);
            })
        }
        function onDeleted(){
            clear();
        }
    }

    function load() {
        clear();
        chatItem.chat["messages"].forEach((message) =>{
            add(message);
        });
    }

    function show(messageData) {
        console.log(chatItem.chat["title"] + ": " + JSON.stringify(chatItem.chat["messages"]));
        var comp = Qt.createComponent("MessageBlock.qml");
        var message;
        if(messageData["login"] == user["login"]) {
            message = comp.createObject(messagesBlock, {
                "message" : messageData,
                "anchors.right" : messagesBlock.right,
                "anchors.rightMargin" : 5
            });
        }
        else {
            message = comp.createObject(messagesBlock, {
                "message" : messageData,
                "anchors.left" : messagesBlock.left,
                "anchors.leftMargin" : 5
            });
        }
    }

    function add(messageData) {
        show(messageData);
        messagesBlockView.ScrollBar.vertical.position = 1.0;
    }

    function clear() {
        messagesBlock.children.forEach((msgBlock)=>{
            msgBlock.destroy();
        });
    }


}