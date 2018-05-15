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
            text: "Friend List View"
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
                Text {
                    text: modelData;
                    color: "black";
                    font.pixelSize: 16;
                }
                width: listView.width - listView.leftMargin - listView.rightMargin
                height: avatar.implicitHeight
                leftPadding: avatar.implicitWidth + 32
                /*Image {
                    id: avatar
                    source: "qrc:/" + modelData.replace(" ", "_") + ".png"
                    //source:"images/loupe.png"
                }*/
             }
            ScrollIndicator.vertical: ScrollIndicator { }
         }
    }

    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_friendListViewContextCommands
    }
}
