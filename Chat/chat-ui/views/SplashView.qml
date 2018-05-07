import QtQuick 2.9
import assets 1.0

Column {
    id: columnWithRectangle

    Rectangle {
        id: rectangle
        anchors.fill: parent
        color: Style.colourBackground
        Text {
            anchors.centerIn: parent
            text: "Splash View"
            color: Style.colourDashboardFont
            font.pixelSize: Style.pixelSizeDashboard
        }
    }
}
