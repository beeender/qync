import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ScrollView {
    anchors.fill: parent

    ListView {
        anchors.fill: parent
        model: groupListModel

        Component {
            id: catergoryDelegate

            Column {
                Text {
                    id: catergoryText
                    text: groupName
                }
                ListView {
                    height: 40 * count
                    width: parent.width
                    model: buddyListModel
                    interactive: false
                    delegate:  BuddyItem {
                    }
                }
            }
        }

        delegate: Column {
            Loader {
                property string groupName: name
                property var buddyListModel: groupListModel.getBuddyListModel(index)
                sourceComponent: catergoryDelegate
            }
        }
    }
}
