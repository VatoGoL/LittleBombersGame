#include "ClientManager.hpp"

ClientManager::ClientManager()
{
    init();
}
ClientManager::~ClientManager()
{

}
void ClientManager::init(){
    if(__client.socket != -1){
        qDebug()<< "__client.socket" << __client.socket;
        return;
    }

    if((__client.socket = socket(AF_INET, SOCK_STREAM,0)) < 0){
        perror("Client He могу получить socket\n");
        return;
    }
    __client.address.sin_family = AF_INET;
    if(!inet_aton(DEF_ADDRESS,&__client.address.sin_addr)){
        perror("Не получиось установить клиенту ip");
        return;
    }
    __client.address.sin_port = 0;
}
bool ClientManager::connectToServer(QString ip, QString port){
    __server_info = gethostbyname(ip.toStdString().c_str());
    memcpy(__server_info->h_addr, &__server.address.sin_addr,__server.length_address);

    __server.address.sin_port = htons(port.toInt());
    __server.address.sin_family = AF_INET;

    if(connect(__client.socket,(sockaddr*)&__server.address, __server.length_address)){
        perror("Клиент не может nnnnnсоединиться.");
        return false;
    }

    if(!__server_worker.openConnection(__client.socket)){
        return false;
    }
    return true;
}

void ClientManager::setOperationMode(NetWorker::OPERATION_MODE mode){
    if(__mode == NetWorker::OPERATION_NONE){
        __mode = mode;
    }

}

void ClientManager::stepExecute(){
    NetWorker::OPERATION_MODE operation;
    bool status_connection;

    __server_worker.getWorkingMode(&operation);

    if(operation == NetWorker::OPERATION_NONE){
        if(__mode == NetWorker::OPERATION_WRITE){
            __server_worker.setMessage(__message_buffer);
            __message_buffer = "";
            __server_worker.setWorkingMode(__mode);

            __mode = NetWorker::OPERATION_NONE;
        }
        else{
            __server_worker.getMessage(&__message_buffer);
            __server_worker.isAliveConnection(&status_connection);
            __server_worker.setWorkingMode(__mode);

            __mode = NetWorker::OPERATION_NONE;
        }
    }


    usleep(100);


}

QByteArray ClientManager::getMessageBuffer(){
    return __message_buffer;
}

void ClientManager::loginOnServer(QString login, QString password){
    __login = login;
    __password = password;

    __message_buffer = JsonMessages::connectToServer(__login,__password).toJson(QJsonDocument::Compact);
    __mode = NetWorker::OPERATION_WRITE;
    stepExecute();
}

void ClientManager::logoutIsServer(){
    __message_buffer = JsonMessages::logout().toJson(QJsonDocument::Compact);
    __mode = NetWorker::OPERATION_WRITE;
    stepExecute();

    closeConnection();
}

void ClientManager::synchronization(bool player_ready, QString login, QString number){
    __message_buffer = JsonMessages::synchronizationQuery(player_ready,login,number).toJson(QJsonDocument::Compact);
    __mode = NetWorker::OPERATION_WRITE;
    stepExecute();
}

void ClientManager::setClient(net_node_t client){
    if(__client.socket != -1){
        close(__client.socket);
    }
    __client = client;
}
net_node_t ClientManager::getClient(){
    return __client;
}
ClientManager& ClientManager::operator=(const ClientManager &right){
    if(this == &right){
        return *this;
    }
    this->setClient(right.__client);
    return *this;
}
void ClientManager::closeConnection(){
    __server_worker.closeConnection();
    close(__client.socket);
    close(__server.socket);
    __client.socket = -1;
    init();
}
