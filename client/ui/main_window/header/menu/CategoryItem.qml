import QtQuick 2.15

Item {
    id: categoryItem
    property bool isActive: false
    property string itemText: ""
    Text {
        id: categoryText
        text: itemText.toUpperCase()
        font.family: "Open Sans"
        font.weight: 700
        font.pixelSize: 14
        color: categoryItem.isActive ? "#D72130" : "#B2B2B2"
        anchors.centerIn: parent

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                //categoryMenu.currentItem = categoryMenu.itemAtIndex(ind);
                console.log(ind)
                categoryMenu.currentIndex = ind
                categoryMenu.positionViewAtIndex(ind, ListView.Beginning);
            }
        }
    }
}
