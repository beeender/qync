import QtQuick 2.0

Item {
    id: buddyItem
    height: 40
    Row {
        id: buddyItemRow

        Image {
            id: buddyImage
            width: 100
            source: "qrc:/qtquickplugin/images/template_image.png"
        }

        Text {
            id: aliasText
            text: aliasName
            font.pixelSize: 12
        }
    }

}
