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

CoverBackground {
    Label {
        anchors.horizontalCenter: parent.horizontalCenter
        id: spacer1
    }
    Label {
        id: label
        //anchors.centerIn: parent
        width: parent.width - (2 * Theme.paddingLarge)
        anchors.horizontalCenter: parent.horizontalCenter
        text: qsTr("SailGo")
    }
    Label {
        width: parent.width - (2 * Theme.paddingLarge)
        wrapMode: Text.WrapWord
        text: ""
    }
    Image {
        id:goImage
        anchors.centerIn: parent
        source: "/usr/share/icons/hicolor/172x172/apps/harbour-sailgo.png"
    }
    Column {
        id:totals
        anchors.horizontalCenter: parent.horizontalCenter
        anchors {
            bottom: parent.bottom
            bottomMargin:  Theme.paddingLarge
        }

        height: childrenRect.height

        Row {
            spacing: Theme.paddingMedium
            height: childrenRect.height
            anchors {
                margins: Theme.paddingLarge
            }

            Label {
                text: qsTr("Black: ")
                color: Theme.highlightColor
            }
            Label {
                id: swart
                property int count: 0
                text: boardController.blackTotal
            }
            Label {
                text: qsTr("White: ")
                color: Theme.highlightColor
            }
            Label {
                id: whit
                text: boardController.whiteTotal
            }
        }
    }
    CoverActionList {
        id: coverAction

        /*CoverAction {
            iconSource: "image://theme/icon-cover-next"
        }

        CoverAction {
            iconSource: "image://theme/icon-cover-pause"
        }*/
    }
}


