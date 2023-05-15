#include "ServerApp.hpp"

ServerApp::ServerApp(int width)
{
    __width_application = width;
    __s_renderer = new ServerRenderer;
    __s_manager = new ServerManager(__MAX_PLAYER_COUNT);
    __controller_db_manager = new Controller_DB_Manager();

    pthread_mutex_init(&__key_mutex, nullptr);
}
ServerApp::~ServerApp()
{
    pthread_mutex_destroy(&__key_mutex);
    delete __s_renderer;
    delete __s_manager;
    delete __controller_db_manager;
}
void* ServerApp::__keyReader(void *value){
    key_info_t *object = (key_info_t*)value;
    char keys[ServerApp::SIZE_TEMP_KEY_BUFFER+1];
    bool skip_step = false, exit = false;

    for(;!exit;){
        pthread_mutex_lock(object->mutex);
        skip_step = *(object->skip_step);
        pthread_mutex_unlock(object->mutex);

        if(skip_step){
            continue;
        }

        scanf("%s",keys);

        pthread_mutex_lock(object->mutex);
        if(!(*object->key_read)){
            exit = true;
        }
        *object->key_buffer = keys;
        *(object->skip_step) = true;
        pthread_mutex_unlock(object->mutex);



    }
    pthread_exit(nullptr);
}

void ServerApp::execute()
{
    //init();
    bool exit = false;

    for(;!exit;){
        pthread_mutex_lock(&__key_mutex);
        __key_command = __key_buffer;
        __key_buffer.clear();

        if(__key_command.size() >0 ){
            __skip_step = true;
        }
        if(__close_server){
            __key_read = false;
            exit = true;
        }
        pthread_mutex_unlock(&__key_mutex);

        __s_manager->stepExecute();

        __clients = __s_manager->getClients();

        if(__key_command.size() > 0){

            __s_renderer->draw(__key_command);
            __message_from_view = __s_renderer->getCommand();
            pthread_mutex_lock(&__key_mutex);
            __skip_step = false;
            pthread_mutex_unlock(&__key_mutex);

        }
        __temp_time = std::chrono::steady_clock::now();

        if(std::chrono::duration_cast<std::chrono::seconds>(__temp_time - __last_time).count()  >= 1.f){
            if(__game_status == ACTIVE_STAGE || __game_status == RESULTS_STAGE){
                __s_current_time--;
                __timer = "00:" + QString().setNum(__s_current_time);
                //__s_renderer->draw("");
            }

            __last_time = __temp_time;
        }

        __commandProcessing();

        __gameStep();

    }
}
void ServerApp::init()
{
    __s_manager->initServer();
    printf("Init Server\n");

    QMap<QString,QString> ip_port = __s_manager->getIpAndPort();
    __clients = __s_manager->getClients();
    __s_renderer->init(__clients,ip_port[MAP_IP],ip_port[MAP_PORT],&__timer,&__game_status,__width_application);

    __key_read = true;

    __thread_arguments.mutex = &__key_mutex;
    __thread_arguments.key_read = &__key_read;
    __thread_arguments.key_buffer = &__key_buffer;
    __thread_arguments.skip_step = &__skip_step;
    pthread_create(&__key_input_id,nullptr,ServerApp::__keyReader,(void*)&__thread_arguments);
    pthread_detach(__key_input_id);
}

void ServerApp::__commandProcessing(){
    QJsonDocument document;
    QJsonValue target;
    QString target_value;

    for(int i = 0; i < __clients->size(); i++){

        document = QJsonDocument::fromJson(__clients->at(i).message_buffer);
        target = document["target"];

        if(!target.isUndefined()){
            target_value = target.toString();
            if(target_value == "login"){
                __autorization(&((*__clients)[i]), document);
            }
            else if(target_value == "logout"){
                __logoutClient(&((*__clients)[i]));
            }
            else if(target_value == "check_count_players"){
                __checkCountPlayers(&((*__clients)[i]));
            }
            else if(target_value == "synchronization"){
                //recive Query and send reply
                __synchronization(&((*__clients)[i]),document);
            }

        }

    }
    target = __message_from_view["target"];
    if(!target.isUndefined()){

        target_value = target.toString();
        if(target_value == "close_server"){
            system("clear");
            this->destroy();
        }
        else if(target_value == "change_access_level"){
            QJsonValue login = __message_from_view["login"];
            QJsonValue level = __message_from_view["access_level"];
            for(int i = 0; i < __clients->size(); i++){
                if(__clients->at(i).client_login == login.toString()){
                    __s_renderer->addLog("Player '"+login.toString() +"': access level changet");
                    (*__clients)[i].access_level = (Controller_DB_Manager::ACCESS_LEVEL)level.toInt();
                    __controller_db_manager->changeAccessLevel(login,(*__clients)[i].access_level);
                    __s_renderer->clearBuffer();
                }
            }
        }
        else if(target_value == "kick_player"){
            QJsonValue login = __message_from_view["login"];
            for(int i = 0; i < __clients->size(); i++){
                if(__clients->at(i).client_login == login.toString()){
                    __s_renderer->addLog("Player '"+login.toString() +"' kick from the server");
                    //__s_renderer->draw("");

                    (*__clients)[i].message_buffer = JsonMessages::logout().toJson(QJsonDocument::Compact);
                    (*__clients)[i].mode = NetWorker::OPERATION_WRITE;
                    (*__clients)[i].access_level = Controller_DB_Manager::ACCESS_ERROR;
                    __s_renderer->clearBuffer();
                }
            }
        }

        __message_from_view = QJsonDocument();
    }
}
void ServerApp::__synchronization(struct client_t *client, QJsonDocument document){

    QJsonValue target = document["ready"];

    printf("%s ", target.toString().toStdString().c_str());
    client->ready = target.toBool();

    target = document["number"];

    client->number = target.toString().toInt();

    //send Reply
    QVector<QString> player_logins;
    QVector<QString> player_numbers;
    for(size_t i = 0; i < __clients->size(); i++){
        if((*__clients)[i].client_login != client->client_login){
            player_logins.push_back((*__clients)[i].client_login);
            player_numbers.push_back(QString().setNum((*__clients)[i].number));
        }
    }

    client->message_buffer = JsonMessages::synchronizationReply(__game_status,player_logins,
                                                                player_numbers,__last_winner,__timer).toJson(QJsonDocument::Compact);
    client->mode = NetWorker::OPERATION_WRITE;
}
void ServerApp::__autorization(struct client_t *client, QJsonDocument document){

    QJsonValue login = document["login"];
    QJsonValue password = document["password"];
    QString message;

    Controller_DB_Manager::ACCESS_LEVEL result = __controller_db_manager->connectPlayer(login,password, &message);

    switch(result){
        case Controller_DB_Manager::ACCESS_ERROR:
            client->message_buffer = JsonMessages::authFailed().toJson(QJsonDocument::Compact);
            client->mode = NetWorker::OPERATION_WRITE;
            client->access_level = result;
        break;
        default:
            client->client_login = login.toString();
            client->message_buffer = JsonMessages::authSuccessful().toJson(QJsonDocument::Compact);
            client->mode = NetWorker::OPERATION_WRITE;

            client->access_level = result;
            __s_renderer->addLog("Player '"+login.toString() +"' join the game");
            //__s_renderer->draw("");
        break;
    }


}
void ServerApp::__logoutClient(struct client_t *client){
    __s_renderer->addLog("Player '"+client->client_login +"' leave the game");
    client->client_worker->closeConnection();
}
void ServerApp::__checkCountPlayers(struct client_t *client){
    client->message_buffer = JsonMessages::checkCountPlayers(__clients->size()).toJson(QJsonDocument::Compact);
    client->mode = NetWorker::OPERATION_WRITE;
}

void ServerApp::__gameStep(){
    if(__s_current_time <= 0){
        if(__game_status == ACTIVE_STAGE){
            __game_status = RESULTS_STAGE;
            __s_current_time = __START_TIMER;
            __timer = "00:00";
        }
        else if(__game_status == RESULTS_STAGE){
            __s_renderer->addLog("Waiting player stage");
            __game_status = WAITING_PLAYER;
            __s_current_time = __START_TIMER;
            __timer = "00:00";
            __last_winner = "";
            //__s_renderer->draw("");
        }
    }

    if(__game_status == WAITING_PLAYER){
        int temp_count = 0;
        //printf("%d ",__clients->size());
        if(__clients->size() > 1){
            for(int i = 0; i < __clients->size(); i++){
                if(__clients->at(i).ready == true){
                    temp_count++;
                }
            }
            if(temp_count == __clients->size()){
                __game_status = ACTIVE_STAGE;
                __s_renderer->addLog("Start 'Active' stage");
                //__s_renderer->draw("");

            }
        }
    }
    else if(__game_status == ACTIVE_STAGE){
        if(__clients->size() > 1){
            for(int i = 0; i < __clients->size();i++){
                if(__clients->at(i).number == -1){
                    return;
                }
            }
            __s_current_time = 0;
            __s_renderer->addLog("Start 'Restult' stage");
            //__s_renderer->draw("");
        }
    }
    else if(__game_status == RESULTS_STAGE){
        //подводим итог

        if(__last_winner != ""){
            return;
        }
        double sum = 0;
        double result = 0;
        int count_current_player = 0;
        for(int i = 0; i < __clients->size(); i++){
            if(__clients->at(i).number != -1){
                sum += __clients->at(i).number;
                count_current_player++;
            }
        }
        result = sum / count_current_player;
        result /= 2.f;

        int winner_pos = 0;
        double min_difference = 101.f, temp_difference;
        for(int i = 0; i < __clients->size(); i++){
            temp_difference = abs(result - (double)__clients->at(i).number);
            if(temp_difference < min_difference){
                min_difference = temp_difference;
                winner_pos = i;
            }
        }

        __last_winner = __clients->at(winner_pos).client_login;
        __s_current_time = __RESULT_TIMER;


        for(int i = 0; i < __clients->size(); i++){
            //(*__clients)[i].number = -1;
            (*__clients)[i].ready = false;
        }

    }

}

void ServerApp::destroy(){
    __close_server = true;
}
