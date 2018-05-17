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
                iconCharacter: ""
                description: ""
                image: "../images/lines.png";
                hoverColour: "#b4b4d9"
                onNavigationButtonClicked: isCollapsed = !isCollapsed
            }
            NavigationButton {
                iconCharacter: ""
                description: "Chats"
                image: "../images/message.png";
                hoverColour: "#b4b4d9"
                onNavigationButtonClicked: masterController.ui_navigationController.goChatListView();
            }
            NavigationButton {
                iconCharacter: ""
                description: "Friends"
                image: "../images/friends.png";
                hoverColour: "#b4b4d9"
                onNavigationButtonClicked: masterController.ui_navigationController.goFriendListView();
            }

            NavigationButton {
                iconCharacter: ""
                description: "Settings"
                image: "../images/settings.png";
                hoverColour: "#b4b4d9"
                onNavigationButtonClicked: masterController.ui_navigationController.goChatView(); //change
            }

            NavigationButton {
                iconCharacter: ""
                description: "Exit"
                image: "../images/exit.png";
                hoverColour: "#b4b4d9"
                onNavigationButtonClicked: masterController.ui_navigationController.goExitView();
            }


        }
    }
}
