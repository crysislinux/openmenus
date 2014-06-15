// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: menuTable
    width: 240
    height: 240
    color: "#F5F5F5"

    Component{
        id: menuListDelegate

        Rectangle{
            width: parent.width;
            height: 96
            border.width: 0
            border.color: "#D3D3D3"
            color: "#F5F5F5"
            function menuDetailClicked(){
                menuDetail.index = menuIndex
                menuDetail.name = name
                menuDetail.price = unitPrice
                menuDetail.description = description
                menuDetail.images = image
                menuDetail.count = count
            }

            Image{
                id: _image
                anchors.left: parent.left
                width: 65; height: 94;
                property string imagePath: image
                source: {
                    if(imagePath.length<1)
                        source = "noimage.jpg"
                    else
                        source = "http://127.0.0.1:8080/"+imagePath.split(";", 1)
                }
            }
            Column{
                id: information
                anchors.left: _image.right
                anchors.leftMargin: 10
                anchors.top: parent.top
                anchors.topMargin: 3
                spacing: 4
                Text {
                    id: _name
                    text: name
                    font.pixelSize: 20
                    font.bold: true
                    elide: Text.ElideRight
                    maximumLineCount: 2
                }
                Text {
                    id: _unitPrice
                    text: myModel.number(unitPrice)+"$"
                    font.pixelSize: 15
                    font.bold: true
                    color: "red"
                }
                Text {
                    id: _description
                    width: 160
                    /*
                    text: {
                        if(description.length>30){
                            text = description.slice(0,30)+"..."
                        }else{
                            text = description
                        }
                    }
                    */
                    text: description
                    elide: Text.ElideRight
                    maximumLineCount: 2
                    font.pixelSize: 10
                    wrapMode: Text.WrapAnywhere
                }
            }
            Text{
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 3
                anchors.left: _image.right
                anchors.leftMargin: 10
                font.pixelSize: 11
                text: "已点数: "+ myModel.number(count)
            }
            Button{
                id: decreaseButton
                image: "decrease.png"
                onPressedImage: "decrease_pressed.png"
                width: 20; height: 15
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 2
                anchors.right: parent.right
                anchors.rightMargin: 4
                radius: 3
                onButtonClick: {
                    console.log("decreaseButton pressed-index:" + new Number(index))
                    if(count > 0){
                        myModel.setCount(menuIndex, count-1)
                        viewPort.totalNum --
                        viewPort.totalPrice -= unitPrice
                    }
                }
            }

            Button{
                id: increaseButton
                image: "increase.png"
                onPressedImage: "increase_pressed.png"
                width: 20; height: 15
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 2
                anchors.right: decreaseButton.left
                anchors.rightMargin: 4
                radius: 3
                onButtonClick: {
                    console.log("increaseButton pressed-index:" + new Number(index))
                    myModel.setCount(menuIndex, count+1)
//                    myModel.setCount(ListView.view.model)
                    viewPort.totalNum ++;
                    viewPort.totalPrice += unitPrice
                }
            }

            Button{
                image: "detail.png"
                onPressedImage: "detail_pressed.png"
                width: 20; height: 15
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 2
                anchors.right: increaseButton.left
                anchors.rightMargin: 4
                radius: 3
                onButtonClick: {
                    console.log("detailButton pressed-index:" + new Number(index))
                    menuDetailClicked()
                    viewPort.lastView = viewPort.inMenuView
                    viewPort.inMenuView = 2
                    console.log(menuDetail.images)
                }
            }
            Rectangle{
                anchors.bottom: parent.bottom
                width: parent.width
                height:1
                color: "#D3D3D3"
            }
        }
    }

    ListView {
        id: menuListView
        model: myModel
        delegate: menuListDelegate
        width: parent.width
        height: parent.height
    }
}
