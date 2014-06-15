// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: openMenus
    width: 320
    height: 240
    signal submit()
    ViewPort {
        anchors.right: parent.right
        anchors.top: parent.top
        id: viewPort
    }

    MainOperation {
        id: operationBox
        anchors.left: parent.left
        anchors.top: parent.top
        onOrderFormClicked: {
            viewPort.lastView = viewPort.inMenuView
            if (viewPort.inMenuView == 0)
                viewPort.inMenuView = 1
            else
                viewPort.inMenuView = 0
        }
    }

    onSubmit: {
        console.log("submit")
    }
}
