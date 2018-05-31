import QtQuick 2.9
import CHAT 1.0
import assets 1.0
import components 1.0

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2

Item {
        property Friend friend
        property  int friendStatus : friend.ui_status.ui_value

        implicitWidth: parent.width
        implicitHeight: Math.max(clientColumn.implicitHeight) + (Style.heightDataControls / 2)

        Rectangle {
            id: background
            width: parent.width
            height: parent.height
            color: Style.colourPanelBackground

            RowLayout {
                id: clientColumn
                width: parent / 2
                anchors {
                    left: parent.left
                    top: parent.top
                    margins: Style.heightDataControls / 4
                }
                spacing: Style.heightDataControls / 2

                Rectangle {
                     id: status
                     anchors.left: parent.left
                     anchors.leftMargin: 10
                     width: 20
                     height: width
                     color: friendStatus === 1 ? "lightGreen" : "grey"
                     radius: width*0.5
                }

                Text {
                    id: textName
                    anchors.left: status.right
                    text: "\t" + friend.ui_friendName.ui_value
                    font.pixelSize: Style.pixelSizeDashboard
                    color: Style.colourPanelFont
                }

                Text {
                    id: lastVisit
                    anchors.left: textName.right
                    text: friendStatus === 1 ? "" : "\t last visit: " + Qt.formatDateTime(friend.ui_lastVisit.ui_value, "d MMM hh:mm")
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
                onClicked: masterController.ui_viewController.ui_chatListModelView.gui_chatDetailViewRequested(friend.ui_reference.ui_value)
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

}
