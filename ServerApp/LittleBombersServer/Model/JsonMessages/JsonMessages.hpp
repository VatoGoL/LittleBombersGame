#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
//#include "Controller/Controller_DB_Manager/Controller_DB_Manager.hpp"
#include "Controller_DB_Manager.hpp"
class JsonMessages
{
public:
    JsonMessages();

    static QJsonDocument authSuccessful();
    static QJsonDocument authFailed();
    static QJsonDocument logout();
    static QJsonDocument checkCountPlayers(int count_players);
    static QJsonDocument kickPlayer(QString player_login);
    static QJsonDocument changeAccessMode(QString login,Controller_DB_Manager::ACCESS_LEVEL level);
    static QJsonDocument closeApplication();
    static QJsonDocument synchronizationReply(int status_game, QVector<QString> player_logins,
                                              QVector<QString> player_numbers, QString last_winner,
                                              QString time);
};
