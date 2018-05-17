import QtQuick 2.9
import assets 1.0

Item {
    anchors {
        top: parent.top
        bottom: parent.bottom
        left: parent.left
    }
    property bool isCollapsed: true
    width: isCollapsed ? Style.widthNavigationBarCollapsed : Style.heightNavigationBarExpanded

    Rectangle {
        anchors.fill: parent
        color: Style.colourNavigationBarBackground
        Column {
            width: parent.width
            NavigationButton {
                iconCharacter: "\uf0c9"
                description: ""
                hoverColour: "#993333"
                onNavigationButtonClicked: isCollapsed = !isCollapsed
            }
            NavigationButton {
                iconCharacter: "\uf015"
                description: "Chats"
                hoverColour: "#dc8a00"
                onNavigationButtonClicked: masterController.ui_navigationController.goChatListView();
            }
            NavigationButton {
                iconCharacter: "\uf234"
                description: "Friends"
                hoverColour: "#dccd00"
                onNavigationButtonClicked: masterController.ui_navigationController.goFriendListView();
            }
            NavigationButton {
                iconCharacter: "\uf002"
                description: "Exit"
                hoverColour: "#8aef63"
                onNavigationButtonClicked: masterController.ui_navigationController.goExitView();
            }

        }
    }
}
