import QtQuick 2.9
import components 1.0
import assets 1.0

import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import QtQuick.Controls 2.3

Item {
    id: columnWithRectangle
    Rectangle {
        id: rectangle
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
            text: "Friends List View"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboard
        }

        ListView {
            id: listView
            anchors.fill: parent
            topMargin: welcomeText.anchors.topMargin + 60
            leftMargin: welcomeText.anchors.leftMargin
            bottomMargin: 20
            rightMargin: 10
            spacing: 20

            model: ["Albert Einstein", "Ernest Hemingway", "Hans Gude"]

            delegate: ItemDelegate {
                width: listView.width - listView.leftMargin - listView.rightMargin
                Text {
                    text: modelData
                    //color: "black"
                    font.pixelSize: 16
                    height: avatar.implicitHeight
                    leftPadding: avatar.implicitWidth + 32
                }
                onClicked: {
                    console.log("clicked:", modelData)
                    contentFrame.replace("qrc:/views/ChatView.qml");
                }
                Image {
                    id: avatar
                    source: "../images/" + modelData.replace(" ", "_") + ".png"
                }
             }
            ScrollIndicator.vertical: ScrollIndicator { }
         }
    }

    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_friendListViewContextCommands
    }
}
