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
        qDebug() << "Query not active";
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
    __header_data->push_back("count_players");

    return __header_data;
}
QVector<QVector<QVariant>>* ServerListt::parseData(){

    if(!openConnect()){
        return (new QVector<QVector<QVariant>>());
    }

    QString query = QString("SELECT * FROM ") + DB_NAME;
    QSqlQuery reply = __db_manager->runQuery(query);
    if(!reply.isActive()){
        qDebug() << "Query not active";
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
        temp.push_back("");
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
QString ServerListt::getHeaderData(int column){
    if(__header_data == nullptr){
        return QString("");
    }
    if(column >= __header_data->size() || column < 0){
        return QString("");
    }
    return __header_data->at(column);
}
QString ServerListt::getData(int row,int column){
    if(__data == nullptr){
        return QString("");
    }
    if(row >= __data->size() || row < 0){
        return QString("");
    }
    if(column >= __data->at(row).size() || column < 0){
        return QString("");
    }
    return __data->at(row).at(column).toString();
}
bool ServerListt::insertRowData(QString name, QString ip, QString port){
    if(!openConnect() || name == "" || ip == "" || port == ""){
        qDebug() << "name = " << name << " ip = " << ip << " port = " << port;
        return false;
    }
    QString query = QString("INSERT INTO ") + DB_NAME +" (name,ip,port) VALUES ( "
                    + "'" + name + "' , "
                    + "'" + ip + "' , "
                    + "'" + port + "' );";
    //qDebug() << query;
    QSqlQuery reply = __db_manager->runQuery(query);

    if(!reply.isActive()){
        qDebug() << "InsertRowData: Data not insert";
        return false;
    }

    QVector<QVariant> temp;
    temp.push_back(ip);
    temp.push_back(port);
    temp.push_back(name);
    temp.push_back("");
    __data->push_back(temp);
    return true;
}
bool ServerListt::deleteRowData(int row){
    if(!openConnect() || row >= __data->size() || row < 0){
        return false;
    }
    QString query = QString("DELETE FROM ") + DB_NAME + " WHERE " +
                    "name = '" + __data->at(row).at(POS_S_NAME).toString() + "' AND " +
                    "ip = '" + __data->at(row).at(POS_S_IP).toString() + "' AND " +
                    "port = '" + __data->at(row).at(POS_S_PORT).toString() + "';";
    QSqlQuery reply = __db_manager->runQuery(query);
    if(!reply.isActive()){
        qDebug() << "deleteRowData: Data not delete";
        return false;
    }

    return true;
}
bool ServerListt::closeConnection(){
    if(__db_manager == nullptr){
        return false;
    }
    return __db_manager->closeConnection();
}

