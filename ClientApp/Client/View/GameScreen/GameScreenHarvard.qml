import QtQuick 2.15
import QtQuick.Controls 2.15
import GameHarvard 1.0
import "../FormInput"

Rectangle {
    id: wrapper

    property int const_waiting_player: 1
    property int const_active_stage: 2
    property int const_result_stage: 3

    property int swidth: parent.width / 100
    property int sheight: parent.height / 100
    property string game_login: ""
    property string color_title_box: "#109474"
    property string color_vertical_line: "#C4FBE4"
    property string background_game_area: "#D9D9D9"
    property string statistic_text_color: "#FFFFFF"
    property string color_button_active: "#1EAFDD"
    property string color_button_success: "#25AD95"
    property string color_button_inactive: "#1A93B9"
    property string color_background_card: "#0066A5"
    width: parent.width
    height: parent.height
    x: parent.x
    y: parent.y
    color: parent.color

    onWindowChanged:{
        game_harvard.setNetManager(client_wrapper.getClientManager());
    }
    Component.onCompleted: {
        //game_harvard.setNetManager(client_wrapper.getClientManager());
        game_harvard.setName(wrapper.game_login);
    }

    GameHarvard{
        id: game_harvard

        onKickFromServer: ()=>{
            wrapper.destroy();
            window.swapScreen("server_list","");
        }
        onCountPlayerChanget: ()=>{
            showPlayer(game_harvard.getCountPlayer(), game_harvard.getStatusGame());
        }
        onStageGameChanget: ()=>{
            var status_game = game_harvard.getStatusGame();
            switch(status_game){
                case wrapper.const_waiting_player:
                    information_text.text = "Подтвердите свою готовность";
                    fi_number.setText("",false);
                    fi_number.visible = false;
                    game_harvard.setNumber("-1");
                    but_confirm_text.text = "Я готов";
                break;
                case wrapper.const_active_stage:
                    information_text.text = "Введите число от 1 до 100";
                    time_text.text = "Осталось: " + game_harvard.getTime();
                    fi_number.visible = true;
                    but_confirm.success = false;

                    but_confirm_text.text = "Подтвердить";
                break;
                case wrapper.const_result_stage:
                    information_text.text = "Победитель: " + game_harvard.getLastWinner();
                    time_text.text = "Осталось: " + game_harvard.getTime();
                    showPlayer(game_harvard.getCountPlayer(),status_game);
                    but_confirm.success = false;
                    fi_number.setText("",false);
                    fi_number.visible = false;


                    game_harvard.setPlayerReady(false);
                break;
            }
        }
    }

    function showPlayer(count, stage){

        if(count >= 0){
            enemy_1_box.visible = false
            enemy_2_box.visible = false
            enemy_3_box.visible = false
        }
        if(count >= 1){
            enemy_1_box.visible = true
            enemy_1_text.text = game_harvard.getEnemyName(0);
            if(stage === wrapper.const_result_stage){
                enemy_1_card_text.text = game_harvard.getEnemyNumber(0);
            }
            else{
                enemy_1_card_text.text = "";
            }
        }
        if(count >= 2){
            enemy_2_box.visible = true
            enemy_2_text.text = game_harvard.getEnemyName(1);
            if(stage === wrapper.const_result_stage){
                enemy_2_card_text.text = game_harvard.getEnemyNumber(1);
            }
            else{
                enemy_2_card_text.text = "";
            }
        }
        if(count >= 3){
            enemy_3_box.visible = true;
            enemy_3_text.text = game_harvard.getEnemyName(2);
            if(stage === wrapper.const_result_stage){
                enemy_3_card_text.text = game_harvard.getEnemyNumber(2);
            }
            else{
                enemy_3_card_text.text = "";
            }
        }
    }

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

            x: swidth * 35
            y:parent.y
            z:1
            color: color_vertical_line
        }
        Rectangle{
            id: time_box
            anchors.left: vl_1.right
            anchors.top: parent.top
            width: swidth * 30
            height: parent.height
            color: parent.color

            Text{
                id: time_text
                anchors.fill: parent
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                text: "Осталось: 00:00"
                color: "#FFFFFF"
                font.pointSize: swidth * 1.2
            }
        }


        Rectangle{
            id: vl_2
            width: swidth * 0.2082
            height: parent.height

            x: swidth * 65
            y:parent.y
            z:1
            color: color_vertical_line
        }

        Button{
            property bool hover: false

            id: but_back
            width: swidth * 15
            height: sheight * 5
            anchors.verticalCenter: parent.verticalCenter
            x: swidth * 4

            background: Rectangle{
                color: parent.hover ? color_button_active : color_button_inactive;
                Text{
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: swidth * 1.2
                    color: "#FFFFFF"
                    text: "Вернуться"
                }
            }

            onHoveredChanged: {hover = !hover}
            onClicked: ()=>
            {
                game_harvard.leaveTheGame();
                wrapper.destroy();
                window.swapScreen("server_list","");
            }
        }
    }

    Rectangle{
        id: game_wrapper
        width: parent.width
        height: parent.height - title_box.height
        anchors.top: title_box.bottom
        anchors.left: parent.left
        color: parent.color

        Rectangle{
            id: enemy_1_box
            width: swidth * 11.4062
            height: sheight * 28.3333
            anchors.horizontalCenter: parent.horizontalCenter
            y: sheight * 1.574
            color: parent.color

            Rectangle{
                id: enemy_1_card
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                height: sheight * 25
                width: parent.width
                color: color_background_card

                Text{
                    id: enemy_1_card_text
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#FFFFFF"
                    font.pointSize: swidth * 2
                    text: "27"
                }
            }
            Text {
                id: enemy_1_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                font.pointSize: swidth
                color: "#000000"

                text: "Enemy_one"
            }
        }
        Rectangle{
            id: enemy_2_box
            width: swidth * 11.4062
            height: sheight * 28.3333
            x: swidth * 4.5833
            y: sheight * 30.0925
            color: parent.color

            Rectangle{
                id: enemy_2_card
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                height: sheight * 25
                width: parent.width
                color: color_background_card

                Text{
                    id: enemy_2_card_text
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#FFFFFF"
                    font.pointSize: swidth * 2
                    text: "27"
                }
            }
            Text {
                id: enemy_2_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                font.pointSize: swidth
                color: "#000000"

                text: "Enemy_two"
            }
        }
        Rectangle{
            id: enemy_3_box
            width: swidth * 11.4062
            height: sheight * 28.3333
            x: swidth * 83.75
            y: sheight * 30.0925
            color: parent.color

            Rectangle{
                id: enemy_3_card
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                height: sheight * 25
                width: parent.width
                color: color_background_card

                Text{
                    id: enemy_3_card_text
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    color: "#FFFFFF"
                    font.pointSize: swidth * 2
                    text: "27"
                }
            }
            Text {
                id: enemy_3_text
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                font.pointSize: swidth
                color: "#000000"

                text: "Enemy_three"
            }
        }

        Text{
            id: information_text
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            font.pointSize: swidth * 2
            color: "#000000"

            text: "Победитель Иван"
        }

        Rectangle{
            id: player_zone
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            width: swidth * 22.1296
            height: sheight * 20
            color: color_background_card

            Rectangle{
                id: input_box
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                width: parent.width * 0.8
                height: parent.height
                color: parent.color
                FormInput{
                    id: fi_number
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width
                    height: sheight * 10
                    y: sheight * 1.5
                    color: parent.color

                    color_text_value: "#FFFFFF"
                    text_title: "Ваше число"
                    text_size: swidth * 1.2

                    color_text_input_back: "#00D9C6"
                    color_text_input: "#000000"

                    max_length: 3
                }
                Button{
                    property bool hover: false
                    property bool success: false
                    property int stage: const_waiting_player
                    id: but_confirm
                    anchors.horizontalCenter: parent.horizontalCenter
                    width: parent.width / 2
                    height: sheight * 5
                    y: fi_number.y + fi_number.height + sheight

                    background: Rectangle{
                        width: parent.width
                        height: parent.height
                        color: parent.success ? color_button_success : (parent.hover ? color_button_active : color_button_inactive);

                        Text{
                            id: but_confirm_text
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter
                            font.pointSize: swidth * 0.9
                            color: "#FFFFFF"
                            text: "Подтвердить"
                        }
                    }

                    onHoveredChanged: {hover = !hover}
                    onClicked: ()=>
                    {
                        var status_game = game_harvard.getStatusGame();

                        if(status_game === wrapper.const_waiting_player){
                            if(but_confirm.success === false){
                                game_harvard.setPlayerReady(true);
                            }
                            but_confirm.success = true;
                        }
                        else if(status_game === wrapper.const_active_stage){
                            if(but_confirm.success === false){
                                game_harvard.setNumber(fi_number.getText());
                            }
                            but_confirm.success = true;
                        }
                        else if(status_game === wrapper.const_result_stage){

                        }
                    }
                }
            }
        }
    }

}
