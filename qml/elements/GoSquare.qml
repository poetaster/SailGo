import QtQuick 2.2

Rectangle {
    width: 30
    height: 30

    color: "transparent"
    property color lineColor: "black"

    state: "Normal"

    states: [
        State {
            name: "TopLeft"
        },
        State {
            name: "Top"
        },
        State {
            name: "TopRight"
        },
        State {
            name: "Left"
        },
        State {
            name: "Normal"
        },
        State {
            name: "Right"
        },
        State {
            name: "BottomLeft"
        },
        State {
            name: "Bottom"
        },
        State {
            name: "BottomRight"
        }

    ]

    Rectangle {
        width: parent.width / 2
        height: 2

        color: parent.lineColor
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter

        visible: String(parent.state).search("Right") != -1 ? false : true

    }

    Rectangle {
        width: 2
        height: parent.height / 2

        color: parent.lineColor
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter

        visible: String(parent.state).search("Bottom") != -1 ? false : true
    }

    Rectangle {
        width: parent.width / 2
        height: 2

        color: parent.lineColor
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter

        visible: String(parent.state).search("Left") != -1 ? false : true
    }

    Rectangle {
        width: 2
        height: parent.height / 2

        color: parent.lineColor
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        visible: String(parent.state).search("Top") != -1 ? false : true
    }
}
