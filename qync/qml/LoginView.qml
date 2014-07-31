import QtQuick 2.0
import QtQuick.Controls 1.1
import QyncSipe 1.0

Column {
    y: 120
    height: 400
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
        text: ""
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
        text: ""
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
        text: ""
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

