#pragma once

#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>

class JsonMessages
{
public:
    JsonMessages();

    static QJsonDocument authSuccessful();
    static QJsonDocument authFailed();
    static QJsonDocument logout();
    static QJsonDocument checkCountPlayers(int count_players);
    static QJsonDocument kickPlayer(QString player_login);
    static QJsonDocument closeApplication();
    static QJsonDocument synchronizationReply(int status_game, QVector<QString> player_logins,
                                              QVector<QString> player_numbers, QString last_winner,
                                              QString time);
};
