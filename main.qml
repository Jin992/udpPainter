import QtQuick 2.11
import QtQuick.Window 2.11
import QtQuick.Controls 1.6
import backend.Data 1.0

Window {
    id: root_window
    visible: true
    width: 320
    height: 340
    title: qsTr("UdpPainter")

    Button {
        id: button
        x: 227
        y: 22
        text: qsTr("Start")
        onClicked: {
            backendData.port =  portValue.text
            backendData.startUdp()
        }
    }

    Rectangle {
        id: portValueFrame
        x: 64
        y: 22
        width: 151
        height: 26
        color: "#00000000"
        border.width: 2

        TextInput {
            id: portValue
            anchors.fill: parent
            font.pixelSize: 15
            text: backendData.port
            anchors.leftMargin: 5
            anchors.topMargin: 5
            font.bold: false
            font.weight: Font.ExtraLight
            font.capitalization: Font.AllUppercase
        }
    }

    Label {
        id: label
        x: 13
        y: 22
        height: 26
        text: qsTr("Port:")
        font.pointSize: 14
    }

    Item {
        Clock {
            id: clock
            x: root_window.width/2 - width/2
            y: root_window.height/2 - height/2.5

            width:  240
            height: 240

            Label {
                id: label2
                x: 209
                y: 240
                text: qsTr("0")
            }
        }
    }

    Label {
        id: azimuthLabel
        x: 8
        y: 314
        text: qsTr("Azimuth:")
    }

    Label {
        id: azimuthValue
        x: 78
        y: 314
        text: backendData.azimut.toFixed(2)
    }

    Label {
        id: label1
        x: 190
        y: 314
        text: qsTr("Errors:")
    }

    Label {
        id: label3
        x: 13
        y: 61
        text: qsTr("Status:")
    }

    Rectangle {
        id: rectangle
        x: 70
        y: 63
        width: 14
        height: 14
        color: backendData.connectionIndicator ? "green" : "#f32b2b"
        radius: 7
    }
}
