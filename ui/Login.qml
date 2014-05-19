import QtQuick 2.0
import QtQuick.Controls 1.1

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
        visible: false
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
            text: qsTr("Button")
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    MouseArea {
        id: mouseArea1
        x: 30
        y: 307
        width: 80
            height: 58
        }

    states: [

        State {
            name: "WAITING"
            when: mouseArea1.pressed == true

            PropertyChanges {
                target: startColumn
                visible: true
            }

            PropertyChanges {
                target: waitingColumn
                visible: true
            }

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
        }
    ]

    transitions: [
        Transition {
            from: ""
            to: "WAITING"
            reversible: true
            SequentialAnimation {
                id: animateOpacity
                NumberAnimation {
                    target: startColumn
                    duration: 1050
                    properties: "opacity"
                    from: 1
                    to: 0
                    easing {type: Easing.OutQuad}
                }
                PropertyAnimation {
                    target: startColumn
                    properties: "visible"; easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: waitingColumn
                    duration: 1000
                    properties: "opacity"
                    from: 0
                    to: 1
                    easing {type: Easing.OutQuad}
                }
            }

        }
    ]

}
