// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id:button
    property bool isOff: false
    signal _onClicked()
    signal offClicked()
    anchors.centerIn: parent
    width: 60
    height: 25
    radius: 5
    gradient: Gradient {
             GradientStop { position: 0.0; color: "#D3D3D3" }
             GradientStop { position: 1.0; color: "#F5F5F5" }
    }

    Rectangle{
        id: onButton
        width: parent.width/1.7
        height: parent.height
        anchors.top: parent.top
        anchors.left: parent.left
        radius: parent.radius
        smooth: true
        gradient: Gradient {
                 GradientStop { position: 0.0; color: "#4169E1" }
                 GradientStop { position: 1.0; color: "#6495ED" }
        }
    }

    Rectangle{
        id: offButton
        width: 0
        height: parent.height
        anchors.top: parent.top
        anchors.right: parent.right
        radius: parent.radius
        smooth: true
        gradient: Gradient {
                 GradientStop { position: 0.0; color: "#4169E1" }
                 GradientStop { position: 1.0; color: "#6495ED" }
        }
    }

    Text {
        id: textOn
        text: "ON"
        color: "white"
        anchors.verticalCenter: onButton.verticalCenter
        x: (onButton.width-width)/2
    }
    Text {
        id: textOff
        text: "OFF"
        color: "white"
        anchors.verticalCenter: offButton.verticalCenter
        x: button.width
    }
    states: State {
        when: isOff == true
        PropertyChanges { target: offButton; width: button.width/1.7 }
        PropertyChanges { target: onButton; width: 0 }
        PropertyChanges { target: textOn; x: -textOn.width}
        PropertyChanges { target: textOff; x: (button.width-offButton.width)+(offButton.width-width)/2}
    }
    transitions: Transition {
        NumberAnimation { properties: "width"; duration: 100; easing.type: Easing.Linear }
        NumberAnimation { properties: "x"; duration: 100; easing.type: Easing.Linear }
    }
    MouseArea{
        anchors.fill: parent
        onClicked: {
            if(isOff == true){
                isOff = false
                _onClicked()
            }else{
                isOff = true
                offClicked()
            }
        }
    }
}
