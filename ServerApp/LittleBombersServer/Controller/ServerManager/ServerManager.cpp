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
    printf("Socket: %d\n", __node_server.socket);
    __node_server.address.sin_family = AF_INET;
    __node_server.address.sin_addr.s_addr = htonl(INADDR_ANY);
    __node_server.address.sin_port = htons(0);
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

    printf("Server Init Succeful\n");
}
void ServerManager::stepExecute(){
    __temp_client.socket = -1;
    __temp_client.socket = accept(__node_server.socket,(sockaddr*)&__temp_client.address,(socklen_t*)&__temp_client.length_address);
    if(__temp_client.socket != -1 && __node_client.size() <= __max_player_count){
        __node_client.push_back(__temp_client);
        __client_worker.push_back(new NetWorker());
        __client_worker.last()->openConnection(__node_client.last().socket);
    }

    for(int i = 0; i < __client_worker.size(); i++){

    }


}
void ServerManager::destroyServer(){

    close(__node_server.socket);
}
