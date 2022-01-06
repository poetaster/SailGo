import QtQuick 2.6
import Sailfish.Silica 1.0

Page {
    id: page

    SilicaFlickable {
        id: flickable
        anchors.fill: parent
        contentHeight: column.height

        VerticalScrollDecorator { flickable: flickable }

        Column {
            id: column

            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - (2 * Theme.paddingLarge)
            spacing: Theme.paddingLarge

            PageHeader {
                title: qsTr("SailGo")
            }
            Label {
                width: parent.width - (2 * Theme.paddingLarge)
                wrapMode: Text.WrapWord
                text: ""
            }
            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                linkColor: "#ffffff"
                text: "<a href=\"https://github.com/LouJo/SailGo\">LouJo</a> \n"  +
                                "\n ©2015 Louis-Joseph Fournier \n"
                color: Theme.primaryColor
                wrapMode: TextEdit.WordWrap
                onLinkActivated: {
                    Qt.openUrlExternally(link)
                }
            }
            Label {
                width: parent.width - (2 * Theme.paddingLarge)
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                wrapMode: Text.WrapWord
                text: " ©2021 Mark Washeim \n\n" + qsTr("GPLv2 license.")
                color: Theme.primaryColor
            }
            Label {
                width: parent.width - (2 * Theme.paddingLarge)
                wrapMode: Text.WrapWord
                text: ""
            }
            Label {
                width: parent.width
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: Theme.primaryColor
                linkColor: "#ffffff"
                wrapMode: TextEdit.WordWrap
                //font.pixelSize: units.fx("small")
                text: "<a href=\"https://github.com/poetaster/harbour-sailgo\">Source: github</a>"
                onLinkActivated: {
                    Qt.openUrlExternally(link)
                }
            }

        } // Column
    }
}






