// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    width: 240
    height: 240
    color: "#F5F5F5"
    property bool is: false
    Component{
        id: orderFormDelegate
        Rectangle{
            width: parent.width;
            height: 30
            border.width: 0
            border.color: "#D3D3D3"
            color: {
                if(is == false){
                    color = "#FFFFFF"
                    is = true
                }else{
                    color = "#F5F5F5"
                    is = false
                }
            }
            function menuDetailClicked()  {
                menuDetail.index = index
                menuDetail.name = name
                menuDetail.price = unitPrice
                menuDetail.description = description
                menuDetail.images = image
                menuDetail.count = count
            }


            Row{
                anchors.verticalCenter: parent.verticalCenter
                Rectangle{

                    width: 73
                    height: parent.height
                    Text{
                        width: parent.width
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 11
                        text: name
                        verticalAlignment: Text.AlignVCenter
                        horizontalAlignment: Text.AlignHCenter
                        elide: Text.ElideRight
                        maximumLineCount: 1
                        wrapMode: Text.WrapAnywhere
                    }
                }
                Rectangle{
                    width: 43
                    height: parent.height
                    Text{
                        anchors.centerIn: parent
                        font.pixelSize: 11
                        text: myModel.number(count)
                    }
                }

                Rectangle{
                    width: 43
                    height: parent.height
                    Text {
                        anchors.centerIn: parent
                        font.pixelSize: 11
                        text: myModel.number(unitPrice)
                        elide: Text.ElideRight
                        maximumLineCount: 1
                        wrapMode: Text.WrapAnywhere
                    }
                }
                Rectangle{
                    width: 81
                    height: parent.height
                        Button{
                            anchors.verticalCenter: parent.verticalCenter
                            id: detailButton
                            image: "detail.png"
                            onPressedImage: "detail_pressed.png"
                            width: 20; height: 15
                            anchors.left: parent.left
                            anchors.leftMargin: 6
                            radius: 3
                            onButtonClick: {
                                console.log("detailButton pressed-index:" + new Number(index))
                                menuDetailClicked()
                                viewPort.lastView = viewPort.inMenuView
                                viewPort.inMenuView = 2

                            }
                        }
                        Button{
                            id: increaseButton
                            anchors.verticalCenter: parent.verticalCenter
                            image: "increase.png"
                            onPressedImage: "increase_pressed.png"
                            width: 20; height: 15
                            anchors.left: detailButton.right
                            anchors.leftMargin: 4
                            radius: 3
                            onButtonClick: {
                                console.log("increaseButton pressed-index:" + new Number(index))
//                                countChanged(index)
                                myModel.setCount(menuIndex, count+1)
                                viewPort.totalNum ++
                                viewPort.totalPrice += unitPrice
                            }
                        }
                        Button{
                            id: decreaseButton
                            anchors.verticalCenter: parent.verticalCenter
                            image: "decrease.png"
                            onPressedImage: "decrease_pressed.png"
                            width: 20; height: 15
                            anchors.left: increaseButton.right
                            anchors.leftMargin: 4
                            radius: 3
                            onButtonClick: {
                                console.log("decreaseButton pressed-index:" + new Number(index))
//                                countChanged(index)
                                if(count > 0){
                                    myModel.setCount(menuIndex, count-1)
                                    viewPort.totalNum --
                                    viewPort.totalPrice -= unitPrice
                                }
                            }
                        }

                }
            }
        }
    }

    Rectangle{
        id: header
        width: parent.width
        height: 22
        gradient: Gradient{
            GradientStop { position: 0.0; color: "#F5F5F5"}
            GradientStop { position: 1.0; color: "#D3D3D3"}
        }
        Row{
            anchors.verticalCenter: parent.verticalCenter
            Rectangle{
                width: 73
                height: parent.height
                Text{
                    anchors.centerIn: parent
                    font.pixelSize: 11
                    text: "菜名"                    
                }
            }
            Rectangle{
                width: 43
                height: parent.height
                Text{
                    anchors.centerIn: parent
                    font.pixelSize: 11
                    text: "数量"
                }
            }

            Rectangle{
                width: 43
                height: parent.height
                Text {
                    anchors.centerIn: parent
                    font.pixelSize: 11
                    text: "单价"
                }
            }
            Rectangle{
                width: 81
                height: parent.height
                Text{
                    anchors.centerIn: parent
                    font.pixelSize: 11
                    text: "操作"
                }
            }
        }
    }

    ListView {
        id: orderFormView
        anchors.top: header.bottom
        model: myOrderModel
        width: parent.width
        height: parent.height
        delegate: orderFormDelegate

    }
}
