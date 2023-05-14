#include "WrapperForClientManager.hpp"

WrapperForClientManager::WrapperForClientManager(QObject *parent)
    : QObject{parent}
{
    __client_manager = new ClientManager();
}
WrapperForClientManager::~WrapperForClientManager(){
    delete __client_manager;
}
ClientManager* WrapperForClientManager::getClientManager(){
    return __client_manager;
}
