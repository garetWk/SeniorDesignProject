import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtLocation 5.4
import QtPositioning 5.4

Item {
    id: item2
    anchors.fill: parent
    Layout.fillHeight: true
    Layout.fillWidth: true
    visible: false

    property alias button3: button3
    property alias button2: button2
    property alias button1: button1
    property alias sliderVertical1: sliderVertical1
    property alias text1: text1
    property alias text2: text2
    property alias text3: text3
    property alias text4: text4
    property alias sliderHorizontal1: sliderHorizontal1
    property alias sliderHorizontal2: sliderHorizontal2
    property alias sliderHorizontal3: sliderHorizontal3

    Slider {
        id: sliderVertical1
        maximumValue: 10
        minimumValue: 0
        stepSize: 1
        value: 0
        tickmarksEnabled: true
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
        text: qsTr("0/10")
        font.pixelSize: 50
    }





    /*TextField {
        id: textField1
        anchors.centerIn: parent
        text: "Screen2"
        font.pointSize: 14
        placeholderText: qsTr("Text Field")
    }*/

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

    Slider {
        id: sliderHorizontal1
        value: 90

        anchors.top: text1.bottom
        anchors.left: sliderVertical1.right
        anchors.right: parent.right
        anchors.margins: 15

        stepSize: 10
        maximumValue: 180
        Layout.fillHeight: false
        Layout.fillWidth: true
    }

    Slider {
        id: sliderHorizontal2

        anchors.top: text2.bottom
        anchors.left: sliderVertical1.right
        anchors.right: parent.right
        anchors.margins: 15

        stepSize: 5
        value: 0
        minimumValue: 0
        maximumValue: 243
        Layout.fillHeight: false
        Layout.fillWidth: true
    }

    Text {
        id: text2

        anchors.top: sliderHorizontal1.bottom
        anchors.horizontalCenter: sliderHorizontal1.horizontalCenter
        anchors.margins: 15

        text: qsTr("90")
        font.pixelSize: 50
    }

    Text {
        id: text3

        anchors.top: sliderHorizontal2.bottom
        anchors.horizontalCenter: sliderHorizontal2.horizontalCenter
        anchors.margins: 15

        text: qsTr("0")
        font.pixelSize: 50
    }

    Slider {
        id: sliderHorizontal3
        minimumValue: 0
        value: 0

        anchors.top: text3.bottom
        anchors.left: sliderVertical1.right
        anchors.right: parent.right
        anchors.margins: 15

        stepSize: 10
        maximumValue: 173
        Layout.fillHeight: false
        Layout.fillWidth: true
    }

    Text {
        id: text4

        anchors.top: sliderHorizontal3.bottom
        anchors.horizontalCenter: sliderHorizontal3.horizontalCenter
        anchors.margins: 15

        text: qsTr("0")
        font.pixelSize: 50
    }

}

