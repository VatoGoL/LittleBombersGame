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

#include "NetWorker.hpp"

using namespace std;
struct net_node_t {
    int socket;
    sockaddr_in address;
    socklen_t length_address;

};

class ServerManager{
private:

    net_node_t __node_server;
    int __max_player_count = 0;
    QVector<net_node_t> __node_client;
    net_node_t __temp_client;
    QVector<NetWorker*> __client_worker;
public:
    ServerManager(int max_player_count);
    virtual ~ServerManager();

    void initServer();
    void stepExecute();
    void destroyServer();
};
