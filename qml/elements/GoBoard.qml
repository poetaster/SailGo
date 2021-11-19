import QtQuick 2.2

Item {
    id: board
    property int boardSize: 13

    property bool hoverEnabled: false

    Grid {
        anchors.centerIn: parent
        anchors.fill: parent

        columns: parent.boardSize

        columnSpacing: -1
        rowSpacing: -1

        Repeater {
            model : boardListModel

            MouseArea {
                id: area

                width: board.width / boardSize
                height: board.height / boardSize

                hoverEnabled: board.hoverEnabled

                onClicked: {
                    boardController.playMove(index);
                }


                GoSquare {
                    anchors.centerIn: parent
                    anchors.fill: parent

                    state: squareState
                    //onStateChanged: console.debug('squareState: ' + pieceState);

                    GoPiece {
                        id: hoverPiece

                        anchors.fill: parent
                        state: area.containsMouse ? boardController.nextPlayer : "empty"

                        opacity: 0.5
                    }


                    GoPiece {
                        anchors.centerIn: parent
                        width: parent.width
                        height: width

                        state: pieceState
                       // onStateChanged: console.debug('pieceState: ' + pieceState);
                    }
                }
            }
        }
    }

    Image {
        z: -1
        source: "images/board.svg"

        sourceSize.width: 500
        sourceSize.height: 500

        anchors.centerIn: parent
        anchors.fill: parent
    }
}
