#pragma once
#include <stdio.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <QString>

#include "../../Model/NetWorker/NetWorker.hpp"
#include "../../Model/JsonMessages/JsonMessages.hpp"

#define DEF_ADDRESS "127.0.0.2"

struct net_node_t {
    int socket = -1;
    sockaddr_in address;
    socklen_t length_address = sizeof(address);
};

class ClientManager
{

private:
    net_node_t __client;
    QString __login, __password;

    net_node_t __server;
    struct hostent *__server_info;
    NetWorker __server_worker;

    QByteArray __message_buffer;
    NetWorker::OPERATION_MODE __mode = NetWorker::OPERATION_NONE;
public:
    ClientManager();
    ~ClientManager();

    void init();
    bool connectToServer(QString ip, QString port);
    void closeConnection();
    void setOperationMode(NetWorker::OPERATION_MODE mode);

    void stepExecute();

    void loginOnServer(QString login, QString password);
    void logoutIsServer();
    void synchronization(bool player_ready, QString login, QString number);

    void setClient(net_node_t client);
    net_node_t getClient();

    QByteArray getMessageBuffer();

    ClientManager& operator=(const ClientManager &right);
};
