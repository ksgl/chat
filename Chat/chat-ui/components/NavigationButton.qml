import QtQuick 2.5
import assets 1.0

Item {
    property alias image: iconImage.source
    property alias iconCharacter: textIcon.text
    property alias description: textDescription.text
    property color hoverColour: Style.colourNavigationBarBackground
    signal navigationButtonClicked()

    width: parent.width
    height: Style.heightNavigationButton

    Rectangle {
        id: background
        anchors.fill: parent
        color: Style.colourNavigationBarBackground

        states: [
            State {
                name: "hover"
                PropertyChanges {
                    target: background
                    color: hoverColour
                }
            }
        ]

        Row {
            Rectangle {
                id: imgContainer
                width: Style.widthNavigationButtonIcon
                height: Style.widthNavigationButtonIcon
                color: "transparent"

                Image {
                    id:iconImage
                    source: ""
                    width: 50
                    height: 50
                    anchors.centerIn: parent
                }

            }

            Text {
                id: textIcon
                width: Style.widthNavigationButtonIcon - 50
                height: Style.heightNavigationButtonIcon
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font {
                    family: Style.fontAwesome
                    pixelSize: Style.pixelSizeNavigationBarIcon
                }
                color: Style.colourNavigationBarFont
                text: "\uf11a"
            }

            Text {
                id: textDescription
                verticalAlignment: Text.AlignVCenter
                width: Style.widthNavigationButtonDescription
                height: Style.heightNavigationButtonDescription
                color: Style.colourNavigationBarFont
                font.pixelSize: Style.pixelSizeNavigationBarText
                text: "SET ME!!"
            }
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            hoverEnabled: true
            onEntered: background.state = "hover"
            onExited: background.state = ""
            onClicked: navigationButtonClicked()
        }

    }


}
