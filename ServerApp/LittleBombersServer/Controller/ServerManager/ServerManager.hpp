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
#include <QString>
#include <QVector>
#include <QJsonDocument>
#include <QJsonArray>
#include <string>
#include "Controller_DB_Manager.hpp"

#include "NetWorker.hpp"

#define MAP_IP "IP"
#define MAP_PORT "Port"

using namespace std;
struct net_node_t {
    int socket;
    sockaddr_in address;
    socklen_t length_address;
};
struct client_t{
    net_node_t node_client;
    NetWorker *client_worker;
    QString client_login;
    QByteArray message_buffer;
    NetWorker::OPERATION_MODE mode = NetWorker::OPERATION_NONE;
    Controller_DB_Manager::ACCESS_LEVEL access_level = Controller_DB_Manager::ACCESS_STANDART_PLAYER;

    int number = -1;
    bool ready = false;
};
struct accept_info_t{
    QVector<client_t>* clients;
    bool *finish_accept;
    pthread_mutex_t *mutex;
    net_node_t server;
    int max_player_count;
};

class ServerManager{
private:

    net_node_t __node_server;
    int __max_player_count = 4;

    QVector<NetWorker*> __client_worker;
    QVector<QString> __client_login;
    QVector<net_node_t> __node_client;

    QVector<client_t> __clients;
    QByteArray __command;
    bool __client_status_connection;

    pthread_t __accept_worker;
    pthread_mutex_t __mutex;
    accept_info_t __accept_arg;
    bool __finish_accept = false;
    static void* __acceptConnection(void* value);
public:
    ServerManager(int max_player_count);
    virtual ~ServerManager();

    void initServer();
    void stepExecute();
    QVector<client_t>* getClients();
    QMap<QString,QString> getIpAndPort();
    void destroyServer();

};
