#pragma once
#include <stdio.h>
#include <QByteArray>
#include <QVector>
//#include "NetWorker.hpp"
#include "ServerManager.hpp"
#include "JsonMessages.hpp"
#include <wchar.h>

#define NO_CHANGE_SCREEN "no_change_screen";
enum STATUS_GAME{
    ERROR = 0,
    WAITING_PLAYER,
    ACTIVE_STAGE,
    RESULTS_STAGE
};

struct size_view_box{
    int x;
    int y;
    int width;
    int height;
};

class ServerRenderer
{
private:

    const QString __MAIN_SCREEN = "main";
    const QString __PLAYER_LIST_SCREEN = "player_list";
    const QString __ACCESS_MODE_CHANGE_SCREEN = "access_mode_change";
    const QString __KICK_PLAYER_SCREEN = "kick_player";
    const int __LOG_HISTORY_MAX = 3;
    const QString __FIELD_1 = "1";
    const QString __FIELD_2 = "2";
    const QString __FIELD_3 = "3";
    const QString __FIELD_4 = "4";
    const QString __FIELD_5 = "5";
    //__table_symbols:
    //
    //    '\u250c', // ┌ 0
    //    '\u2510', // ┐ 1
    //    '\u2518', // ┘ 2
    //    '\u2514', // └ 3
    //    '\u2534', // ┴ 4
    //    '\u252c', // ┬ 5
    //    '\u251c', // ├ 6
    //    '\u2500', // ─ 7
    //    '\u253c', // ┼ 8
    //    '\u2524', // ┤ 9
    //    '\u2502' // │ 10


    enum TERMINAL_COLOR{
        BLACK = 1,
        RED,
        BLUE,
        YELLOW,
        WHITE
    };

    QString __screen = __MAIN_SCREEN;
    QString __ip = "", __port = "";
    QVector<QString> __log_history;
    QVector<client_t> *__players;
    QString *__time;
    STATUS_GAME *__status_game;
    bool __select_field_mode = true;
    int __width;
    struct size_view_box __title_box;
    struct size_view_box __screen_box;
    struct size_view_box __input_box;
    struct size_view_box __log_box;

    QJsonDocument __command_buffer;

    void __drawTitle();
    void __drawScreen();
    void __drawInputField();
    void __drawLog();
    void __drawRectangle(int x, int y, int width, int height);

    void __drawPlayerList();

    //void __setScreen(QString screen);

    void __execCommand(QByteArray command);
    void __setFGColor(TERMINAL_COLOR color);
    void __setBGColor(TERMINAL_COLOR color);
    void __clearScreen();
    void __setCarriagePos(int x, int y);


public:
    ServerRenderer();

    void addLog(QString log);
    void init(QVector<struct client_t> *players, QString ip, QString port, QString *time, STATUS_GAME *status_game, int width = 80);
    void draw(QByteArray command);
    QJsonDocument getCommand();
};
