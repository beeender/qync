import QtQuick 2.0
import QtQuick.Controls 1.0
import QtQuick.Layouts 1.0

ScrollView {
    anchors.fill: parent

    ListView {
        transformOrigin: Item.Center
        model: buddyListModel

        delegate: BuddyListItem {
            nameStr: aliasName
            isGroupItem: isGroup
            groupNameStr: groupName
        }
    }
}
