#pragma once
#include <qqml.h>
#include <QDebug>

#include "../../Model/DataBaseManager/DataBaseManager.hpp"
#include "../../Model/TableModel/TableModel.hpp"
#include "../../Controller/ClientManager/ClientManager.hpp"

#define DEF_SIZE_NAME 16.5104
#define DEF_SIZE_IP 14.6354
#define DEF_SIZE_PORT 10.7812
#define DEF_SIZE_PLAYERS_ACTIVE 16.927
#define DB_NAME "ServerList"
#define DB_PATH "DataBase/ServerList.db"


class ServerListt: public QObject
{
    Q_OBJECT
    QML_ELEMENT
private:
    DataBaseManager *__db_manager = nullptr;
    QVector<QString> *__header_data = nullptr;
    QVector<QVector<QVariant>> *__data = nullptr;
    ClientManager *__client_manager;
    QString __error_message;

public:
    ServerListt(QObject *parent = nullptr);
    bool openConnect();
    virtual ~ServerListt();
signals:
    void initTable();

public slots:
    QVector<QString>* parseHeaderData();
    QVector<QVector<QVariant>>* parseData();

    QString getHeaderData(int column);
    QString getData(int row,int column);

    bool insertRowData(QString name, QString ip, QString port);
    bool deleteRowData(int row);
    void setNetManager(ClientManager *client_manager);
    bool closeConnection();
    QString getErrorMessage();

    bool loginServer(QString ip, QString port, QString login, QString password);
};

