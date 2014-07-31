import QtQuick 2.0
import QtQuick.Controls 1.1

Column {
    y: 120
    height: 118
    anchors.right: parent.right
    anchors.rightMargin: 30
    anchors.left: parent.left
    anchors.leftMargin: 30

    ProgressBar {
        id: progressBar
        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        indeterminate: true
        activeFocusOnTab: false
    }

    Text {
        id: watingText
        text: qsTr("Please wait...")
        horizontalAlignment: Text.AlignHCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: 12
    }

    Button {
        id: cancelButton
        text: qsTr("Cancel")
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
