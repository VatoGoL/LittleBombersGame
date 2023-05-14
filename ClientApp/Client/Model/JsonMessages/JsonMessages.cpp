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
QJsonDocument JsonMessages::connectToServer(QString login, QString password){
    QJsonObject result;
    result["target"] = "login";
    result["login"] = login;
    result["password"] = password;
    return QJsonDocument(result);
}
QJsonDocument JsonMessages::synchronizationQuery(bool player_ready, QString login, QString number){
    QJsonObject result;
    result["target"] = "synchronization";
    result["ready"] = player_ready;
    result["login"] = login;
    result["number"] = number;
    return QJsonDocument(result);
}
