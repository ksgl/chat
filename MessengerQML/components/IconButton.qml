import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Button {
  id: leftMenuButton
  text: qsTr("Search")
  width: smallLeftBar.width
  height:smallLeftBar.width
  y:200

  /*function getImagePath(buttonName)
  {
      var path = ""
      if(buttonName == "searchMenuIcon")
          path = "file:///home/vicky/Development/C++ messenger project/loupe.png";
      else if (buttonName == "messageMenuIcon")
          path = "file:///home/vicky/Development/C++ messenger project/message3.png";
      else if (buttonName == "settingsMenuIcon")
          path = "file:///home/vicky/Development/C++ messenger project/settinds2.png";
      return path
  }*/

  style: ButtonStyle {
    background: Rectangle {
      //border.color: "#888"
       color: leftMenuButton.pressed ? "#b4b4d9" : "#544b82";
       //radius:100;
    }
    label: Image {
        source: "images/loupe.png";
        fillMode: Image.PreserveAspectFit  // ensure it fits
    }
  }
}
