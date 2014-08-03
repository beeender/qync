import QtQuick 2.0
import QtQuick.Controls 1.1

Column {
    id: column1
    anchors.right: parent.right
    anchors.rightMargin: 30
    anchors.left: parent.left
    anchors.leftMargin: 30

    ProgressBar {
        id: progressBar
        anchors.horizontalCenter: parent.horizontalCenter
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
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
