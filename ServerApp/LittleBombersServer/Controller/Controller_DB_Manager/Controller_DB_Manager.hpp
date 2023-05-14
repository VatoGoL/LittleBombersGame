#pragma once

#include "DataBaseManager.hpp"
#include <QJsonValue>

class Controller_DB_Manager
{
private:
    const QString DB_NAME = "Users";
    const QString DB_PATH = "DataBase/Users.db";

    DataBaseManager *__db_manager = nullptr;

    bool __openConnection();
public:
    enum ACCESS_LEVEL{
        ACCESS_ERROR = -1,
        ACCESS_STANDART_PLAYER,
        ACCESS_MODERATION_PLAYER
    };

    Controller_DB_Manager();
    virtual ~Controller_DB_Manager();


    ACCESS_LEVEL connectPlayer(QJsonValue login, QJsonValue password, QString *message);
    bool changeAccessLevel(QJsonValue login, ACCESS_LEVEL access_level);

};
