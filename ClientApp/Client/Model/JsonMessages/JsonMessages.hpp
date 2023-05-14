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
    static QJsonDocument connectToServer(QString login, QString password);
    static QJsonDocument kickPlayer(QString player_login);
    static QJsonDocument closeApplication();
    static QJsonDocument synchronizationQuery(bool player_ready, QString login, QString number);
};
