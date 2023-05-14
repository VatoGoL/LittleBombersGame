#pragma once

#include <qqml.h>
#include <QDebug>
#include <QTimer>
#include "../../Controller/ClientManager/ClientManager.hpp"


class GameScreenHarvard: public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    GameScreenHarvard(QObject *parent = nullptr);
    virtual ~GameScreenHarvard();

    enum STATUS_GAME{
        ERROR = 0,
        WAITING_PLAYER,
        ACTIVE_STAGE,
        RESULTS_STAGE
    };
private slots:
    void __synchronization();

public slots:
    void setNetManager(ClientManager *client_manager);

    void leaveTheGame();


    void setNumber(QString number);
    void setName(QString name);
    void setPlayerReady(bool ready);

    int getCountPlayer();
    QString getName();
    int getNumber();
    QString getEnemyName(int num_player);
    QString getEnemyNumber(int num_player);
    int getStatusGame();
    QString getLastWinner();
    QString getTime();
signals:
    void countPlayerChanget();
    void stageGameChanget();
    void kickFromServer();
private:
    QTimer *__timer = nullptr;
    pthread_mutex_t __mutex;
    ClientManager *__client_manager;
    int __count_player = 1;
    STATUS_GAME __status_game = ERROR;

    QString __name = "";
    int __number = -1;
    bool __player_ready = false;
    QVector<QString> __enemy_name;
    QVector<QString> __enemy_number;
    QString __last_winner = "";
    QString __time = "00:00";
};

