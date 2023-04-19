import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    property string color_text_value: ""
    property string text_title: ""
    property int text_size: 0

    property string color_text_input_back: ""
    property string color_text_input: ""

    property int max_length: 18

    Rectangle{
        id: title_box
        width: parent.width
        height: parent.height/2
        anchors.top: parent.top
        anchors.left: parent.left
        color: parent.color

        Text{
            id: info_title_text
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            text: text_title
            font.family: "Inter"
            font.pointSize: text_size
            color: color_text_value
        }
    }

    Rectangle{
        id: text_input_box
        width: parent.width
        height: parent.height/2
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: color_text_input_back
        TextInput{
            width: parent.width
            height: parent.height
            color: color_text_input
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
            clip: true
            maximumLength: max_length

            font.family: "Inter"
            font.pointSize: text_size
        }
    }
}
