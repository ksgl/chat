import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

import "qrc:/components" as MyComponents

Rectangle
{
    id: smallLeftBar
    width: 50
    height: parent.height
    color:"#544b82"
//----------------SearchMenuIcon--------------------
    MyComponents.IconButton {
        id: searchMenuIcon
        y:200
    }
//-----------------MessageMenuIcon------------------
    MyComponents.IconButton {
        id: messageMenuIcon
        y:260

        style: ButtonStyle {
          background: Rectangle {
             color:  messageMenuIcon.pressed ? "#b4b4d9" : "#544b82";
          }

          label: Image {
              source: "images/message.png"
              fillMode: Image.PreserveAspectFit  // ensure it fits
          }
        }
    }
//-----------------SettingsMenuIcon----------------------------
    MyComponents.IconButton {
        id: settingsMenuIcon
        y:320

        style: ButtonStyle {
          background: Rectangle {
             color: settingsMenuIcon.pressed ? "#b4b4d9" : "#544b82";
          }

          label: Image {
              source: "images/settings.png"
              fillMode: Image.PreserveAspectFit  // ensure it fits
          }
        }
    }
//------------------------------------------------------------
}
