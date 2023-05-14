import QtQuick
import QtQuick.Window
import "./View/StartScreen"
import ClientWrapper

Window {
    id: window

    width: 800
    height: 800
    visible: true
    title: qsTr("Little Bombers")
    signal swapScreen(after_screen: string, login:string)


    Rectangle{

        id: current_screen
        width: parent.width
        height: parent.height
        color: "#7DDAD2"

        ClientWrapper{
            id: client_wrapper
        }

        StartScreen{
            id: start_screen
            width: parent.width
            height: parent.height
        }
    }

    onSwapScreen: (after_screen, login)=>
    {
        var component;
        var status;
        if(after_screen === "server_list"){
            start_screen.visible = false
            component = Qt.createComponent("View/ServerList/ServerList.qml")
            if(component.status === Component.Ready){
                status = component.createObject(current_screen,{});
                if(status === null){
                    console.log("Ошибка в создании окна: \"Список серверов\"");
                }
            }
        }
        else if(after_screen === "game_screen"){
            start_screen.visible = false
            console.log(login);
            component = Qt.createComponent("View/GameScreen/GameScreenHarvard.qml")
            if(component.status === Component.Ready){
                status = component.createObject(current_screen,{game_login: login});
                if(status === null){
                  console.log("Ошибка в создании окна: \"Игровой экран\"");
                }
            }
        }
        else{
            start_screen.visible = true
        }
    }
}
