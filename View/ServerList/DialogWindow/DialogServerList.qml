import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {

    property string color_header_box: "#0066A5";
    property string color_header_text: "#FFFFFF";
    property int header_text_size: width * 0.041;

    property string color_content_box: "#EFEFEF";
    property string color_content_text: "#000000";
    property int content_text_size: width * 0.041;

    property string color_footer_box: "#0066A5";
    property string color_footer_text: "#FFFFFF";
    property string color_footer_inactive_button: "#1A93B9";
    property string color_footer_active_button: "#1EAFDD";
    property int footer_text_size: width * 0.041;

    signal clickOk()

    header: Rectangle{
        width: parent.width
        height: parent.height * 0.081018
        color: color_header_box
        Text{
            anchors.fill: parent
            color: color_header_text
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
            clip: true

            font.family: "Inter"
            font.pointSize: header_text_size
            text: "Внимание"
        }
    }
    contentItem: Rectangle{
        width: parent.width
        height: parent.height * 0.740742
        color: color_content_box
        Text{
            width: parent.width
            height: parent.height
            color: color_content_text
            verticalAlignment: TextInput.AlignVCenter
            horizontalAlignment: TextInput.AlignHCenter
            clip: true

            font.family: "Inter"
            font.pointSize: content_text_size
            text: "<p>Следующие поля <br/>должны быть заполнены: <br/>
                        <ul>
                            <li>IP</li>
                            <li>Порт</li>
                            <li>Логин</li>
                            <li>Пароль</li>
                        </ul>
                    </p>"
        }
    }
    footer: Rectangle{
        width: parent.width
        height: parent.height * 0.17824
        color: color_footer_box
        Button{
            property bool hover: false

            width: parent.width * 0.375
            height: parent.height * 0.64935
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter

            background: Rectangle{
                color: parent.hover ? color_footer_active_button : color_footer_inactive_button
                Text{
                    anchors.fill: parent
                    text: "Ok"
                    font.family: "Inter"
                    font.pointSize: footer_text_size
                    verticalAlignment: TextInput.AlignVCenter
                    horizontalAlignment: TextInput.AlignHCenter
                    color: color_footer_text
                }
            }
            onHoveredChanged: {hover = !hover}
            onClicked: {
                clickOk()
            }
        }
    }
    padding: 0
}
