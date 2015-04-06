import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtLocation 5.4
import QtPositioning 5.4
import QtSensors 5.0

Item {
    id: item1
    anchors.fill: parent
    Layout.fillHeight: true
    Layout.fillWidth: true
    visible: false

    property alias button3: button3
    property alias button2: button2
    property alias button1: button1
    property alias sliderVertical1: sliderVertical1
    property alias sliderVertical2: sliderVertical2
    property alias text1: text1
    property alias text2: text2
    property alias checkBox1: checkBox1
    property alias checkBox2: checkBox2
    property alias sliderHorizontal1: sliderHorizontal1
    property alias text3: text3
    property alias accelerometerItem: accelerometerItem
    property alias accel: accel

    Slider {
        id: sliderVertical1
        updateValueWhileDragging: true
        tickmarksEnabled: true
        stepSize: 10
        minimumValue: -250
        maximumValue: 250
        value: 0
        Layout.fillHeight: true
        Layout.fillWidth: false
        anchors.left: parent.left
        anchors.leftMargin: 15
        anchors.bottom: row1.top
        anchors.bottomMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 15
        orientation: Qt.Vertical
    }

    Text {
        id: text1

        anchors.left: sliderVertical1.right
        anchors.leftMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 15

        text: qsTr("0")
        font.pixelSize: 50
        Layout.fillWidth: false
        Layout.fillHeight: false
    }

    Slider {
        id: sliderVertical2
        tickmarksEnabled: true
        stepSize: 10
        minimumValue: -250
        maximumValue: 250
        Layout.fillHeight: true
        Layout.fillWidth: false
        anchors.right: parent.right
        anchors.rightMargin: 15
        anchors.bottom: row1.top
        anchors.bottomMargin: 15
        anchors.top: parent.top
        anchors.topMargin: 15
        orientation: Qt.Vertical
    }

    Text {
        id: text2

        anchors.right: sliderVertical2.left
        //anchors.rightMargin: 15
        anchors.top: parent.top
        //anchors.topMargin: 15

        anchors.margins: 15

        text: qsTr("0")
        font.pixelSize: 50
        Layout.fillWidth: false
        Layout.fillHeight: false
    }

    Slider {
        id: sliderHorizontal1
        value: 90

        anchors.top: checkBox1.bottom
        anchors.right: sliderVertical2.left
        anchors.left: sliderVertical1.right

        anchors.margins: 15


        stepSize: 10
        maximumValue: 180
        orientation: Qt.Horizontal

        //Layout.fillHeight: false
        //Layout.fillWidth: true
    }

    Text {
        id: text3

        anchors.top: sliderHorizontal1.bottom

        anchors.horizontalCenter: sliderHorizontal1.horizontalCenter


        anchors.margins: 15

        Layout.fillHeight: false
        Layout.fillWidth: false

        text: qsTr("90")
        font.pixelSize: 50
    }

    Row {
        id: row1
        Layout.fillWidth: true
        Layout.fillHeight: false
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 50
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 50

        Button {
            id: button1
            text: qsTr("Main")
        }

        Button {
            id: button2
            text: qsTr("Screen1")
        }

        Button {
            id: button3
            text: qsTr("Screen2")
        }
    }

    CheckBox {
        id: checkBox1
        checked: false
        anchors.top: text1.bottom
        anchors.topMargin: 15
        anchors.left: sliderVertical1.right
        anchors.leftMargin: 15
        text: qsTr("Locked")
    }

    CheckBox {
        id: checkBox2
        checked: false
        anchors.top: text3.bottom
        anchors.topMargin: 15
        anchors.left: sliderVertical1.right
        anchors.leftMargin: 15
        text: qsTr("accel")
    }

    Item {
        id: accelerometerItem

        Layout.fillHeight: true
        Layout.fillWidth: true

        anchors.bottom: row1.top
        anchors.left: sliderVertical1.right
        anchors.right: sliderVertical2.left
        anchors.top: checkBox2.bottom

        anchors.margins: 15

        visible: flase

        Accelerometer {
            id: accel
            dataRate: 10
            active: fasle
        }

        Text {
            id: acceltext1
            anchors.bottom: parent.bottom
            anchors.margins: 15

            text: accel.active ? qsTr("z: " + calcPosition((accel.reading.z*50))) : qsTr("not active")
            font.pixelSize: 50
            Layout.fillWidth: false
            Layout.fillHeight: false
        }

        Text {
            id: acceltext2

            anchors.bottom: acceltext1.top
            anchors.margins: 15

            text: accel.active ? qsTr("y: " + calcPosition((accel.reading.y*50))) : qsTr("not active")
            font.pixelSize: 50
            Layout.fillWidth: false
            Layout.fillHeight: false
        }

        Text {
            id: acceltext3

            anchors.bottom: acceltext2.top
            anchors.margins: 15

            Layout.fillHeight: false
            Layout.fillWidth: false

            text: accel.active ? qsTr("x: " + calcPosition((accel.reading.x*50))) : qsTr("not active")
            font.pixelSize: 50
        }
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
}



