import QtQuick
import QtQuick.Window
import "./View/StartScreen"
Window {
    id: window

    width: 800
    height: 800
    visible: true
    title: qsTr("Little Bombers")
    signal swapScreen(after_screen: string)

    Rectangle{
        id: current_screen
        width: parent.width
        height: parent.height
        color: "#7DDAD2"
        StartScreen{
            id: start_screen
            width: parent.width
            height: parent.height
        }
    }

    onSwapScreen: (after_screen)=>
    {
        if(after_screen === "server_list"){
            start_screen.visible = false
        }
        else if(after_screen === "game_screen"){
            start_screen.visible = false
        }
        else{
            start_screen.visible = true
        }
    }
}
