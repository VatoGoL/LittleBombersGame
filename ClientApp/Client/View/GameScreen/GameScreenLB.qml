import QtQuick 2.15
import QtQuick.Controls 2.15
//import NetManager 1.0

Rectangle {
    id: wrapper
    property int swidth: parent.width / 100
    property int sheight: parent.height / 100
    property string color_title_box: "#109474"
    property string color_vertical_line: "#C4FBE4"
    property string background_game_area: "#D9D9D9"
    property string statistic_text_color: "#FFFFFF"
    //property NetManager net_manager: window.net_manager

    width: parent.width
    height: parent.height
    x: parent.x
    y: parent.y
    color: parent.color

    Rectangle{
        id: title_box
        width: parent.width
        height: sheight * 7.4074
        x: parent.x
        y: parent.y
        color: color_title_box
        //Вертикальные линии
        Rectangle{
            id: vl_1
            width: swidth * 0.2082
            height: parent.height
            x: swidth * 23.6458
            y:parent.y
            z:1
            color: color_vertical_line
        }
        Rectangle{
            id: vl_2
            width: swidth * 0.2082
            height: parent.height
            x: swidth * 50
            y:parent.y
            z:1
            color: color_vertical_line
        }
        Rectangle{
            id: vl_3
            width: swidth * 0.2082
            height: parent.height
            x: swidth * 75.7291
            y:parent.y
            z:1
            color: color_vertical_line
        }

        //Статистика
        Rectangle{
            id: score_box
            anchors.top: title_box.top
            anchors.left: title_box.left
            height: title_box.height
            width: swidth * 23.6458
            color: title_box.color
            Row{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: swidth * 2

                Text{
                    id: score_title
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color: statistic_text_color
                    text: "Очки"
                }
                Text{
                    id: score_value
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color: statistic_text_color
                    text: "0"
                }
            }
        }
        Rectangle{
            id: lives_player_box
            anchors.top: title_box.top
            anchors.left: vl_1.left
            height: title_box.height
            width: swidth * 26.3541
            color: title_box.color
            Row{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: swidth * 2

                Text{
                    id: lives_player_title
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color: statistic_text_color
                    text: "Живых игроков"
                }
                Text{
                    id: lives_player_value
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color: statistic_text_color
                    text: "0"
                }
            }
        }
        Rectangle{
            id: enemy_count_box
            anchors.top: title_box.top
            anchors.left: vl_2.left
            height: title_box.height
            width: swidth * 25.7291
            color: title_box.color
            Row{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: swidth * 2

                Text{
                    id: enemy_count_title
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color: statistic_text_color
                    text: "Врагов"
                }
                Text{
                    id: enemy_count_value
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color: statistic_text_color
                    text: "0"
                }
            }
        }
        Rectangle{
            id: lives_count_box
            anchors.top: title_box.top
            anchors.left: vl_3.left
            height: title_box.height
            width: swidth * 27.2708
            color: title_box.color
            Row{
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: swidth * 2

                Text{
                    id: lives_count_title
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color: statistic_text_color
                    text: "Жизни"
                }
                Text{
                    id: lives_count_value
                    font.family: "Inter"
                    font.pointSize: swidth * 1.5
                    color: statistic_text_color
                    text: "0"
                }
            }
        }
    }

    Rectangle{
        id:game_area
        anchors.top: title_box.bottom
        anchors.horizontalCenter: wrapper.horizontalCenter
        width: swidth * 52.0833
        height: width
        color: background_game_area
    }
}
