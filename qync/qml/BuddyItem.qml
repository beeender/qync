import QtQuick 2.0
import QyncSipe 1.0

Item {
    id: buddyItem
    height: 50
    width:320
    Row {
        id: buddyItemRow


        Rectangle {
            id: statusRect
            width: 10
            height: 40
            color: {
                var co = "transparent";
                console.log(buddy.status);
                switch(buddy.status) {
                case QyncSipe.StatusActive:
                    co = "green";
                    break;
                case QyncSipe.StatusInactive:
                    co = "yellow";
                    break;
                case QyncSipe.StatusBusy:
                    co = "red";
                    break;
                case QyncSipe.StatusDND:
                case QyncSipe.StatusAway:
                    co = "red";
                    break;
                case QyncSipe.StatusOffline:
                default:
                    break;
                }
                co;
            }
        }

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
