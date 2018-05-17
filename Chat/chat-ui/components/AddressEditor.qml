import QtQuick 2.9
import CHAT 1.0
import assets 1.0

Panel {
    property Address address
    property Address temporatyAddress
    property Address addressBindTo: address ? address : temporatyAddress

    contentComponent:
        Column {
            id: column
            spacing: Style.sizeControlSpacing

            StringEditorSingleLine {
                stringDecorator: addressBindTo.ui_building
                anchors {
                    left: parent.left
                    right: parent.right
                }
            }
            StringEditorSingleLine {
                stringDecorator: addressBindTo.ui_street
                anchors {
                    left: parent.left
                    right: parent.right
                }
            }
            StringEditorSingleLine {
                stringDecorator: addressBindTo.ui_city
                anchors {
                    left: parent.left
                    right: parent.right
                }
            }
            StringEditorSingleLine {
                stringDecorator: addressBindTo.ui_postcode
                anchors {
                    left: parent.left
                    right: parent.right
                }
            }
        }
}

