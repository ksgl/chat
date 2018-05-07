import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

Button {
  id:myButton
  style: ButtonStyle {
    background: Rectangle {
       border.color: "#888"
       color: myButton.pressed ? "#b4b4d9" : "#d8d8eb";
       radius: 10
    }

    label: Text {
      verticalAlignment: Text.AlignVCenter
      horizontalAlignment: Text.AlignHCenter
      font.family: "Arial"
      font.pointSize: 10
      color: "black"
      text: control.text
    }
  }
}
