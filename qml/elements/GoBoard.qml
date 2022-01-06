import QtQuick 2.2

Item {
    id: board

    property bool debug: false
    property int boardSize: 13
    property bool hoverEnabled: false

    function getMarkers(index){
        var markers = [42,48,84,120,126]
        if ( markers.indexOf(index) !== -1) {
            if (debug) console.debug('index: ' + index);
            return "black"
        } else {
            return "empty"
        }
    }

    Grid {
        anchors.centerIn: parent
        anchors.fill: parent

        columns: parent.boardSize

        columnSpacing: -1
        rowSpacing: -1

        Repeater {
            model : boardListModel
            property string curentMarker: "empty"

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
                    onStateChanged: {
                        if (debug) console.debug('squareState: ' + pieceState);
                        if (debug) console.debug('index: ' + model.index);
                    }
                    GoPiece {
                        x: parent.width/3 + 2
                        y: parent.width/3 + 2
                        id: marker
                        width:parent.width / 4
                        height:parent.width / 4
                        state: getMarkers(model.index)
                        /*onStateChanged: {
                            var markers = [42,48,133,139]
                            if ( markers.indexOf(model.index) !== -1) {
                                if (debug) console.debug('index: ' + model.index);
                                currentMarker = "black"
                            } else {

                            }

                        }*/

                    }

                    GoPiece {
                        id: hoverPiece
                        anchors.fill: parent
                        opacity: 0.5
                        state: area.containsMouse ? boardController.nextPlayer : "empty"
                    }


                    GoPiece {
                        anchors.centerIn: parent
                        width: parent.width
                        height: width
                        state: pieceState
                        onStateChanged: {
                            if (debug) console.debug('pieceState: ' + pieceState);
                            if (debug) console.debug('index: ' + model.index);
                        }

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
