#include "ServerRenderer.hpp"

ServerRenderer::ServerRenderer()
{
    __title_box.x = 0;
    __title_box.y = 1;
    __title_box.height = 4;

    __screen_box.x = __title_box.x;
    __screen_box.y = __title_box.y + __title_box.height + 1;
    __screen_box.height = 9;

    __input_box.x = __title_box.x;
    __input_box.y = __screen_box.y + __screen_box.height + 1;
    __input_box.height = 2;

    __log_box.x = __title_box.x;
    __log_box.y = __input_box.y + __input_box.height + 1;
    __log_box.height = 5;
}

void ServerRenderer::init(QVector<struct client_t> *players, QString ip, QString port,QString *time, STATUS_GAME *status_game, int width){
    __players = players;
    __ip = ip;
    __port = port;
    __width = width;
    __time = time;
    __status_game = status_game;
    __title_box.width = __screen_box.width = __input_box.width = __log_box.width = __width;

    __clearScreen();
    __drawTitle();
    __drawScreen();
    __drawLog();
    __drawInputField();
}
void ServerRenderer::draw(QByteArray command){
    __execCommand(command);
    __clearScreen();
    __drawTitle();
    __drawScreen();
    __drawLog();
    __drawInputField();
    //usleep(100);
}

void ServerRenderer::__drawTitle(){

    __drawRectangle(__title_box.x,
                    __title_box.y,
                    __title_box.width,
                    __title_box.height);

    __setCarriagePos(__title_box.x + 3, __title_box.y + 1);
    printf("IP: %s", __ip.toStdString().c_str());
    __setCarriagePos(__title_box.x + 3, __title_box.y + 3);
    printf("Port: %s", __port.toStdString().c_str());
    __setCarriagePos(__title_box.x + 68, __title_box.y + 1);
    printf("Time: %s", __time->toStdString().c_str());
    __setCarriagePos(__title_box.x + 52, __title_box.y + 3);
    printf("Status_game: ");
    switch((int)(*__status_game)){
        case WAITING_PLAYER:
            printf("Waiting player");
            break;
        case ACTIVE_STAGE:
            printf("Active stage");
            break;
        case RESULTS_STAGE:
            printf("Result stage");
            break;
    }
}
void ServerRenderer::__drawScreen(){
    __drawRectangle(__screen_box.x,
                            __screen_box.y,
                            __screen_box.width,
                            __screen_box.height);

    if(__screen == __MAIN_SCREEN){
        __setCarriagePos(__screen_box.x +3, __screen_box.y+1);
        printf("1: Посмотреть список игроков");
        __setCarriagePos(__screen_box.x +3, __screen_box.y+3);
        printf("2: Изменить права игрока");
        __setCarriagePos(__screen_box.x +3, __screen_box.y+5);
        printf("3: Выгнать игрока");
        __setCarriagePos(__screen_box.x +3, __screen_box.y+7);
        printf("4: Выключить сервер");

    }
    else if(__screen == __PLAYER_LIST_SCREEN){
        __setCarriagePos(__screen_box.x +3, __screen_box.y+1);
        printf("1: Вернуться");
        __drawPlayerList();
    }
    else if(__screen == __ACCESS_MODE_CHANGE_SCREEN){
        __setCarriagePos(__screen_box.x +3, __screen_box.y+1);
        printf("Выберите игрока");

        for(int i = 0; i < __players->size() && i < 2;i++){
            __setCarriagePos(__screen_box.x +3, __screen_box.y+3 + i*2);
            printf("%d : %s ", i+1, __players->at(i).client_login.toStdString().c_str());
            switch(__players->at(i).access_level){
                case Controller_DB_Manager::ACCESS_STANDART_PLAYER:
                    printf("(S)");
                    break;

                case Controller_DB_Manager::ACCESS_MODERATION_PLAYER:
                    printf("(M)");
                    break;
            }
        }
        for(int i = 2,j = 0; i < __players->size(); i++, j++){
            __setCarriagePos(__screen_box.x + __screen_box.width/2 + 3, __screen_box.y+3 + j*2);
            printf("%d : %s ", i+1, __players->at(i).client_login.toStdString().c_str());
            switch(__players->at(i).access_level){
                case Controller_DB_Manager::ACCESS_STANDART_PLAYER:
                        printf("(S)");
                        break;

                case Controller_DB_Manager::ACCESS_MODERATION_PLAYER:
                    printf("(M)");
                    break;
            }
        }
        __setCarriagePos(__screen_box.x +3, __screen_box.y+3 + 2*2);
        printf("5: Вернуться");
        //__drawPlayerList();
    }
    else if(__screen == __KICK_PLAYER_SCREEN){
        __setCarriagePos(__screen_box.x +3, __screen_box.y+1);
        printf("Выберите игрока");

        for(int i = 0; i < __players->size() && i < 2;i++){
            __setCarriagePos(__screen_box.x +3, __screen_box.y+3 + i*2);
            printf("%d : %s ", i+1, __players->at(i).client_login.toStdString().c_str());
            switch(__players->at(i).access_level){
                case Controller_DB_Manager::ACCESS_STANDART_PLAYER:
                    printf("(S)");
                    break;

                case Controller_DB_Manager::ACCESS_MODERATION_PLAYER:
                    printf("(M)");
                    break;
            }
        }
        for(int i = 2, j = 0; i < __players->size(); i++, j++){
            __setCarriagePos(__screen_box.x + __screen_box.width/2 + 3, __screen_box.y+3 + j * 2);
            printf("%d : %s ", i+1, __players->at(i).client_login.toStdString().c_str());
            switch(__players->at(i).access_level){
                case Controller_DB_Manager::ACCESS_STANDART_PLAYER:
                        printf("(S)");
                        break;

                case Controller_DB_Manager::ACCESS_MODERATION_PLAYER:
                    printf("(M)");
                    break;
            }
        }

        __setCarriagePos(__screen_box.x +3, __screen_box.y+3 + 2*2);
        printf("5: Вернуться");
        //__drawPlayerList();
    }
}
void ServerRenderer::__drawInputField(){
    __drawRectangle(__input_box.x,
                    __input_box.y,
                    __input_box.width,
                    __input_box.height);
    __setCarriagePos(__input_box.x + 2, __input_box.y+1);
    printf("INPUT: ");
}
void ServerRenderer::__drawLog(){
    __drawRectangle(__log_box.x,
                    __log_box.y,
                    __log_box.width,
                    __log_box.height);
    __setCarriagePos(__log_box.x + 2, __log_box.y +1);
    for(int i = 0; i < __log_history.size(); i++){
        __setCarriagePos(__log_box.x + 2, __log_box.y +1+i);
        printf("- %s", __log_history.at(i).toStdString().c_str());
    }
}

void ServerRenderer::__drawPlayerList(){
    __setCarriagePos(__screen_box.x + __screen_box.width/2,__screen_box.y);
    printf("\u252c");
    for(int i = 0; i < __screen_box.height; i++){
        __setCarriagePos(__screen_box.x + __screen_box.width/2,__screen_box.y +1 + i);
        printf("\u2502");
    }
    __setCarriagePos(__screen_box.x + __screen_box.width/2,__screen_box.y + __screen_box.height);
    printf("\u2534");

    for(int i = 0; i < __players->size(); i++){
        __setCarriagePos(__screen_box.x + __screen_box.width/2+3,__screen_box.y + 1 + i*2);
        printf("- : %s", __players->at(i).client_login.toStdString().c_str());
        switch(__players->at(i).access_level){
            case Controller_DB_Manager::ACCESS_STANDART_PLAYER:
                printf("(S)");
                break;
            case Controller_DB_Manager::ACCESS_MODERATION_PLAYER:
                printf("(M)");
                break;
        }
    }
}

void ServerRenderer::__drawRectangle(int x, int y, int width, int height){
    __setCarriagePos(x,y);

    printf("\u250c");
    for(int i = 1, length = width - 1; i < length; i++){
        printf("\u2500");
    }
    printf("\u2510");

    __setCarriagePos(x+1,y+height);
    printf("\u2514");
    for(int i = 1, length = width - 1; i < length; i++){
        printf("\u2500");
    }
    printf("\u2518");

    for(int i = 1, length = height; i < length; i++){
        __setCarriagePos(x,y+i);
        printf("\u2502");
    }

    for(int i = 1,length = height; i < length; i++){
        __setCarriagePos(width,y+i);
        printf("\u2502");
    }

}

void ServerRenderer::__execCommand(QByteArray command){


    if(__screen == __MAIN_SCREEN){

        //__select_field_mode = false;
        //посмотреть список игроков
        if(command == __FIELD_1){
            __screen = __PLAYER_LIST_SCREEN;
            //__select_field_mode = true;
        }
        //изменить права игрока
        else if(command == __FIELD_2){
            __screen = __ACCESS_MODE_CHANGE_SCREEN;
            //__select_field_mode = true;
        }
        //выгнать игрока
        else if(command == __FIELD_3){
            __screen = __KICK_PLAYER_SCREEN;
            //__select_field_mode = true;
        }
        //выключить сервер
        else if(command == __FIELD_4){
            __command_buffer = JsonMessages::closeApplication();
        }
    }
    else if(__screen == __PLAYER_LIST_SCREEN){
        //вернуться
        if(command == __FIELD_1){
            __screen = __MAIN_SCREEN;
        }
    }
    else if(__screen == __ACCESS_MODE_CHANGE_SCREEN){
        if(__select_field_mode){

            //сделать модератором игрока ...
            if(command == __FIELD_1 || command == __FIELD_2 || command == __FIELD_3 || command == __FIELD_4){
                //__select_field_mode = false;
                if(command.toInt()-1 < __players->size()){
                    switch(__players->at(command.toInt()-1).access_level){
                    case Controller_DB_Manager::ACCESS_STANDART_PLAYER:
                        (*__players)[command.toInt()-1].access_level = Controller_DB_Manager::ACCESS_MODERATION_PLAYER;
                        break;
                    case Controller_DB_Manager::ACCESS_MODERATION_PLAYER:
                        (*__players)[command.toInt()-1].access_level = Controller_DB_Manager::ACCESS_STANDART_PLAYER;
                        break;
                    }
                    __command_buffer = JsonMessages::changeAccessMode(__players->at(command.toInt()-1).client_login,
                                                                        __players->at(command.toInt()-1).access_level);
                }
            }

        }
        //вернуться
        if(command == __FIELD_5){
            __screen = __MAIN_SCREEN;
            //__select_field_mode = true;
        }
    }
    else if(__screen == __KICK_PLAYER_SCREEN){

        //выгнать игрока ...
        if(command == __FIELD_1 || command == __FIELD_2 || command == __FIELD_3 || command == __FIELD_4){
            if(command.toInt()-1 < __players->size()){
                __command_buffer = JsonMessages::kickPlayer(__players->at(command.toInt()-1).client_login);
            }
        }
        //вернуться
        else if(command == __FIELD_5){
            __screen = __MAIN_SCREEN;
        }
    }
}
void ServerRenderer::addLog(QString log){
    if(__log_history.size() > __LOG_HISTORY_MAX){
        __log_history.pop_front();
    }
    __log_history.push_back(log);
    __fout.open(LOG_FILE,ofstream::app);
    if(__fout.is_open()){
        switch(*__status_game){
        case WAITING_PLAYER:
            __fout << "STAGE: WAITING PLAYER: ";
            break;
        case ACTIVE_STAGE:
            __fout << "STAGE: ACTIVE; ";
            break;
        case RESULTS_STAGE:
            __fout << "STAGE: RESULTS; ";
            break;
        }
        __fout << "TIME: " << __time->toStdString() << "; ";

        __fout << " MESSAGE: " <<log.toStdString() <<"; "<< endl;

        __fout.close();
    }
}

void ServerRenderer::__setFGColor(TERMINAL_COLOR color){
    switch(color){
    case BLACK:
        printf("\E[38;2;0;0;0m");
        break;
    case WHITE:
        printf("\E[38;2;255;255;255m");
        break;
    case RED:
        printf("\E[38;2;222;56;43m");
        break;
    case BLUE:
        printf("\E[38;2;44;181;233m");
        break;
    case YELLOW:
        printf("\E[38;2;255;255;0m");
        break;
    }
}
void ServerRenderer::__setBGColor(TERMINAL_COLOR color){
    switch(color){
    case BLACK:
        printf("\E[48;2;0;0;0m");
        break;
    case WHITE:
        printf("\E[48;2;255;255;255m");
        break;
    case RED:
        printf("\E[48;2;222;56;43m");
        break;
    case BLUE:
        printf("\E[48;2;44;181;233m");
        break;
    case YELLOW:
        printf("\E[48;2;255;255;0m");
        break;
    }
}
void ServerRenderer::__setCarriagePos(int x, int y){
    printf("\E[%d;%df", y, x);
}
void ServerRenderer::__clearScreen(){
    printf("\E[H\E[J");
    //system("clear");
}
QJsonDocument ServerRenderer::getCommand(){
    return __command_buffer;
}
void ServerRenderer::clearBuffer(){
    __command_buffer = QJsonDocument();
}
