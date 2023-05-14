#pragma once

#include <stdio.h>
#include <unistd.h>
#include <QByteArray>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <chrono>

#include "ServerRenderer.hpp"
#include "ServerManager.hpp"
#include "Controller_DB_Manager.hpp"
#include "JsonMessages.hpp"

using namespace std;
using namespace std::chrono;

#define DEF_WIDTH 80

struct key_info_t{
    pthread_mutex_t *mutex;
    bool *key_read;
    QByteArray *key_buffer;
    bool *skip_step;
};

class ServerApp
{
private:



    int __width_application;

    pthread_t __key_input_id;
    pthread_mutex_t __key_mutex;
    key_info_t __thread_arguments;
    QByteArray __key_buffer;
    QByteArray __key_command;
    bool __skip_step = false;
    bool __key_read = true;

    const int __MAX_PLAYER_COUNT = 4;
    ServerManager *__s_manager = nullptr;
    QMap<QString,QString> __s_ip_and_port;
    QVector<struct client_t> *__clients;

    ServerRenderer *__s_renderer = nullptr;
    Controller_DB_Manager *__controller_db_manager = nullptr;

    QJsonDocument __message_from_view;

    bool __close_server = false;

    //GameStatus
    const int __START_TIMER = 30;
    const int __RESULT_TIMER = 5;
    STATUS_GAME __game_status = WAITING_PLAYER;
    QString __last_winner = "";
    std::chrono::steady_clock::time_point __last_time = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point __temp_time;
    int __s_current_time = __START_TIMER;
    QString __timer = "00:00";


    static void* __keyReader(void *value);

    void __commandProcessing();
    void __autorization(struct client_t *client, QJsonDocument document);
    void __logoutClient(struct client_t *client);
    void __checkCountPlayers(struct client_t *client);
    void __synchronization(struct client_t *client, QJsonDocument document);
    void __gameStep();
public:
    static const int SIZE_TEMP_KEY_BUFFER = 10;

    ServerApp(int width = DEF_WIDTH);
    ~ServerApp();

    void execute();

    void init();
    void destroy();

};

//const int ServerApp::SIZE_TEMP_KEY_BUFFER = 10;
