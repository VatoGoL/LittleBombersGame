#pragma once

#include <QtSql/QSqlDatabase>
//#include <QSqlDatabase>
//#include <QSqlQuery>
#include <QtSql/QSqlQuery>

class DataBaseManager{

private:
    QSqlDatabase *__db_connection = nullptr;
    QString __db_name = "";
    const QString __db_type = "QSQLITE";

    QSqlQuery *__query = nullptr;
public:
    DataBaseManager(QString data_base_name = "");
    virtual ~DataBaseManager();

    void setDBName(QString data_base_name);
    QString getDBName();

    bool openConnect(bool forward_only = false);
    bool isOpenConnection();
    QSqlQuery runQuery(QString value);

};
