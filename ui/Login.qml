import QtQuick 2.0
import QtQuick.Controls 1.1
import QyncSipe 1.0

Rectangle {
    id: loginPanel
    width: 320
    height: 640

    Column {
        id: startColumn
        y: 120
        height: 400
        visible: true
        anchors.right: parent.right
        anchors.rightMargin: 30
        anchors.left: parent.left
        anchors.leftMargin: 30

        Label {
            id: accountLabel
            text: qsTr("Account:")
            verticalAlignment: Text.AlignTop
            transformOrigin: Item.Right
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        TextField {
            id: accountTextField
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            placeholderText: qsTr("user@company.com")
        }

        Label {
            id: usernameLabel
            text: qsTr("Username:")
            verticalAlignment: Text.AlignTop
            transformOrigin: Item.Right
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        TextField {
            id: usernameTextField
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
            placeholderText: qsTr("Domain\\username")
        }

        Label {
            id: passwordLabel
            text: qsTr("Password:")
            verticalAlignment: Text.AlignTop
            transformOrigin: Item.Right
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        TextField {
            id: passwordTextField
            inputMask: qsTr("")
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.left: parent.left
            anchors.leftMargin: 0
        }

        Button {
            id: loginButton
            text: qsTr("Login")
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                qyncSipe.accountName = accountTextField.text;
                qyncSipe.domainUser = usernameTextField.text;
                qyncSipe.password = passwordTextField.text;
                qyncSipe.start();
            }
        }
    }

    Column {
        id: waitingColumn
        y: 120
        height: 118
        opacity: 0
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

    states: [

        State {
            name: "WAITING"
            when: qyncSipe.status == QyncSipe.InProcess

            PropertyChanges {
                target: emailTextField
                readOnly: true
            }

            PropertyChanges {
                target: usernameTextField
                readOnly: true
            }

            PropertyChanges {
                target: passwordTextField
                readOnly: true
            }

            PropertyChanges {
                target: loginButton
                enabled: false
                checkable: false
            }

            PropertyChanges {
                target: waitingColumn
                opacity: 0
            }
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "WAITING"
            SequentialAnimation {
                NumberAnimation {
                    target: startColumn
                    duration: 200
                    properties: "opacity"
                    from: 1
                    to: 0
                    easing {type: Easing.OutQuad}
                }
                NumberAnimation {
                    target: waitingColumn
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
                    target: waitingColumn
                    duration: 200
                    properties: "opacity"
                    from: 1
                    to: 0
                    easing {type: Easing.OutQuad}
                }
                NumberAnimation {
                    target: startColumn
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
