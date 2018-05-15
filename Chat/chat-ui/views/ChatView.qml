import QtQuick 2.9
import components 1.0
import assets 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
Item {
    id: conversationPage

    property string inConversationWith

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

    ColumnLayout {
        anchors.fill: parent

        ListView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            verticalLayoutDirection: ListView.BottomToTop
            spacing: 12
            model: 14
            delegate: Row {
                readonly property bool sentByMe: index % 2 == 0

                anchors.right: sentByMe ? parent.right : undefined
                spacing: 6

                Rectangle {
                    id: avatar
                    x:100
                    width: height
                    height: parent.height
                    color: "grey"
                    visible: !sentByMe
                }

                Rectangle {
                    width: 80
                    height: 40
                    color: sentByMe ? "#d9d8e3" : "#8f79b0"
                    radius: 7

                    Label {
                        anchors.centerIn: parent
                        text: index
                        color: sentByMe ? "black" : "white"
                    }
                }
            }

            ScrollBar.vertical: ScrollBar {}

        }

        Pane {
            id: pane
            Layout.fillWidth: true

            RowLayout {
                width:parent.width

                TextArea {
                    id: messageField
                    Layout.fillWidth: true
                    placeholderText: qsTr("Enter text")
                    font.family: "Arial"
                    font.pixelSize: 14
                    textFormat: TextArea.PlainText
                    clip: true
                    selectByMouse: true
                    wrapMode: TextArea.Wrap
                }

                FormButton {
                    id: sendButton
                    iconCharacter: ""
                    description: qsTr("Send")
                    width: 70
                    height: 25
                    enabled: messageField.length > 0
                }


                //StackView.view.push(...) - better way
                FormButton {          //temporary
                    id: backButton
                    description: qsTr("Back")
                    iconCharacter: ""
                    width: 70
                    height: 25
                    x: 30
                    y: 100
                    onFormButtonClicked: contentFrame.replace("qrc:/views/ChatListView.qml")

                }
            }

        }


    }

    CommandBar {
        id: commandBar
        //commandList: masterController.ui_commandController.ui_chatListViewContextCommands
    }
}
