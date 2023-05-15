#include "JsonMessages.hpp"

JsonMessages::JsonMessages()
{

}
QJsonDocument JsonMessages::authSuccessful(){
    QJsonObject result;
    result["target"] = "connection_confirm";
    result["status"] = "successful";
    return QJsonDocument(result);
}
QJsonDocument JsonMessages::authFailed(){
    QJsonObject result;
    result["target"] = "connection_confirm";
    result["status"] = "failed";
    return QJsonDocument(result);
}
QJsonDocument JsonMessages::logout(){
    QJsonObject result;
    result["target"] = "logout";
    return QJsonDocument(result);
}
QJsonDocument JsonMessages::checkCountPlayers(int count_players){
    QJsonObject result;
    result["target"] = "check_count_players";
    result["count"] = QString().setNum(count_players);
    return QJsonDocument(result);
}
QJsonDocument JsonMessages::closeApplication(){
    QJsonObject result;
    result["target"] = "close_server";
    return QJsonDocument(result);
}
QJsonDocument JsonMessages::kickPlayer(QString player_login){
    QJsonObject result;
    result["target"] = "kick_player";
    result["login"] = player_login;
    return QJsonDocument(result);
}
QJsonDocument JsonMessages::changeAccessMode(QString login, Controller_DB_Manager::ACCESS_LEVEL level){
    QJsonObject result;
    result["target"] = "change_access_level";
    result["login"] = login;
    result["access_level"] = (int)level;
    return QJsonDocument(result);
}
QJsonDocument JsonMessages::synchronizationReply(int status_game, QVector<QString> player_logins,
                                                 QVector<QString> player_numbers, QString last_winner,
                                                 QString time)
{
    QJsonArray array_number, array_logins;
    QJsonObject result;

    result["target"] = "synchronization";
    result["status_game"] = QString().setNum(status_game);

    for(size_t i = 0; i < player_logins.size(); i++){
        array_logins.push_back(QJsonValue(player_logins[i]));
    }
    result["player_logins"] = array_logins;

    for(size_t i = 0; i < player_numbers.size(); i++){
        array_number.push_back(QJsonValue(player_numbers[i]));
    }
    result["player_numbers"] = array_number;

    result["winner"] = last_winner;
    result["time"] = time;

    return QJsonDocument(result);
}
