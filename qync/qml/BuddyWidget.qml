import QtQuick 2.0

Rectangle {
    id: buddyRectangle
    width: 300
    height: 62
    property string accountId: ""
    property string displayName
    property string statusString
    property Image image

    Row {
        id: row
        anchors.fill: parent

        Rectangle {
            id: imageRectangle
            anchors.right: textColumn.left
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0

            Image {
                id: buddyImage
                fillMode: Image.PreserveAspectFit
                anchors.rightMargin: 10
                anchors.leftMargin: 10
                anchors.bottomMargin: 10
                anchors.topMargin: 10
                anchors.fill: parent
                source: "qrc:/images/.png"
            }
        }

        Column {
            id: textColumn
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 100

            Text {
                id: buddyText
                text: displayName
                anchors.top: parent.top
                anchors.topMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                font.pixelSize: 12
            }

            Text {
                id: statusText
                text: statusString
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                font.pixelSize: 12
            }
        }


    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        opacity: 0
    }
    states: [
        State {
            name: "StateActive"

            PropertyChanges {
                target: imageRectangle
                color: "#5ecf85"
            }
        },
        State {
            name: "StateInactive"

            PropertyChanges {
                target: imageRectangle
                color: "#e9fc84"
            }
        },
        State {
            name: "StateBusy"

            PropertyChanges {
                target: imageRectangle
                color: "#fc9183"
            }
        }
    ]
}
