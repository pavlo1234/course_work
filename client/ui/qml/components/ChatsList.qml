import QtQuick

import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls

import services
import data

ScrollView {
    id: chatsListView
    property var user
    property var chats
    property Item activeChat
    signal chatSelected(chat: var)
    signal error(msg: string)

    contentWidth: width
    
    Column {
        id: chatsList
        anchors.fill: parent
        spacing: 5
    }

   
    Component.onCompleted: {
        load();
        updating.start();
    }

    RequestManager {
        id: chatsListUpdateRequest
        method: "GET"
        onFinished: {
            add(chatsListUpdateRequest.reply["chat"]);
            chatsListUpdateRequest.reply["chats"].forEach((chat)=>{
                add(chat);
            });
        }
        onFailed: (code) => {
            if(code === 1)
                error("Server is not responding. Trying to connect...");
        }
    }

    Timer {
        id: updating
        interval: 1000
        repeat: true 
        running: false
        onTriggered: {
            var id_from = chats.length > 0 ? chats[chats.length-1]["id"] : "0";
            chatsListUpdateRequest.exec(QueryBuilder.resource("user/chats", {
                "id-from" : id_from
            }));
        }
    }

    function load() {
        clear();
        chats.forEach((chat) => {
            show(chat);
        });
    }

    function filter(title) {
        chatsList.children.forEach((chatBlock) => {
            chatBlock.visible = (chatBlock.chat["title"].search(title) !== -1);
        });
    }

    function add(chatData) {
        chats.push(chatData);
        show(chatData);
        chatsListView.ScrollBar.vertical.position = 1.0;
    }

    function show(chatData){
        var comp = Qt.createComponent("ChatBlock.qml");
        var chat = comp.createObject(chatsList, {
            "chat" : chatData
        });
        if(comp.status !== Component.Ready)
            console.log("comp is not ready ");
        if(comp.status === Component.Error)
            console.log("Error: " + comp.errorString());
        
        chat.selected.connect(function(chatBlock){
            if(activeChat == chatBlock)
                return;
            if(activeChat !== null) 
                activeChat.active = false;
            activeChat = chatBlock;
            activeChat.active = true;
            chatSelected(chatBlock.chat)
            console.log("selected() event captured");
        });
    }

    function remove(chatItem) {
        var ind = chats.findIndex((chat) => { 
            chat === chatItem
        });
        chats.splice(ind, 1);
        chatItem.destroy();
    }

    function clear() {
        chatsList.children.forEach((chatBlock)=>{
            chatBlock.destroy();
        });
    }

}