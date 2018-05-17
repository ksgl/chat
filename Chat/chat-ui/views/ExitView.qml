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
            anchors.centerIn: parent
            text: "Do you want to exit?"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboard
        }
    }
    CommandBar {
        id: commandBar
        commandList: masterController.ui_commandController.ui_exitViewContextCommands
    }
}
