// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle{
    id: iconView
    color: "blue"
    Connections {
            target: sizeData
            onSizeChanged: {
                iconView.width = width
                iconView.height = height
            }
    }

    GridView{
        anchors.fill: parent
        anchors.margins: 20
        model: orderModel
        cellWidth: (parent.width-2)/4; cellHeight: cellWidth; width: parent.width; height: parent.height
        delegate: Column {
            Rectangle{
                width: 60
                height: 60
                color: "red"
            }

            Text{
                text: name
            }
        }

    }
}
