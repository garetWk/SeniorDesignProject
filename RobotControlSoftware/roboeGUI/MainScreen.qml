import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import QtLocation 5.4
import QtPositioning 5.4

Rectangle {
    Layout.fillHeight: true
    Layout.fillWidth: true
    anchors.fill: parent
    visible: true

    property alias button3: button3
    property alias button2: button2
    property alias button1: button1
    property alias mainItem: mainItem


    Item {
        id: mainItem
        Layout.fillHeight: false
        Layout.fillWidth: false
        anchors.bottom: parent.bottom
        anchors.fill: parent

        Text {
            id: textArea1
            text: "socket information TBD"
            font.pointSize: 30
            font.family: "Verdana"
            textFormat: Text.PlainText
            anchors.bottom: row1.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottomMargin: 50
            anchors.centerIn: parent
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


    }

}

