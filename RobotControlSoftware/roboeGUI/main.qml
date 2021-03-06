import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtLocation 5.4
import QtPositioning 5.4
import QtSensors 5.0


ApplicationWindow {
    title: qsTr("Main Window")
    width: 400
    height: 640
    visible: true

    MainScreen {
        id: mainScreen
        anchors.fill: parent

        children: [
            Screen1{
                id:screen1
                button1.onClicked: { screen1.visible = false; parent.mainItem.visible = true; screen2.visible = false }
                button2.onClicked: { }
                button3.onClicked: { screen1.visible = false; parent.mainItem.visible = false; screen2.visible = true }

                sliderVertical1.onValueChanged: {                 
                    text1.text = sliderVertical1.value
                    checkBox1.checked ? socket.writeMotorLR(sliderVertical1.value) : socket.writeMotorL(sliderVertical1.value)
                }
                sliderVertical2.onValueChanged: {
                    text2.text = sliderVertical2.value
                    if(!checkBox1.checked)
                    {
                        socket.writeMotorR(sliderVertical2.value)
                    }

                }
                sliderHorizontal1.onValueChanged: {
                    text3.text = sliderHorizontal1.value
                    socket.writeRotation(sliderHorizontal1.value)
                }

                sliderVertical2.value: checkBox1.checked ? sliderVertical1.value : sliderVertical2.value

                accelerometerItem.visible: checkBox2.checked ? true : false
                accel.active: checkBox2.checked ? true : false
                accel.onReadingChanged: {
                    var y = calcPosition((accel.reading.y*50))
                    socket.writeMotorLR(y)
                }

                function calcPosition(value)
                {
                    var nval = Math.floor(value/5) * -5

                    if(nval >= 255)
                        return 255
                    else if(nval <= -255)
                        return -255
                    else if( nval >= 20 )
                        return nval
                    else if( nval <= -20 )
                        return nval
                    else
                        return 0
                }
            },
            Screen2{
                id:screen2
                button1.onClicked: { screen2.visible = false; parent.mainItem.visible = true; screen1.visible = false }
                button2.onClicked: { screen2.visible = false; parent.mainItem.visible = false; screen1.visible = true }
                button3.onClicked: { screen2.visible = true; parent.mainItem.visible = false; screen1.visible = false }

                sliderVertical1.onValueChanged: {
                    text1.text = sliderVertical1.value.toString() + "/10"
                    socket.writeExtend(sliderVertical1.value)
                }
                sliderHorizontal1.onValueChanged: {
                    text2.text = sliderHorizontal1.value
                    socket.writeRotation(sliderHorizontal1.value)
                }
                sliderHorizontal2.onValueChanged: {
                    text3.text = sliderHorizontal2.value
                    socket.writeElevation(sliderHorizontal2.value)
                }
                sliderHorizontal3.onValueChanged: {
                    text4.text = sliderHorizontal3.value
                    socket.writeGrip(sliderHorizontal3.value)
                }
            }
        ]

        button1.onClicked: {  }
        button2.onClicked: { mainItem.visible = false; screen1.visible = true; screen2.visible = false }
        button3.onClicked: { mainItem.visible = false; screen1.visible = false; screen2.visible = true }

        button4.onClicked: { socket.connect(textField1.text,textField2.text);
                             button4.enabled = false;
                             button2.enabled = true;
                             button3.enabled = true  }
    }
}
