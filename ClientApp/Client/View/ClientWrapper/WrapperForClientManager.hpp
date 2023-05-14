#pragma once

#include <QObject>
#include <qqml.h>
#include "ClientManager.hpp"

class WrapperForClientManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
private:
    ClientManager *__client_manager = nullptr;
public:
    WrapperForClientManager(QObject *parent = nullptr);
    ~WrapperForClientManager();
public slots:
    ClientManager* getClientManager();

};


