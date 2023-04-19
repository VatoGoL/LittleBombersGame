#include "ServerListt.hpp"

ServerListt::ServerListt(QObject *parent): QObject(parent)
{
    __db_manager = new DataBaseManager(DB_PATH);
    emit initTable();
}

ServerListt::~ServerListt()
{
    if(__db_manager != nullptr){
        delete __db_manager;
    }
}
QVector<QMap<int,QString>> ServerListt::parseHeaderData(){
    if(!openConnect()){
        return new QVector<QMap<int,QString>>();
    }

    QString query = QString("PRAGMA table_info(%1)").arg(DB_NAME);
    QSqlQuery reply = __db_manager->runQuery(query);
    if(!reply.isActive()){
        qDebug() << "Query not valid";
        return new QVector<QMap<int,QString>>();
    }

    //QVector<QMap<int,QString>>* result = new QVector<QMap<int,QString>>();
    QVector<QMap<int,QString>> result;
    /*reply.next();
    for(int i = 0; reply.next(); i++){
        QMap<int,QString> temp;
        temp[i] = reply.value("name").toString();
        result->push_back(temp);
    }*/
    QMap<int,QString> temp;
    QMap<int,QString> temp_1;
    QMap<int,QString> temp_2;
    temp[0] = "AAA";
    temp_1[1] = "sss";
    result.push_back(temp);
       result.push_back(temp_1);


    return result;
}
QVector<QVector<QVariant>> ServerListt::parseData(){
    //QString query = "SELECT * FROM " + DB_NAME;
    if(!openConnect()){
        return new QVector<QVector<QVariant>>();
    }

    QString query = QString("SELECT * FROM ") + DB_NAME;
    QSqlQuery reply = __db_manager->runQuery(query);
    if(!reply.isActive()){
        qDebug() << "Query not valid";
        return new QVector<QVector<QVariant>>();
    }

    //QVector<QVector<QVariant>> *result = new QVector<QVector<QVariant>>();
    QVector<QVector<QVariant>> result;
    /*reply.next();
    for(int i = 0; reply.next(); i++){
        QVector<QVariant> temp;
        temp.push_back(reply.value("ip"));
        temp.push_back(reply.value("port"));
        temp.push_back(reply.value("name"));
        result->push_back(temp);
    }
    */
    result.push_back({"aaa","aaaa","asds"});
    result.push_back({"aaa","aaaa","asdss"});
    result.push_back({"aaa","aaaa","s"});
    return result;
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
    qDebug() << "Connection open!!!";
    return true;
}
