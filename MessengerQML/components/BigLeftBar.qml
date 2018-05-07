import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Controls 2.3

import "qrc:/components" as MyComponents

Rectangle
{
    id: bigLeftBar
    width:200
    height: parent.height
    color:"#3a344c"
    x: smallLeftBar.width

    Rectangle {
        id: searchFieldContainer
        x: 10
        y: 17
        width: 100
        height: 25
        color: "white"
        border.width: 1
        border.color: "grey"
        radius: 10

        TextInput {
            id: textInput1
            x: 10
            y: 3
            width: 80
            height: 20
            text: qsTr("Text Input")
            clip: true
            font.pixelSize: 12
        }
    }

   MyComponents. ChatButton {
        id: searchButton
        text: qsTr("Search")
        width: 60
        height: 25
        x:122
        y:17
    }

 //-------------------------------------------------------------

   ListView {
       id: listView
       anchors.fill: parent
       topMargin: 60
       leftMargin: 30
       bottomMargin: 20
       rightMargin: 10
       spacing: 20

       model: ["Albert Einstein", "Ernest Hemingway", "Hans Gude"]

       delegate: ItemDelegate {
           Text { text: modelData; color: "white" }
           width: listView.width - listView.leftMargin - listView.rightMargin
           height: avatar.implicitHeight
           leftPadding: avatar.implicitWidth + 32
           /*Image {
               id: avatar
               source: "qrc:/" + modelData.replace(" ", "_") + ".png"
               //source:"images/loupe.png"
           }*/
        }
       //ScrollIndicator.vertical: ScrollIndicator { }
    }
//---------------------------------------------------------------------------

}
