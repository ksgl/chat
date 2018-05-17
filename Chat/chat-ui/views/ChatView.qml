import QtQuick 2.9
import components 1.0
import CHAT 1.0
import assets 1.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.3

import QtQuick.Controls 2.3
Item {
    id: conversationPage

    property ChatModel newChatModel: masterController.ui_newChatModel
    property Message newMessage: masterController.ui_newMessage
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
 //-------------------------------------------------------
    ListModel {
        id: sampleMessageModel

        /*ListElement {
            messageText: "Apple"
        }*/
    }
//-----------------------------------------------------


    ColumnLayout {
        anchors.fill: parent

        ListView {
            id:listView
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.margins: pane.leftPadding + messageField.leftPadding
            displayMarginBeginning: 40
            displayMarginEnd: 40
            //verticalLayoutDirection: ListView.BottomToTop
            spacing: 25
            //model: 14
            //model: newChatModel
             model: sampleMessageModel

           /*delegate: Row{
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
                    id: rectForMessage
                    width: 80
                    height: 40
                    color: sentByMe ? "#d9d8e3" : "#8f79b0"
                    radius: 7

                    Label {
                        id:messageLabel
                        anchors.centerIn: parent
                        Text { text: messageText }
                        //text: index
                        /*ItemDelegate {
                            text: model.display
                        }//
                        color: sentByMe ? "black" : "white"
                    }
                }
            }*/
             delegate: Column {
                 readonly property bool sentByMe: index % 2 == 0

                 anchors.right: sentByMe ? parent.right : undefined
                 spacing: 6

                 Row {
                     id: messageRow
                     spacing: 6
                     anchors.right: sentByMe ? parent.right : undefined

                     Image {
                         id: avatar
                         //source: !sentByMe ? "qrc:/" + model.author.replace(" ", "_") + ".png" : ""
                          source: "../images/Albert_Einstein.png"
                          visible: !sentByMe
                     }

                     Rectangle {
                         id: rectForMessage

                         Label {
                             id: messageLabel
                             Text { text: messageText }
                             color: sentByMe ? "black" : "white"
                             anchors.fill: parent
                             anchors.margins: 12
                             wrapMode: Label.Wrap
                             clip: true
                         }

                         width: len + 100
                         height: messageLabel.implicitHeight + 24
                         color: sentByMe ? "#d9d8e3" : "#8f79b0"
                         radius: 7
                     }
                 }

                 Label {
                     id: timestampText
                     text: Qt.formatDateTime("d MMM hh:mm")
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
                    /*onFormButtonClicked: {
                        listView.model.sendMessage(messageField.text)
                        messageField.text = "";
                    }*/

                    /*onFormButtonClicked: {
                        //ChatModel.ui_messages = messageField.text
                       //listView.model.ui_messages = messageField.text
                        newMessage.ui_messageData = messageField.text;
                        newChatModel.addMessage();
                        messageField.text = "";
                        listView.update();
                    }*/
                    onFormButtonClicked: {
                        sampleMessageModel.append({"messageText": messageField.text, "len": messageField.text.length})
                        messageField.text = "";
                        sampleMessageModel.append({"messageText": "Hi!"}) // not here
                    }
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
