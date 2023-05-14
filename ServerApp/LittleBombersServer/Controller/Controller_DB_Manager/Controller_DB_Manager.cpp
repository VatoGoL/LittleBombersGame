#include "Controller_DB_Manager.hpp"
#include <unistd.h>
Controller_DB_Manager::Controller_DB_Manager()
{
    __db_manager = new DataBaseManager(DB_PATH);
    __db_manager->openConnect(true);
}

Controller_DB_Manager::~Controller_DB_Manager(){
    delete __db_manager;
}

bool Controller_DB_Manager::__openConnection(){
    if(!__db_manager->isOpenConnection()){
        return __db_manager->openConnect();
    }
    return true;
}

Controller_DB_Manager::ACCESS_LEVEL Controller_DB_Manager::connectPlayer(QJsonValue login, QJsonValue password, QString *message){
    if(!__openConnection()){
        *message = "connection open failed";
        return ACCESS_ERROR;
    }

    QString query = "SELECT login, password, access_level FROM users WHERE login = '" + login.toString() + "';";
    QSqlQuery result = __db_manager->runQuery(query);

    //создаём нового пользователя

    if(!result.next()){
        query = "INSERT INTO users (login, password, access_level) VALUES ('" + login.toString()
                                                                              + "', '"
                                                                              + password.toString()
                                                                              + "', "
                                                                              + QString().setNum(ACCESS_STANDART_PLAYER)
                                                                              + ");";
        result = __db_manager->runQuery(query);
        if(!result.isActive()){
            return ACCESS_ERROR;
        }
        return ACCESS_STANDART_PLAYER;
    }

    //result.next();
    if(result.value("password").toString() != password.toString()){
        return ACCESS_ERROR;
    }

    return (ACCESS_LEVEL)result.value("access_level").toInt();
}

bool Controller_DB_Manager::changeAccessLevel(QJsonValue login, ACCESS_LEVEL access_level){

    if(!__openConnection()){
        return false;
    }

    QString query = "UPDATE users SET access_level = " + QString().setNum(access_level)
                                                       + " WHERE login = '"
                                                       + login.toString()
                                                       + "';";
    QSqlQuery result = __db_manager->runQuery(query);
    if(!result.isActive()){
        return false;
    }

    return true;
}
