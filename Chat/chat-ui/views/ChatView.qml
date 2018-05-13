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
            anchors.centerIn: parent
            text: "Chat Detail View"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboard
        }

        Rectangle {
           id: textAreaContainer

           //x: smallLeftBar.width + bigLeftBar.width + 20
           x:  Style.widthNavigationBarCollapsed - 20
           y: parent.height-90
           width: parent.width - 200
           height: 70
           color: "#d8d8eb"
           border.width: 1
           border.color: "grey"
           radius: 10

           TextArea {
                id:textarea

                placeholderText: qsTr("Enter text")
                focus: true
                width: textAreaContainer.width
                font.family: "Arial"
                font.pixelSize: 14
                textFormat: TextEdit.PlainText
                clip: true
                selectByMouse: true
                wrapMode: TextEdit.Wrap
                height: 70
            }
       }
        FormButton {
            id: sendButton
            iconCharacter: ""
            description: qsTr("Send")
            width: 70
            height: 25
            x: parent.width - 100
            y: parent.height - 70
        }
    }

    CommandBar {
        id: commandBar
        //commandList: masterController.ui_commandController.ui_chatListViewContextCommands
    }
}
