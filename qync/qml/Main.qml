import QtQuick 2.0
import QtQuick.Controls 1.1
import QyncSipe 1.0

Rectangle {
    id: mainRect
    width: 320
    height: 640

    LoginView {
        id: loginView
        visible: true
    }

    LoginWaitingView {
        id: loginWaitingView
        visible: false
    }

    BuddyListView {
        id: buddyView
        visible: false
    }

    states: [
        State {
            name: "WAITING"
            when: qyncSipe.status == QyncSipe.StatusInProcess

            PropertyChanges {
                target: loginWaitingView
                visible: true
            }
        },

        State {
            name: "ONLINE"
            when: (qyncSipe.status != QyncSipe.StatusInProcess &&
            qyncSipe.status != QyncSipe.StatusOffline)

            PropertyChanges {
                target: loginWaitingView
                visible: false
            }

            PropertyChanges {
                target: buddyView
                visible: true
            }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "WAITING"
            SequentialAnimation {
                NumberAnimation {
                    target: loginView
                    duration: 200
                    properties: "opacity"
                    from: 1
                    to: 0
                    easing {type: Easing.OutQuad}
                }
                NumberAnimation {
                    target: loginWaitingView
                    duration: 500
                    properties: "opacity"
                    from: 0
                    to: 1
                    easing {type: Easing.OutQuad}
                }
            }

        },

        Transition {
            from: "WAITING"
            to: ""
            SequentialAnimation {
                NumberAnimation {
                    target: loginWaitingView
                    duration: 200
                    properties: "opacity"
                    from: 1
                    to: 0
                    easing {type: Easing.OutQuad}
                }
                NumberAnimation {
                    target: loginView
                    duration: 500
                    properties: "opacity"
                    from: 0
                    to: 1
                    easing {type: Easing.OutQuad}
                }
            }
        }
    ]
}
