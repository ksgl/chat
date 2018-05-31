import QtQuick 2.9
import assets 1.0

Item {
    property alias textValue: label.text

    Text {
        id:label
       // x: parent.width / 3
        x:300
        y: Style.loginFieldPositionY

        text: ""
        color: Style.colourDashboardFont
        font.pixelSize: Style.pixelSizeDashboardSmall
    }

    Rectangle {
        id: fieldContainer
        x: 300
        y: Style.loginFieldPositionY

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
            clip: true
            font.pixelSize: 12
        }
    }


}
