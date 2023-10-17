import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQml.Models 2.15

import "menu/"

Item {
    id: menuLine
    width: parent.width
    height: 45

    Rectangle {
        id: leftArrowIconBlock
        width: parent.width * 0.1
        height: parent.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 1) }
            GradientStop { position: 0.7; color: Qt.rgba(1, 1, 1, 0.5) }
            GradientStop { position: 1.0; color: Qt.rgba(1, 1, 1, 0) }
            orientation: Gradient.Horizontal
        }
        anchors.left: parent.left
        z: 1

        Image {
            id: leftArrowIcon
            fillMode: Image.PreserveAspectFit
            source: {
                var path = "qrc:/assets/images/main_window/header/hmenu/"
                if(categoryMenu.currentIndex === 0)
                    return path+"left-arrow.svg"
                else
                    return path+"left-arrow-active.svg"
            }
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 35
            z: 2

            MouseArea {
                id: leftArrowIcon_mouseHandler
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    if(categoryMenu.currentIndex > 0) {
                        categoryMenu.decrementCurrentIndex();
                        categoryMenu.positionViewAtIndex(categoryMenu.currentIndex, ListView.Beginning);
                    }

                }
            }
        }
    }



    Rectangle {
        id: categoryMenuBlock
        width: parent.width * 0.8
        height: parent.height
        anchors.centerIn: parent
        anchors.leftMargin: 30

        ListView {
            id: categoryMenu
            property var categoryItems: []

            width: parent.width
            height: parent.height
            anchors.centerIn: parent

            orientation: Qt.Horizontal
            spacing: parent.width * 0.1

            model: ListModel {
                id: menuListModel
                Component.onCompleted: {
                    for(var i = 0; i < 12; i++){
                        var itm = { "elText" : "Sample" + i, "elActive" : false, "ind" : i};
                        append(itm);
                        categoryMenu.categoryItems.push(itm);
                    }
                }
            }
            delegate: CategoryItem {
                id: menuIt
                itemText: elText
                isActive: ListView.isCurrentItem
                anchors.verticalCenter: parent.verticalCenter
            }
            displayMarginBeginning: parent.width * 0.25
            displayMarginEnd: parent.width * 0.25

        }

    }

    Rectangle {
        width: parent.width * 0.1
        height: parent.height
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0) }
            GradientStop { position: 0.3; color: Qt.rgba(1, 1, 1, 0.5) }
            GradientStop { position: 1.0; color: Qt.rgba(1, 1, 1, 1) }
            orientation: Gradient.Horizontal
        }
        anchors.right: parent.right
        z: 1

        Image {
            id: rightArrowIcon
            fillMode: Image.PreserveAspectFit
            source: {
                var path = "qrc:/assets/images/main_window/header/hmenu/"
                if(categoryMenu.currentIndex === categoryMenu.count - 1)
                    return path+"left-arrow.svg"
                else
                    return path+"right-arrow-active.svg"
            }
            mirror: categoryMenu.currentIndex === categoryMenu.count - 1
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 35
            z: 2

            MouseArea {
                id: rightArrowIcon_mouseHandler
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    if(categoryMenu.currentIndex < categoryMenu.count) {
                        categoryMenu.incrementCurrentIndex();
                        categoryMenu.positionViewAtIndex(categoryMenu.currentIndex, ListView.Beginning);
                    }
                }
            }
        }
    }


}
