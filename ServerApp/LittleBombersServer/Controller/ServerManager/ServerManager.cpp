#include "ServerManager.hpp"

ServerManager::ServerManager(int max_player_count){
    __max_player_count = max_player_count;
}
ServerManager::~ServerManager(){
    destroyServer();
}

void ServerManager::initServer(){

    if((__node_server.socket = socket(AF_INET,SOCK_STREAM, 0)) < 0){
        perror("Error init server socket\n");
        return;
    }
    //printf("Socket: %d\n", __node_server.socket);
    __node_server.address.sin_family = AF_INET;
    __node_server.address.sin_addr.s_addr = htonl(INADDR_ANY);
    //inet_aton("127.0.0.1",&__node_server.address.sin_addr);
    __node_server.address.sin_port = 0;
    __node_server.length_address = sizeof(__node_server.address);
    if(bind(__node_server.socket, (sockaddr*)&__node_server.address, __node_server.length_address)){
        perror("Error bind server");
        return;
    }

    if(getsockname(__node_server.socket,(sockaddr*)&__node_server.address,(socklen_t*)&__node_server.length_address)){
        perror("Error getsockname");
        return;
    }
    if(listen(__node_server.socket,__max_player_count)){
        perror("Listen error");
        return;
    }

    __accept_arg.clients = &__clients;
    __accept_arg.max_player_count = __max_player_count;
    __accept_arg.mutex = &__mutex;
    __accept_arg.server = __node_server;
    __accept_arg.finish_accept = &__finish_accept;

    pthread_mutex_init(&__mutex,nullptr);
    pthread_create(&__accept_worker,nullptr,__acceptConnection,(void *)&__accept_arg);
    pthread_detach(__accept_worker);

    //printf("Server Init Succeful\n");
}
void ServerManager::stepExecute(){
    NetWorker::OPERATION_MODE operation;
    int delete_position = -1;


    pthread_mutex_lock(&__mutex);
    for(int i = 0; i < __clients.size(); i++){

        __clients[i].client_worker->getWorkingMode(&operation);

        if(__clients[i].mode == NetWorker::OPERATION_WRITE){
            __clients[i].client_worker->setMessage(__clients[i].message_buffer);
            __clients[i].client_worker->setWorkingMode(__clients[i].mode);
            __clients[i].message_buffer = "";
            __clients[i].mode = NetWorker::OPERATION_READ;
        }
        else if(operation == NetWorker::OPERATION_NONE){
            __clients[i].client_worker->getMessage(&__clients[i].message_buffer);
//            __clients[i].client_worker->isAliveConnection(&__client_status_connection);
  //          if(!__client_status_connection){
    //            delete_position = i;
      //      }

            __clients[i].client_worker->setWorkingMode(__clients[i].mode);
            __clients[i].mode = NetWorker::OPERATION_NONE;
        }

        __clients[i].client_worker->isAliveConnection(&__client_status_connection);
        if(!__client_status_connection){
            delete_position = i;
        }

        if(__clients[i].access_level == Controller_DB_Manager::ACCESS_ERROR){
            __clients[i].client_worker->closeConnection();
        }
    }

    //неправильное удаление, но так как мы по 1 чаще всего будем удалять всё должно работать
    if(delete_position != -1){
        __clients.removeAt(delete_position);
    }

    pthread_mutex_unlock(&__mutex);
    usleep(100);
}
void* ServerManager::__acceptConnection(void* value){

    net_node_t __temp_node_client;
    accept_info_t *argument = (accept_info_t*) value;
    bool exit = false;
    __temp_node_client.socket = -1;
    for(;!exit;){
        __temp_node_client.socket = accept(argument->server.socket,(sockaddr*)&__temp_node_client.address,(socklen_t*)&__temp_node_client.length_address);

        pthread_mutex_lock(argument->mutex);
        if(__temp_node_client.socket != -1 && argument->clients->size() <= argument->max_player_count){
            client_t temp_client;
            temp_client.node_client = __temp_node_client;
            temp_client.client_worker = new NetWorker();
            temp_client.client_login = "";

            argument->clients->push_back(temp_client);

            argument->clients->last().client_worker->openConnection(argument->clients->last().node_client.socket);
            argument->clients->last().client_worker->setWorkingMode(NetWorker::OPERATION_READ);

            __temp_node_client.socket = -1;
        }
        if(*argument->finish_accept){
            exit = true;
        }
        pthread_mutex_unlock(argument->mutex);
    }
    pthread_exit(nullptr);
}

QVector<client_t>* ServerManager::getClients(){
    return &__clients;
}
QMap<QString,QString> ServerManager::getIpAndPort(){
    QMap<QString,QString> result;
    result["IP"] = QString(inet_ntoa(__node_server.address.sin_addr));
    result["Port"] = QString().setNum(ntohs(__node_server.address.sin_port),10);
    return result;
}
void ServerManager::destroyServer(){
    __finish_accept = true;
    close(__node_server.socket);
}
