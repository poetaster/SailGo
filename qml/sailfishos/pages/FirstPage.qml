/*
  Copyright (C) 2013 Jolla Ltd.
  Contact: Thomas Perl <thomas.perl@jollamobile.com>
  All rights reserved.

  You may use this file under the terms of BSD license as follows:

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Jolla Ltd nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR
  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import "../../elements"

Page {
    id: page

    property var model: boardListModel

    SilicaFlickable {
        id: flickable

        anchors.fill: parent
        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: {
                    pageStack.push(Qt.resolvedUrl("About.qml"),{});
                }
            }
            MenuItem {
                text: qsTr("New game")
                onClicked: {
                    boardController.resetBoard();
                }
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentWidth: boardContainer.width;
        contentHeight: boardContainer.height

        PageHeader {
            id: header
            title: qsTr("SailGo")
        }


        PinchArea {
            z:10
            id: pinchArea

            property real minScale: 1.0
            property real maxScale: 3.0

            anchors.fill: parent

            enabled: true;
            pinch.target: board
            pinch.minimumScale: minScale * 0.5 // This is to create "bounce back effect"
            pinch.maximumScale: maxScale * 1.5 // when over zoomed

            Item {
                id: boardContainer

                width: Math.max(board.width * board.scale, flickable.width)
                height: Math.max(board.height * board.scale, flickable.height)

                GoBoard {
                    id: board

                    property real prevScale

                    anchors.centerIn: parent

                    width: page.width < page.height ? page.width : page.height
                    height: width

                    onScaleChanged: {
                        if ((width * scale) > flickable.width) {
                            var xoff = (flickable.width / 2 + flickable.contentX) * scale / prevScale;
                            flickable.contentX = xoff - flickable.width / 2
                        }
                        if ((height * scale) > flickable.height) {
                            var yoff = (flickable.height / 2 + flickable.contentY) * scale / prevScale;
                            flickable.contentY = yoff - flickable.height / 2
                        }
                        prevScale = scale
                    }
                }

            }
        }
    }
}


