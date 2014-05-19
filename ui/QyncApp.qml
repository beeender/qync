import QtQuick 2.2
import QtQuick.Controls 1.1
import QtQuick.Window 2.0

ApplicationWindow {
    visible: true
    title: qsTr("Qync")
    width: 320
    height: 640
    color: "green"

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }

    Login {
        id: login1
        anchors.fill: parent
    }

}
