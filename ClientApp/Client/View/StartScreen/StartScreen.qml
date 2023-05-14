import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {

    property int swidth: parent.width / 100
    property int sheight: parent.height / 100
    color: parent.color

    Rectangle{
        id: title_box
        anchors.horizontalCenter: parent.horizontalCenter
        y: sheight * 16.1111
        width: swidth * 21.3541
        height: sheight * 6.7592
        color:parent.color
        Text{
            id: title_text
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Little Bombers"
            font.family: "Inter"
            font.pointSize: swidth * 2.15
            color:"#000000"
        }
    }

    Rectangle {
        id: button_box
        anchors.horizontalCenter: parent.horizontalCenter
        y: sheight * 38.7962
        width: swidth * 29.3229
        height: sheight * 29.2592
        color: parent.color

        Button{
            property bool hover: false
            id: button_server_list
            width: parent.width
            height: sheight * 11.2037
            anchors.left: parent.left
            anchors.top: parent.top
            clip: true

            background: Rectangle{

                color: parent.hover ? "#1EAFDD" : "#1A93B9"
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: "Подключиться"
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color:"#FFFFFF"
                }
            }
            onHoveredChanged: {hover = !hover}
            onClicked: {
                window.swapScreen("server_list", "");
                //window.swapScreen("game_screen");
            }
        }
        Button{
            property bool hover: false
            id: button_exit
            width: parent.width
            height: sheight * 11.2037

            anchors.left: parent.left
            anchors.bottom: parent.bottom
            clip: true

            background: Rectangle{
                color: parent.hover ? "#1EAFDD" : "#1A93B9"
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter

                    text: "Выйти"
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color:"#FFFFFF"
                }

            }
            onHoveredChanged: {hover = !hover}
            onClicked: {window.close()}
        }

    }
}
