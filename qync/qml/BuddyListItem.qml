import QtQuick 2.0

Rectangle {
    width: 100
    height: {
        if (!visible) {
            return 0;
        } else if (isGroupItem) {
            return 20;
        } else {
            return 60;
        }
    }

    property bool isGroupItem: false
    property string groupNameStr: ""
    property string accountStr: ""
    property string nameStr: ""
    property string statusStr: ""
    property Image image

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            if (isGroupItem) {
                var found = false;
                var listViewChildren = parent.parent.children;
                for(var i = 0; i < listViewChildren.length; ++i) {
                    //Found the group
                    if(listViewChildren[i].groupNameStr === groupNameStr) {
                        found = true;
                        continue;
                    }
                    //Found the next group
                    if(found && listViewChildren[i].isGroupItem) {
                        break;
                    }
                    //Hide the items in this group
                    if(found) {
                        listViewChildren[i].visible = !listViewChildren[i].visible;
                    }
                }
            } else {
                console.log("Not isGroup");
            }

        }
    }

    Component {
        id: buddyComponent
        Row {
            Column {
                Text {
                    id: nameText
                    text: nameStr
                }
            }

        }
    }

    Component {
        id: groupComponent

        Rectangle {
            id: groupRect
            Text {
                id: groupText
                text: groupNameStr
            }
        }
    }

    Loader {
        sourceComponent: isGroupItem ? groupComponent : buddyComponent
    }
}
