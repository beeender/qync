import QtQuick 2.0

Item {
    id: buddyItem
    height: 50
    Row {
        id: buddyItemRow

        Image {
            id: buddyImage
            width: 40
            height: 40
            anchors.verticalCenter: parent.verticalCenter
            fillMode: Image.PreserveAspectFit
            source: buddy.imageUrl
        }

        Text {
            id: aliasText
            text: buddy.alias
            font.pixelSize: 12
        }
    }

}
