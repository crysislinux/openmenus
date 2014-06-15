// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: viewPort
    width: 240
    height: 240
    color: "#F5F5F5"

    property int inMenuView : 1
    property int lastView : inMenuView
    property int totalNum: 0
    property real totalPrice: 0.0

    Item {
        id: views
        width: parent.width
        anchors.fill: parent

        MenuTable {
            id: menuTable
            width: parent.width; height: parent.height;

        }
        OrderForm {
            id: orderForm
            width: parent.width; height: parent.height; x: -(parent.width * 1.5);
        }
        MenuDetail{
            id: menuDetail
            width: parent.width; height: parent.height; x: -(parent.width * 1.5);
        }

        states: [
            State {
                name: "DetailView"; when: viewPort.inMenuView == 2
                PropertyChanges { target: menuDetail; x: 0 }
                PropertyChanges { target: orderForm; x:  -(parent.width * 1.5)}
                PropertyChanges { target: menuTable; x:  -(parent.width * 1.5)}
            },
            State {
                name: "OrderView"; when: viewPort.inMenuView == 0
                PropertyChanges { target: orderForm; x: 0 }
                PropertyChanges { target: menuTable; x: -(parent.width * 1.5) }
                PropertyChanges { target: menuDetail; x:  -(parent.width * 1.5)}
            },
            State {
                name: "MenuView"; when: viewPort.inMenuView == 1
                PropertyChanges { target: menuTable; x: 0 }
                PropertyChanges { target: orderForm; x:  -(parent.width * 1.5)}
                PropertyChanges { target: menuDetail; x:  -(parent.width * 1.5)}
            }
        ]
        transitions: Transition {
            NumberAnimation { properties: "x"; duration: 300; easing.type: Easing.InOutQuad }
        }
    }

}
