#pragma once

#include <stdio.h>
#include <unistd.h>
#include <QByteArray>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


#include "ServerRenderer.hpp"
#include "ServerManager.hpp"

struct key_info_t{
    pthread_mutex_t *mutex;
    bool *key_read;
    QByteArray *key_buffer;
};

class ServerApp
{
private:
    pthread_t __key_input_id;
    pthread_mutex_t __key_mutex;
    key_info_t __thread_arguments;
    QByteArray __key_buffer;
    QByteArray __key_command;
    bool __key_read = true;

    ServerRenderer *__s_renderer = nullptr;

    const int __MAX_PLAYER_COUNT = 4;
    ServerManager *__s_manager = nullptr;

    static void* __keyReader(void *value);
public:
    static const int SIZE_TEMP_KEY_BUFFER = 10;

    ServerApp();
    ~ServerApp();

    void execute();

    void init();
    void destroy();

};

//const int ServerApp::SIZE_TEMP_KEY_BUFFER = 10;
