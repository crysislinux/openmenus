// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import QtQuick 1.0

Rectangle {
    id: button
//    property color buttonColor: "lightblue"
    property string onPressedImage: ""
    property string image: ""
    width: 70; height: 20

    MouseArea{
        id: buttonMouseArea

        anchors.fill: parent

        onClicked: buttonClick()
    }

    signal buttonClick()


    Image {
        id: image1
        anchors.fill: parent
        source: buttonMouseArea.pressed ? onPressedImage:image
    }
}
