import QtQuick 2.9
import assets 1.0

Item {
    property alias textValue: label.text
    //property alias number: Style.loginFieldPositionY

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
        //x: parent.width / 2
        y: Style.loginFieldPositionY
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
