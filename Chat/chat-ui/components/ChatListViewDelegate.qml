import QtQuick 2.9
import CHAT 1.0
import assets 1.0
import components 1.0

Item {
        property ChatModel chatModel
        property Message lastMessage : chatModel.ui_lastMessage ? chatModel.ui_lastMessage : ""

        implicitWidth: parent.width
        implicitHeight: Math.max(clientColumn.implicitHeight) + (Style.heightDataControls / 2)

        Rectangle {
            id: background
            width: parent.width
            height: parent.height
            color: Style.colourPanelBackground

            Column {
                id: clientColumn
                width: parent / 2
                anchors {
                    left: parent.left
                    top: parent.top
                    margins: Style.heightDataControls / 4
                }
                spacing: Style.heightDataControls / 2
                Text {
                    id: textName
                    anchors.left: parent.left
                    text: chatModel.ui_friendInChatName.ui_value
                    font.pixelSize: Style.pixelSizeNavigationBarText
                    color: Style.colourPanelFont
                }
                Text {
                    id: textReference
                    anchors.left: parent.left
                    text: lastMessage.ui_sendAt.ui_prettyTimeString + " : \t" +  lastMessage.ui_messageData.ui_value
                    font.pixelSize: Style.pixelSizeDataControls
                    color: Style.inputStringBorderColor
                }

            }

            Rectangle {
                id: borderBottom
                anchors {
                    bottom: parent.bottom
                    left: parent.left
                    right: parent.right
                }
                height: 1
                color: Style.colourPanelFont
            }

            MouseArea {
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true
                onEntered: background.state = "hover"
                onExited: background.state = ""
                onClicked: masterController.ui_viewController.ui_chatListModelView.gui_chatDetailViewRequested(chatModel.ui_reference.ui_value)
            }

            states: [
                State {
                    name: "hover"
                    PropertyChanges {
                        target: background
                        color: Style.colourPanelBackgroundHover
                    }
                }
            ]
        }

        Connections {
            target: chatModel
            onLastMessageChanged: {
                lastMessage = chatModel.ui_lastMessage
            }
        }
}
