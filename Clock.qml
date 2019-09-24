import QtQuick 2.0

Item {
    id: id_root

    property color color: "white"

    property int minutes: currentDate.getMinutes()
    property int seconds: currentDate.getSeconds()
    property var currentDate: new Date()

    Timer {
        id: timer
        repeat: true
        interval: 1000
        running: true

        onTriggered: id_root.currentDate = new Date()
    }

    Rectangle {
        id: id_plate

        anchors.centerIn: parent
        height: Math.min(id_root.width, id_root.height)
        width: height
        radius: width/2
        color: id_root.color
        border.color: "black"
        border.width: 4

        Repeater {
            model: 4

            Item {
                id: hourContainer

                property int hour: index * 90
                height: id_plate.height/2
                transformOrigin: Item.Bottom
                rotation: index * 90
                x: id_plate.width/2
                y: 0

                Rectangle {
                    height: id_plate.height*0.1
                    width: height/3
                    color: "black"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: -5
                }

                Text {
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                    }
                    x: 0
                    y: id_plate.height*0.11
                    rotation: 360 - index * 90
                    text: hourContainer.hour
                    font.pixelSize: id_plate.height*0.1
                    font.family: "Sans"
                }
            }
        }
    }

    Rectangle {
        id: id_center
        width: 32
        height: 32

        anchors.centerIn: parent
        color: "black"
        radius: 16
    }

    MinuteNeedle {
        anchors {
            top: id_plate.top
            bottom: id_plate.bottom
            horizontalCenter: parent.horizontalCenter
        }
        value: backendData.azimut
    }

}

/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
