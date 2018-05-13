import QtQuick 2.9
import CHAT 1.0
import assets 1.0

Item {
    property alias iconCharacter: textIcon.text
    property alias description: textDescription.text
    signal formButtonClicked()
    width: Style.widthFormButton
    height: Style.heightFormButton
    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.colorFormButtonBackground
        radius: Style.sizeFormButtonRadius
        border.color: Style.colorFormButtonBorder
        Text {
            id: textIcon
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
                //margins: Style.heightFormButton / 4
            }
            font {
                family: Style.fontAwesome
                pixelSize: Style.pixelSizeFormButtonIcon
            }
            color: Style.colorFormButtonFont
            text: "\uf11a"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        Text {
            id: textDescription
            anchors {
                left: textIcon.left
                bottom: parent.bottom
                top: parent.top
                right: parent.right
            }
            font.pixelSize: Style.pixelSizeFormButtonText
            color: Style.colorFormButtonFont
            text: "SET ME!!"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: formButtonClicked()
        }
        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    //color: Qt.darker(Style.colorFormButtonBackground)
                    color: "#b4b4d9"
                }
            }
        ]
    }
}
