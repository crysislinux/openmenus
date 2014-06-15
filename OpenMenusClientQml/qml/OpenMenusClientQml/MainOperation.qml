// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
    id: operationBox
    width: 80; height: 240
    color: "#D3D3D3"
    property int totalNum: viewPort.totalNum
    property real totalPrice: viewPort.totalPrice
    signal orderFormClicked();
    signal submitClicked();
    Image{
        id: mainButtonImage
        anchors.topMargin: 0
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        source: "mainButton.png"
    }
    Button {
        id: orderFormButton
        radius: 3
        anchors.left: mainButtonImage.right
        anchors.leftMargin: -76
        anchors.verticalCenter: mainButtonImage.verticalCenter
        width: 35
        height: 16
        image: "orderForm.png"
        onPressedImage: "orderForm_pressed.png"
        onButtonClick: orderFormClicked()
    }
    Button {
        id: submitButton
        width: 35
        height: 16
        radius: 3
        anchors.left: orderFormButton.right
        anchors.leftMargin: 2
        anchors.verticalCenter: mainButtonImage.verticalCenter
        image: "submit.png"
        onPressedImage: "submit_pressed.png"
        onButtonClick: {
            console.log("submitButton clicked" )
            submit()
        }
    }
    Image{
        id: menuLabel
        anchors.top: mainButtonImage.bottom
        anchors.topMargin: 4
        anchors.left:mainButtonImage.left
        anchors.leftMargin: 8
        source: "menulabel.png"
    }
    Button {
        id: helpButton
        radius: 5
        anchors.top: menuLabel.bottom
        anchors.horizontalCenter: mainButtonImage.horizontalCenter
        image: "help.png"
        onPressedImage: "help_pressed.png"
        onButtonClick: console.log("helpButton clicked" )
    }
    Button {
        id: payButton
        anchors.top: helpButton.bottom
        anchors.horizontalCenter: helpButton.horizontalCenter
        image: "pay.png"
        onPressedImage: "pay_pressed.png"
        onButtonClick: console.log("payButton clicked" )
    }
    Button {
        id: mostOrderedButton
        anchors.top: payButton.bottom
        anchors.horizontalCenter: payButton.horizontalCenter
        image: "mostOrdered.png"
        onPressedImage: "mostOrdered_pressed.png"
        onButtonClick: console.log("mostOrderedButton clicked" )
    }
    Button {
        id: specialButton
        anchors.top: mostOrderedButton.bottom
        anchors.horizontalCenter: mostOrderedButton.horizontalCenter
        image: "special.png"
        onPressedImage: "special_pressed.png"
        onButtonClick: console.log("specialButton clicked" )
    }

    Button {
        id: fullscreenButton
        radius: 5
        anchors.top: specialButton.bottom
        anchors.left: specialButton.left
        image: "fullscreen.png"
        onPressedImage: "fullscreen_pressed.png"
        onButtonClick: console.log("fullscreenButton clicked" )
    }

    Image{
        id: menuLabel1
        anchors.top: fullscreenButton.bottom
        anchors.topMargin: 4
        anchors.left:mainButtonImage.left
        anchors.leftMargin: 8
        source: "menulabel1.png"
    }
    Button {
        id: problemButton
        radius: 5
        anchors.top: menuLabel1.bottom
        anchors.left: specialButton.left
        image: "problem.png"
        onPressedImage: "problem_pressed.png"
        onButtonClick: console.log("problemButton clicked" )
    }
    Button {
        id: adviceButton
        radius: 0
        anchors.top: problemButton.bottom
        anchors.left: specialButton.left
        image: "advice.png"
        onPressedImage: "advice_pressed.png"
        onButtonClick: console.log("adviceButton clicked" )
    }
    Button {
        id: loginButton
        radius: 5
        anchors.top: adviceButton.bottom
        anchors.left: specialButton.left
        image: "login.png"
        onPressedImage: "login_pressed.png"
        onButtonClick: console.log("loginButton clicked" )
    }
    Text{
        id: _totalNum
        anchors.top: loginButton.bottom
        anchors.topMargin: 3
        anchors.left: specialButton.left
        font.pixelSize: 11
        text: "总数: "+ new Number(totalNum)
    }
    Text{
        id: _totalPrice
        anchors.top: _totalNum.bottom
        anchors.topMargin: 1
        anchors.left: specialButton.left
        font.pixelSize: 11
        text: "总价: "+ myModel.number(totalPrice)
    }
}
