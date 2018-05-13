import QtQuick 2.9
import components 1.0
import assets 1.0

Item {
    id: columnWithRectangle
    Rectangle {

        id: rectangle
        anchors.fill: parent
        color: Style.colourBackground
        Text {
            id:welcomeText
            x: parent.width / 3
            y: 100

            text: "Welcome to Messenger!"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboard
        }

        Text {
            x: parent.width / 3
            y: 200

            text: "Login"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboardSmall
        }

        Rectangle {
            id: searchFieldContainer
            x: parent.width / 2
            y: 200
            /*anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 200
            anchors.leftMargin: 300
            anchors.rightMargin: 100*/

            width: 200
            height: 25
            color: "white"
            border.width: 1
            border.color: "grey"
            radius: 10

            TextInput {
                id: textInput1
                x: 10
                y: 3
                width: parent.width - 12
                height: parent.height
                //text: qsTr("Text Input")
                clip: true
                font.pixelSize: 12
            }
        }


        Text {
            x: parent.width / 3
            y: 250

            text: "Password"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboardSmall
        }

        Rectangle {
            id: passwordFieldContainer
            x: parent.width / 2
            y: 250
            /*anchors.left: parent.left
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.topMargin: 200
            anchors.leftMargin: 300
            anchors.rightMargin: 100*/

            width: 200
            height: 25
            color: "white"
            border.width: 1
            border.color: "grey"
            radius: 10

            TextInput {
                id: textInput2
                x: 10
                y: 3
                width: parent.width - 12
                height: parent.height
                //text: qsTr("******")
                clip: true
                font.pixelSize: 12
            }
        }

}
    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_loginViewContextCommands
    }
}
