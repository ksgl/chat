import QtQuick 2.9
import QtQuick.Window 2.3
import QtQuick.Controls 2.2
import components 1.0
import assets 1.0

Window {
    visible: true
    width: Style.widthWindow
    height: Style.heightWindow
    title: qsTr("Chat")

    Connections {
        target: masterController.ui_navigationController
        onGoChatListView: {
            navigationBar.visible = true;
            contentFrame.replace("qrc:/views/ChatListView.qml");
        }
        onGoChatView: contentFrame.replace("qrc:/views/ChatView.qml")
        onGoFriendListView: contentFrame.replace("qrc:/views/FriendListView.qml")
        onGoAddFriendView: contentFrame.replace("qrc:/views/AddFriendView.qml")
        onGoExitView: contentFrame.replace("qrc:/views/ExitView.qml")
        onGoRegistrationView: contentFrame.replace("qrc:/views/RegistrationView.qml")
        onGoLoginView: {
            navigationBar.visible = false;
            contentFrame.replace("qrc:/views/LoginView.qml");
        }

    }

    NavigationBar {
        id: navigationBar
        visible: false
    }

    StackView {
        id: contentFrame
        clip: true
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
            left: navigationBar.right
        }

        initialItem: Qt.resolvedUrl("qrc:/views/SplashView.qml")
    }

    Component.onCompleted: contentFrame.replace("qrc:/views/LoginView.qml");

}
