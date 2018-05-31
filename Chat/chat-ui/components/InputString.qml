import QtQuick 2.9
import assets 1.0

Item {
    property alias description : textLabel.text
    property alias inputText : textValue.text

    height: width > textLabel.width + textValue.width ? Style.inputStringHeight : Style.inputStringHeight * 2

    Row {
        anchors.fill: parent

        Rectangle {
            width: Style.inputStringLabelWidht
            height: Style.inputStringHeight
            color: Style.colourBackground

            Text {
                id: textLabel
                anchors {
                    fill: parent
                }
                text: ""
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }

        Rectangle {
            id: background
            width: Style.inputStringWidht
            radius: 10
            height: Style.inputStringHeight
            color: Style.inputStringBackGroundClor
            border {
                width: 1
                color: Style.inputStringBorderColor
            }
            TextInput {
                id: textValue
                anchors {
                    fill: parent
                    margins: Style.inputStringHeight / 4
                }
                text: ""
                color: Style.colourDataControlsFont
                font.pixelSize: Style.pixelSizeDataControls
                verticalAlignment: Qt.AlignVCenter
            }
        }
    }
}
