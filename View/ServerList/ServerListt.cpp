#include "ServerListt.hpp"

ServerListt::ServerListt(QObject *parent): QObject(parent)
{
    __db_manager = new DataBaseManager(DB_PATH);
}

ServerListt::~ServerListt()
{
    if(__db_manager != nullptr){
        delete __db_manager;
    }
}
QVector<QString>* ServerListt::parseHeaderData(){
    if(!openConnect()){
        return (new QVector<QString>());
    }

    QString query = QString("PRAGMA table_info(%1)").arg(DB_NAME);
    QSqlQuery reply = __db_manager->runQuery(query);
    if(!reply.isActive()){
        qDebug() << "Query not valid";
        return (new QVector<QString>());
    }
    if(__header_data != nullptr){
        delete __header_data;
    }

    __header_data = new QVector<QString>();

    reply.next();
    for(int i = 0; reply.next(); i++){
        QString temp;

        temp = reply.value("name").toString();
        __header_data->push_back(temp);
    }


    return __header_data;
}
QVector<QVector<QVariant>>* ServerListt::parseData(){
    //QString query = "SELECT * FROM " + DB_NAME;
    if(!openConnect()){
        return (new QVector<QVector<QVariant>>());
    }

    QString query = QString("SELECT * FROM ") + DB_NAME;
    QSqlQuery reply = __db_manager->runQuery(query);
    if(!reply.isActive()){
        qDebug() << "Query not valid";
        return (new QVector<QVector<QVariant>>());
    }
    if(__data != nullptr){
        delete __data;
    }
    __data = new QVector<QVector<QVariant>>();


    for(int i = 0; reply.next(); i++){
        QVector<QVariant> temp;
        temp.push_back(reply.value("ip"));
        temp.push_back(reply.value("port"));
        temp.push_back(reply.value("name"));
        __data->push_back(temp);
    }

    return __data;
}
bool ServerListt::openConnect(){
    if(__db_manager->isOpenConnection()){
        qDebug() << "Connection open!!!";
        return true;
    }

    if(!__db_manager->openConnect(true)){
        qDebug() << "Connection not open";
        return false;
    }
    qDebug() << "Connection R open!!!";
    return true;
}
