import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

//import QtQuick.Controls 2.3

import "qrc:/components" as MyComponents

/*import QtQuick 2.6
import QtQuick.Controls 2.1*/

Window {
    id: window
    visible: true
    width: 900; height: 600
    color: "#f7f6f6"
    title: qsTr("Chat")

    MyComponents.SmallLeftBar { id:smallLeftBar }

    MyComponents.BigLeftBar { id: bigLeftBar }

    Text {
        text: qsTr("Hi there!")
        style: Text.Normal
        font.pointSize: 17
        font.bold: false
        font.family: "Courier"
        anchors.verticalCenterOffset: 1
        anchors.horizontalCenterOffset: 123
        anchors.centerIn: parent
    }

    Rectangle {
        id: topBar
        x: 250
        width: 650
        height: 65
        color: "#d8d8eb"
    }

     Rectangle {
        id: textAreaContainer

        x: smallLeftBar.width + bigLeftBar.width + 20
        y: parent.height-90
        width: parent.width-350
        height: 70
        color: "#d8d8eb"
        border.width: 1
        border.color: "grey"
        radius: 10

        TextArea {
             id:textarea

             //placeholderText: qsTr("Search")
             focus: true
             width: textAreaContainer.width
             //text: qsTr("Text Edit")
             frameVisible: true
             font.family: "Arial"
             font.pixelSize: 12
             textFormat: TextEdit.PlainText
             clip: true
             selectByMouse: true
             wrapMode: TextEdit.Wrap
             height: 70
         }
    }
     MyComponents.ChatButton {
         id: sendButton
         text: qsTr("Send")
         width: 70
         height: 25
         x:parent.width - 75
         y:parent.height-70
     }
//---------------------
}
