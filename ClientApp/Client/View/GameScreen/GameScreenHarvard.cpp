#include "GameScreenHarvard.hpp"

GameScreenHarvard::GameScreenHarvard(QObject *parent): QObject(parent)
{
    pthread_mutex_init(&__mutex,nullptr);
    __timer = new QTimer(this);
    connect(__timer,SIGNAL(timeout()), this,SLOT(__synchronization()));
    __timer->start(500);
}
GameScreenHarvard::~GameScreenHarvard()
{
    pthread_mutex_destroy(&__mutex);
    disconnect(__timer,SIGNAL(timeout()), this,SLOT(__synchronization()));
    delete __timer;
}
void GameScreenHarvard::setNetManager(ClientManager *client_manager){
    __client_manager = client_manager;
}

void GameScreenHarvard::leaveTheGame(){
    __client_manager->logoutIsServer();
}

void GameScreenHarvard::__synchronization(){
    __client_manager->synchronization(__player_ready,__name,QString().setNum(__number));

    QJsonDocument result;
    QJsonValue value;
    QJsonArray array;

    __client_manager->setOperationMode(NetWorker::OPERATION_READ);

    for(int i = 0;i < 3;i++){

        __client_manager->stepExecute();

        result =  QJsonDocument::fromJson(__client_manager->getMessageBuffer());

        value = result["target"];
        if(!value.isUndefined()){
            if(value.toString() == "synchronization" && result["login"].isUndefined()){

                value = result["status_game"];
                __status_game = (STATUS_GAME)value.toString().toInt();

                if(__status_game != WAITING_PLAYER){
                    value = result["time"];
                    __time = value.toString();
                }
                else{
                    __time = "00:00";
                }
                value = result["player_logins"];
                if(value.isUndefined()){
                    return;
                }

                array = value.toArray();
                __count_player = array.size();
                __enemy_name.clear();
                for(int j = 0; j < __count_player; j++){
                    __enemy_name.push_back(array[j].toString());
                }

                value = result["player_numbers"];
                if(value.isUndefined()){
                    return;
                }

                array = value.toArray();

                __enemy_number.clear();
                for(int j = 0; j < __count_player; j++){
                    __enemy_number.push_back(array[j].toString());
                }
                value = result["winner"];
                __last_winner = value.toString();

                emit stageGameChanget();
                emit countPlayerChanget();
                return;
            }
            else if(value.toString() == "logout"){
                __client_manager->closeConnection();
                emit kickFromServer();
            }
        }
    }
}


void GameScreenHarvard::setNumber(QString number){
    if(number == ""){
        return;
    }
    if(number == "-1"){
        __number = -1;
        return;
    }

    int t_num = number.toInt();

    if(t_num > 100){
        __number = 100;
        return;
    }
    else if(t_num < 0){
        __number = 0;
        return;
    }
    __number = t_num;
}

void GameScreenHarvard::setName(QString name){
    if(name == ""){
        return;
    }
    __name = name;
}
void GameScreenHarvard::setPlayerReady(bool ready){
    __player_ready = ready;
}

int GameScreenHarvard::getCountPlayer(){
    return __count_player;
}
QString GameScreenHarvard::getName(){
    return __name;
}
int GameScreenHarvard::getNumber(){
    return __number;
}
int GameScreenHarvard::getStatusGame(){
    return __status_game;
}
QString GameScreenHarvard::getTime(){
    return __time;
}
QString GameScreenHarvard::getEnemyName(int num_player){
    if(num_player >= __enemy_name.size()){
        return "error";
    }
    return __enemy_name[num_player];
}
QString GameScreenHarvard::getEnemyNumber(int num_player){
    if(num_player >= __enemy_number.size()){
        return "-1";
    }
    //qDebug() << __enemy_number[num_player];
    return __enemy_number[num_player];
}
QString GameScreenHarvard::getLastWinner(){
    return __last_winner;
}
