import QtQuick
import QtQuick.Controls 2.15
import QtQuick.Layouts
import "../FormInput"
import "DialogWindow"
import DataBaseModel 1.0
import ViewServerList 1.0

Rectangle {
    property int pos_s_name: 2
    property int pos_s_ip: 0
    property int pos_s_port: 1
    property int swidth: parent.width / 100
    property int sheight: parent.height / 100
    property string color_line: "#C4FBE4"
    property string color_service_box: "#0066A5"
    property string color_bottom_active: "#1EAFDD"
    property string color_bottom_inactive: "#1A93B9"
    property string color_cell_not_even: "#109474"
    property string color_cell_even: "#18C199"
    property string color_current_cell_even: "#18ADC1"
    property string color_current_cell_not_even: "#0F7F98"
    property string color_background_table: "#10945C"
    property string mode_button: "navigation"
    property var width_cell: [16.5104, 14.6354, 10.7812, 16.927]

    property int current_row: -1

    signal setInfoInInfoBox(read_only: bool)
    signal changeModeButton(mode: string)
    onSetInfoInInfoBox: (read_only) =>
    {
        f_i_name.setText(view_server_list.getData(current_row,pos_s_name),read_only)
        f_i_ip.setText(view_server_list.getData(current_row,pos_s_ip),read_only)
        f_i_port.setText(view_server_list.getData(current_row,pos_s_port),read_only)
    }
    onChangeModeButton: (value)=>
    {
        if(value === "add_server")
        {
            current_row = -1;
            setInfoInInfoBox(false);
            but_back_text.text = "Отмена";
            but_next_text.text = "Добавить";
            mode_button = value;
        }
        else if(value === "navigation")
        {
            but_back_text.text = "Вернуться"
            but_next_text.text = "Подключиться"
            mode_button = value;
        }
    }
    function nextButModeInsert()
    {
        if(view_server_list.insertRowData(f_i_name.getText(),f_i_ip.getText(),f_i_port.getText())){
            db_model.insertRows(0,1);
            changeModeButton("navigation");
            setInfoInInfoBox(false);
        }
    }
    function nextButModeNext()
    {
        if(f_i_ip.getText() === "" || f_i_port.getText() === ""
            || f_i_login.getText() === "" || f_i_password.getText() === "")
        {
            dialog_window.open();
            return;
        }
        view_server_list.closeConnection();
        var component = Qt.createComponent("../GameScreen/GameScreen.qml")
        if(component.status === Component.Ready){
            var status = component.createObject(current_screen,{});
            if(status === null){
                console.log("Ошибка в создании окна: \"Игровой экран\"");
            }
            window.swapScreen("game_screen");
        }
    }
    function backButModeCancel()
    {
        current_row = -1;
        setInfoInInfoBox(false);
        changeModeButton("navigation");
    }
    function backButModeBack()
    {
        view_server_list.closeConnection();
        wrapper.destroy();
        window.swapScreen("start_screen");
    }
    id:wrapper
    width: parent.width
    height: parent.height
    x: parent.x
    y: parent.y
    color: parent.color
    onWindowChanged:{view_server_list.initTable();}
    DataBaseModel{
        id: db_model
    }
    ViewServerList{
        id: view_server_list
        onInitTable: () =>
        {
            db_model.setTableHeader(view_server_list.parseHeaderData())
            db_model.setTableData(view_server_list.parseData())
        }
    }
    DialogServerList{
        id: dialog_window
        anchors.centerIn: parent
        width: swidth * 30
        height: sheight * 40
        onClickOk: {dialog_window.close();}
    }
    //Заголовок
    Rectangle{
        id: title_box
        anchors.horizontalCenter: parent.horizontalCenter
        y: sheight * 6.5740
        width: swidth * 21.3541
        height: sheight * 6.7592
        color:parent.color
        Text{
            id: title_text
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            text: "Список серверов"
            font.family: "Inter"
            font.pointSize: swidth * 2.15
            color:"#000000"
        }
    }

    Rectangle{
        id: server_list_box
        width: swidth * 83.8541
        height: sheight * 71.9444
        anchors.horizontalCenter: parent.horizontalCenter
        y: sheight * 19.1666
        color: "#10945C"

        //горизонтальная линия
        Rectangle{
            width: parent.width
            height: sheight * 0.37
            anchors.left: parent.left
            y: sheight * 7.1296
            color: color_line
            z: 1
        }
        Rectangle{
            width: swidth * 58.8541
            height: sheight * 0.37
            anchors.left: parent.left
            y: parent.height - sheight * 7.1296
            color: color_line
            z: 1
        }
        //Вертикальная линия
        Rectangle{
            width: swidth * 0.2083
            height: parent.height
            anchors.top: parent.top
            x: swidth * 58.8541
            color: color_line
            z: 1
        }

        //Информация о сервере
        Rectangle{
            id: info_box
            width: swidth * 25
            height: parent.height
            anchors.right: parent.right
            anchors.top: parent.top
            color: color_service_box

            Rectangle{
                id: info_title_box
                width: parent.width
                height: sheight * 7.1296
                anchors.top: parent.top
                anchors.right: parent.right
                color:parent.color
                Text{
                    id: info_title_text
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    text: "Информация"
                    font.family: "Inter"
                    font.pointSize: swidth * 1.15
                    color:"#FFFFFF"
                }
            }
            Column{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: info_title_box.bottom
                topPadding: sheight * 1.574
                spacing: sheight * 2.1296
                FormInput{
                    id: f_i_name
                    anchors.horizontalCenter: parent.horizontalCenter

                    width: swidth * 19.6354
                    height: sheight * 8.4259
                    color: color_service_box

                    color_text_value: "#FFFFFF"
                    text_title: "Название"
                    text_size: swidth * 1.15

                    color_text_input_back: "#00D9C6"
                    color_text_input: "#000000"
                }
                FormInput{
                    id: f_i_ip
                    anchors.horizontalCenter: parent.horizontalCenter

                    width: swidth * 19.6354
                    height: sheight * 8.4259
                    color: color_service_box

                    color_text_value: "#FFFFFF"
                    text_title: "IP"
                    text_size: swidth * 1.15

                    color_text_input_back: "#00D9C6"
                    color_text_input: "#000000"

                    max_length: 15
                }
                FormInput{
                    id: f_i_port
                    anchors.horizontalCenter: parent.horizontalCenter

                    width: swidth * 19.6354
                    height: sheight * 8.4259
                    color: color_service_box

                    color_text_value: "#FFFFFF"
                    text_title: "Порт"
                    text_size: swidth * 1.15

                    color_text_input_back: "#00D9C6"
                    color_text_input: "#000000"

                    max_length: 5
                }
                FormInput{
                    id: f_i_login
                    anchors.horizontalCenter: parent.horizontalCenter

                    width: swidth * 19.6354
                    height: sheight * 8.4259
                    color: color_service_box

                    color_text_value: "#FFFFFF"
                    text_title: "Логин"
                    text_size: swidth * 1.15

                    color_text_input_back: "#00D9C6"
                    color_text_input: "#000000"
                }
                FormInput{
                    id: f_i_password

                    anchors.horizontalCenter: parent.horizontalCenter

                    width: swidth * 19.6354
                    height: sheight * 8.4259
                    color: color_service_box

                    color_text_value: "#FFFFFF"
                    text_title: "Пароль"
                    text_size: swidth * 1.15

                    color_text_input_back: "#00D9C6"
                    color_text_input: "#000000"
                }
            }

            Rectangle{
                id: button_box
                width: swidth * 22.8125
                height: sheight * 6.9444
                anchors.horizontalCenter: parent.horizontalCenter
                y: parent.height - (sheight * 3.0555 + sheight * 6.9444)
                color: parent.color

                Button{
                    property bool hover: false

                    id: but_back
                    width: swidth * 9.427
                    height: parent.height
                    anchors.top: parent.top
                    anchors.left: parent.left
                    clip: true

                    background: Rectangle{
                        width: parent.width
                        height: parent.height
                        color: parent.hover ? color_bottom_active : color_bottom_inactive

                        Text{
                            id: but_back_text
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter

                            text: "Вернуться"
                            font.family: "Inter"
                            font.pointSize: swidth * 0.8
                            color:"#FFFFFF"
                        }
                    }
                    onHoveredChanged: {hover = !hover}
                    onClicked: {
                        if(mode_button === "navigation"){
                            backButModeBack()
                        }
                        else if( mode_button === "add_server"){
                            backButModeCancel()
                        }
                    }
                }

                Button{
                    property bool hover: false

                    id: but_next
                    width: swidth * 9.427
                    height: parent.height
                    anchors.top: parent.top
                    anchors.right: parent.right


                    background: Rectangle{
                        width: parent.width
                        height: parent.height
                        color: parent.hover ? color_bottom_active : color_bottom_inactive

                        Text{
                            id: but_next_text
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter

                            text: "Подключиться"
                            font.family: "Inter"
                            font.pointSize: swidth * 0.8
                            color:"#FFFFFF"
                        }
                    }

                    onHoveredChanged: {hover = !hover;}
                    onClicked: {
                        if(mode_button === "navigation"){
                            nextButModeNext();
                        }
                        else if( mode_button === "add_server"){
                            nextButModeInsert();
                        }
                    }
                }
            }


        }

        //Таблица с серверами
        Rectangle{
            id: table_servers
            width: parent.width - info_box.width
            height: parent.height
            anchors.left: parent.left
            anchors.top: parent.top
            color: parent.color

            Rectangle{
                id: table_title
                width: parent.width
                height: sheight * 7.1296
                color: color_service_box
                anchors.left: parent.left
                anchors.top: parent.top
                Text{
                    id: server_name
                    x: parent.x
                    width: width_cell[0] * swidth;
                    height: parent.height

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    text: "Наименование"
                    font.family: "Inter"
                    font.pointSize: swidth * 1.15
                    color:"#FFFFFF"
                }
                Rectangle{
                    width: swidth * 0.2083
                    height: parent.height

                    anchors.left: server_name.right
                    color: color_line
                    z: 1
                }
                Text{
                    id: server_ip
                    x: server_name.x + server_name.width
                    width: width_cell[1] * swidth;
                    height: parent.height

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    text: "IP"
                    font.family: "Inter"
                    font.pointSize: swidth * 1.15
                    color:"#FFFFFF"
                }
                Rectangle{
                    width: swidth * 0.2083
                    height: parent.height

                    anchors.left: server_ip.right
                    color: color_line
                    z: 1
                }
                Text{
                    id: server_port
                    x: server_ip.x + server_ip.width
                    width: width_cell[2] * swidth;
                    height: parent.height

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    text: "Порт"
                    font.family: "Inter"
                    font.pointSize: swidth * 1.15
                    color:"#FFFFFF"
                }
                Rectangle{
                    width: swidth * 0.2083
                    height: parent.height

                    anchors.left: server_port.right
                    color: color_line
                    z: 1
                }
                Text{
                    id: server_count_player
                    x: server_port.x + server_port.width
                    width: width_cell[3] * swidth;
                    height: parent.height

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                    text: "Кол-во игроков"
                    font.family: "Inter"
                    font.pointSize: swidth * 1.15
                    color:"#FFFFFF"
                }

            }
            Rectangle{
                id: table_box
                width: parent.width
                height: parent.height - table_title.height - tool_box.height
                anchors.left: parent.left
                anchors.top: table_title.bottom
                color: color_background_table
                ColumnLayout {
                    anchors.fill: table_box
                    spacing: 0

                    TableView{
                        id: table
                        width: table_box.width
                        height: table_box.height
                        clip: true
                        boundsBehavior:Flickable.StopAtBounds
                        columnWidthProvider: (column)=>{return swidth * width_cell[column]}
                        model: db_model
                        selectionModel: ItemSelectionModel
                        {
                            model: db_model
                        }
                        ScrollBar.vertical: ScrollBar {
                            policy: ScrollBar.AsNeeded
                            active: true
                            onActiveChanged: {
                                if (!active)
                                    active = true;
                            }
                        }

                        delegate: Rectangle {

                            implicitHeight: sheight * 4.2407
                            border.color: color_line
                            border.width: swidth * 0.1041
                            color: (row === current_row) ? (row % 2 ? color_current_cell_even : color_current_cell_not_even) : (row % 2 ? color_cell_even: color_cell_not_even)

                            Text {
                                id: cellText
                                text: display
                                anchors.verticalCenter: parent.verticalCenter
                                x: swidth * 0.2082
                            }
                            MouseArea{
                                anchors.fill: parent
                                onClicked: {
                                    current_row = row
                                    setInfoInInfoBox(true)
                                }
                            }

                        }

                    }
                }
            }
        }

        //Панель инструментов
        Rectangle{
            id: tool_box
            width: swidth * 58.8541
            height: sheight * 6.8518
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            color: color_service_box

            Row{
                width: parent.width
                height: parent.height
                leftPadding: swidth * 1.302
                anchors.verticalCenter: parent.verticalCenter
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: swidth * 21.9791

                Button{
                    id: but_update_list
                    property bool hover: false

                    anchors.verticalCenter: parent.verticalCenter

                    width: swidth * 11.25
                    height: sheight * 4.6296

                    background: Rectangle{
                        width: parent.width
                        height: parent.height
                        color: parent.hover ? color_bottom_active : color_bottom_inactive

                        Text{
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.horizontalCenter: parent.horizontalCenter

                            text: "Обновить"
                            font.family: "Inter"
                            font.pointSize: swidth * 0.8
                            color:"#FFFFFF"
                        }
                    }
                    onHoveredChanged: {hover = !hover}
                    onClicked:
                    {
                        current_row = -1
                        setInfoInInfoBox(false)
                    }
                }
                Row{
                    height: parent.height
                    spacing: swidth * 0.7291
                    Button{
                        property bool hover: false

                        id: but_add_server
                        anchors.verticalCenter: parent.verticalCenter
                        width: swidth * 11.25
                        height: sheight * 4.6296
                        background: Rectangle{
                            width: parent.width
                            height: parent.height
                            color: parent.hover ? color_bottom_active : color_bottom_inactive

                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter

                                text: "Добавить сервер"
                                font.family: "Inter"
                                font.pointSize: swidth * 0.8
                                color:"#FFFFFF"
                            }
                        }
                        onClicked:
                        {
                            changeModeButton("add_server")
                        }
                        onHoveredChanged: {hover = !hover}
                    }
                    Button{
                        property bool hover: false

                        id: but_delete_server
                        anchors.verticalCenter: parent.verticalCenter
                        width: swidth * 11.25
                        height: sheight * 4.6296
                        background: Rectangle{
                            width: parent.width
                            height: parent.height
                            color: parent.hover ? color_bottom_active : color_bottom_inactive

                            Text{
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.horizontalCenter: parent.horizontalCenter

                                text: "Удалить сервер"
                                font.family: "Inter"
                                font.pointSize: swidth * 0.8
                                color:"#FFFFFF"
                            }
                        }
                        onHoveredChanged: {hover = !hover}
                        onClicked: ()=>
                        {
                            if(view_server_list.deleteRowData(current_row)){
                                db_model.removeRows(current_row,1);
                                current_row = -1;
                                setInfoInInfoBox(false);
                                changeModeButton("navigation");
                            }
                        }
                    }
                }
            }
        }
    }


}
