// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Flickable {
    property int index
    property string name
    property real price
    property string description
    property string images
    property int count
    width: parent.width; height: parent.height

    contentWidth: parent.width; contentHeight: getHeight()
    function getHeight(){
        return _information.height+_description.height+_images.height+15
    }
    Rectangle{
        anchors.top: parent.top
        anchors.topMargin: 5
        width: parent.width
        height: _image.height
        id: _information
        color: "#F5F5F5"
//        color: "red"


        Image{
            id: _image
            anchors.left: parent.left
            width: 32; height: 47;
            function getMainImage(){
                if(images.length<1){
                    return "noimage.jpg"
                }
                else
                    return "http://127.0.0.1:8080/"+images.split(";", 1)
            }
            source: getMainImage()
        }

            Text {
                width: 110
                anchors.left: _image.right
                anchors.leftMargin: 0
                anchors.top: _image.top
                id: _name
                text: name
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: 20
                font.bold: true
                elide: Text.ElideRight
                maximumLineCount: 1
                wrapMode: Text.WrapAnywhere
            }
            Text {
                anchors.horizontalCenter: _name.horizontalCenter
                anchors.verticalCenter: increaseButton.verticalCenter
                id: _unitPrice
                text: myModel.number(price)+"$"
                font.pixelSize: 15
                font.bold: true
                color: "red"
            }

            Text{
                anchors.right: backButton.left
                anchors.rightMargin: 13
                anchors.verticalCenter: _name.verticalCenter
                font.pixelSize: 11
                function getCountText(){
                    return "已点数: "+ myModel.number(count)
                }

                text: getCountText()
            }



        Rectangle{
            id: backButton
            width: _image.width
            height: _image.height - 5
            anchors.bottom: _image.bottom
            anchors.bottomMargin: 4
            anchors.right: parent.right
            anchors.rightMargin: 4
            radius: 3
            smooth: true
            border { width: 1; color: Qt.darker(activePalette.button) }
            color: activePalette.button
            SystemPalette { id: activePalette }
            gradient: Gradient {
                     GradientStop {
                         position: 0.0
                         color: {
                             if (mouseArea.pressed)
                                 return activePalette.dark
                             else
                                 return activePalette.light
                         }
                     }
                     GradientStop { position: 1.0; color: activePalette.button }
                 }
            Text{
                text: "Back"
                smooth: true
                anchors.centerIn: parent
            }

            MouseArea{
                id: mouseArea
                anchors.fill: parent
                onClicked: {
                    viewPort.inMenuView = viewPort.lastView
                }
            }
        }

        Button{
            id: decreaseButton
            image: "decrease.png"
            onPressedImage: "decrease_pressed.png"
            width: 20; height: 15
            anchors.bottom: _image.bottom
            anchors.bottomMargin: 4
            anchors.right: backButton.left
            anchors.rightMargin: 16
            radius: 3
            onButtonClick: {
                console.log("decreaseButton pressed-index:" + new Number(index))
                count = myModel.getCount(index)
                if( count > 0){
                    count = count - 1
                    myModel.setCount(index, count)
                    viewPort.totalNum --
                    viewPort.totalPrice -= price
                }
            }
        }

        Button{
            id: increaseButton
            image: "increase.png"
            onPressedImage: "increase_pressed.png"
            width: 20; height: 15
            anchors.bottom: _image.bottom
            anchors.bottomMargin: 4
            anchors.right: decreaseButton.left
            anchors.rightMargin: 4
            radius: 3
            onButtonClick: {
                console.log("increaseButton pressed-index:" + new Number(index))
                count = count + 1
                myModel.setCount(index, count)
                viewPort.totalNum ++;
                viewPort.totalPrice += price
            }
        }


       Text {
            id: _description
            width: parent.width - 8
            anchors.top: _image.bottom
            anchors.topMargin: 12
            anchors.left: parent.left
            anchors.leftMargin: 4
            text: description
            font.pixelSize: 10
            wrapMode: Text.WrapAnywhere
       }
       Item {
           id: _images
            width: parent.width - 8
            height: 96
            anchors.top: _description.bottom
            anchors.topMargin: 6
            anchors.left: parent.left
            anchors.leftMargin: 4

            Component {
                id: myDelegate
                Image{
                    width: 65; height: 96
                    source: __image
                }

            }

            ListView {
                anchors.fill: parent
                orientation: ListView.Horizontal
                function createModel(){
                    var elements = new Array()
                    elements = images.split(";")
                    var tmp = ""
                    for(var i=0;i<elements.length-1;i++){
                        tmp += "ListElement { __image: \"http://127.0.0.1:8080/"+elements[i] + "\"}  "
                    }
                    tmp += "}"
                    return Qt.createQmlObject("import QtQuick 1.1; ListModel { " + tmp,_images, "dynamicSnippet1");
                }
                model:createModel()

                delegate: myDelegate
                spacing: 5
            }
        }
    }
}
