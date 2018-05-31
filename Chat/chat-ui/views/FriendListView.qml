import QtQuick 2.9
import components 1.0
import assets 1.0
import CHAT 1.0

import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import QtQuick.Controls 2.3

Item {
    property FriendListViewModel friendListViewModel: masterController.ui_viewController.ui_friendListViewModel
    id: columnWithRectangle

    Rectangle {
        anchors.fill: parent
        color: Style.colourBackground

        Text {
            id:welcomeText
            anchors {
                left: parent.left
                top: parent.top
                leftMargin: 30
                topMargin: 100
            }
            text: "My Friends"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboard
        }

        Text {
            id: stateText
            anchors {
                left: parent.left
                top: parent.top
                leftMargin: 30
                topMargin: 150
            }
            text: ""
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDataControls
        }

        ListView {
            id: itemsView
            anchors {
                top: stateText.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                margins: Style.sizeScreenMargin
            }
            clip: true
            model: friendListViewModel.ui_friends
            delegate:
                FriendListViewDelegate {
                    friend: modelData
                }
        }
    }

    states: [
            State {
                name: "No Friends"
                when: friendListViewModel.isEmpty()
                PropertyChanges {
                    target: stateText
                    text: "No friends so far, add some"
                }
            },
            State {
                name: "Friends"
                when: !friendListViewModel.isEmpty()
                PropertyChanges {
                    target: stateText
                    text: ""
                }
            }
    ]


    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_friendListViewContextCommands
    }
}
