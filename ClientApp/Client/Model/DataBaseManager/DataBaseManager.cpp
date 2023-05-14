#include "DataBaseManager.hpp"
#include "unistd.h"
DataBaseManager::DataBaseManager(QString data_base_name){
    __db_name = data_base_name;
}
DataBaseManager::~DataBaseManager(){
    if(__db_connection != nullptr){
        __db_connection->close();
        delete __db_connection;
    }
    if(__query != nullptr){
        delete __query;
    }
}

void DataBaseManager::setDBName(QString data_base_name){
    __db_name = data_base_name;
}
QString DataBaseManager::getDBName(){
    return __db_name;
}

bool DataBaseManager::openConnect(bool forward_only){
    if(__db_name == ""){
        return false;
    }

    __db_connection = new QSqlDatabase(QSqlDatabase::addDatabase(__db_type));
    __db_connection->setDatabaseName(__db_name);

    __db_connection->open();
    if(!__db_connection->isOpen()){
        delete __db_connection;
        return false;
    }
    __query = new QSqlQuery(*__db_connection);
    __query->setForwardOnly(forward_only);

    return true;
}
bool DataBaseManager::isOpenConnection(){
    if(__db_connection == nullptr){
        return false;
    }
    return __db_connection->isOpen();
}
bool DataBaseManager::closeConnection(){
    if(__db_connection == nullptr){
        return true;
    }
    __db_connection->close();
}

QSqlQuery DataBaseManager::runQuery(QString value){
    if(__query->exec(value)){
        return *__query;
    }
    return QSqlQuery();
}
