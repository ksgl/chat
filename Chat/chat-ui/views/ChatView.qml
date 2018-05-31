import QtQuick 2.9
import components 1.0
import assets 1.0
import CHAT 1.0

import QtQuick.Layouts 1.3
import QtQuick.Controls 2.2


Page {
    id: root
    property ChatDetailViewModel chatDetailViewModel : masterController.ui_viewController.ui_chatDetailViewModel
    property string inConversationWith : chatDetailViewModel.ui_friend.ui_friendName.ui_value

    header: ToolBar {
        ToolButton {
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: masterController.ui_navigationController.goChatListView
        }

        Label {
            id: pageTitle
            text: inConversationWith
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ColumnLayout {
           anchors.fill: parent

           ListView {
                  id: listView
                  Layout.fillWidth: true
                  Layout.fillHeight: true
                  Layout.margins: pane.leftPadding + messageField.leftPadding
                  displayMarginBeginning: 40
                  displayMarginEnd: 40
                  //verticalLayoutDirection: ListView.BottomToTop
                  spacing: 12
                  model: chatDetailViewModel.ui_messages

                  delegate: Column {
                          anchors.right: sentByMe ? parent.right : undefined
                          spacing: 6

                          readonly property int messageType : modelData.ui_messageType.ui_value
                          readonly property bool sentByMe: messageType !== 1

                          Row {
                              id: messageRow
                              spacing: 6
                              anchors.right: sentByMe ? parent.right : undefined

                              Rectangle {
                                  width: Math.min(messageText.implicitWidth + 24,
                                      listView.width - (!sentByMe ? messageRow.spacing : 0))
                                  height: messageText.implicitHeight + 24
                                  color: sentByMe ? "lightgrey" : "steelblue"

                                  Label {
                                      id: messageText
                                      text: modelData.ui_messageData.ui_value
                                      color: sentByMe ? "black" : "white"
                                      anchors.fill: parent
                                      anchors.margins: 12
                                      wrapMode: Label.Wrap
                                  }
                              }
                          }

                          Label {

                              id: timestampText
                              text: Qt.formatDateTime(modelData.ui_sendAt.ui_value, "d MMM hh:mm")
                              color: "lightgrey"
                              anchors.right: sentByMe ? parent.right : undefined
                          }
                      }

                  ScrollBar.vertical: ScrollBar {}
              }


           Pane {
                      id: pane
                      Layout.fillWidth: true

                      RowLayout {
                          width: parent.width

                          TextArea {
                              id: messageField
                              Layout.fillWidth: true
                              placeholderText: qsTr("Compose message")
                              wrapMode: TextArea.Wrap
                          }

                          Button {
                             id: sendButton
                             text: qsTr("Send")
                             enabled: messageField.length > 0
                             onClicked: {
                                 chatDetailViewModel.sendMessageButtonClicked(messageField.text);
                                 messageField.text = "";
                             }
                         }
                      }
                  }
       }

    Connections {
        target: chatDetailViewModel
        onMessagesChanged: {
            //chatDetailViewModel.ui_messages = chatDetailViewModel.ui_messages
        }
    }
}

/*

Item {
    id: columnWithRectangle
    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: Style.colourBackground
        Text {
            anchors.centerIn: parent
            text: "Chat Detail View"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboard
        }
    }
}
*/
