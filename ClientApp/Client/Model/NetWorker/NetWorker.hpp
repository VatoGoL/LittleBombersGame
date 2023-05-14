#pragma once

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <QByteArray>
#include <QDebug>


class NetWorker
{

public:
    const QByteArray M_END_MESSAGE = "-1end";
    const QByteArray M_CLOSE_CONNECTION = "\"target\":\"close_connection\"";

    enum OPERATION_MODE{
        OPERATION_NONE = -1,
        OPERATION_READ,
        OPERATION_WRITE
    };

    NetWorker();
    virtual ~NetWorker();
    bool openConnection(int client_socket);

    void setMessage(QByteArray message);
    void getMessage(QByteArray *message);

    void setWorkingMode(OPERATION_MODE mode);
    void getWorkingMode(OPERATION_MODE *mode);

    void closeConnection();
    void isAliveConnection(bool *status_connection);
private:

    struct __net_worket_info_t{
        NetWorker *object;
        pthread_mutex_t *mutex;
        QByteArray *message;
        QByteArray *buffer_message;
        OPERATION_MODE *operation;
        OPERATION_MODE *buffer_operation;
        bool *status_connection;
        bool *buffer_status_connection;
        int *socket;
    };

    int __socket;

    pthread_mutex_t *__mutex = nullptr;

    QByteArray __message;
    QByteArray __buffer_message;

    OPERATION_MODE __operation = OPERATION_NONE;
    OPERATION_MODE __buffer_operation = OPERATION_NONE;

    bool __status_connection;
    bool __buffer_status_connection;

    int RECIVE_BUFFER_SIZE = (1 << 10);

    __net_worket_info_t __thread_arguments;
    pthread_t __thread_id;

    //Помещается в поток
    static void* __execute(void *value);
    void __sendMessage();
    void __reciveMessage();
};


