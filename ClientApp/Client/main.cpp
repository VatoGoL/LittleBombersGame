#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Model/TableModel/TableModel.hpp"
#include <ServerListt.hpp>
#include "View/ClientWrapper/WrapperForClientManager.hpp"
#include "View/GameScreen/GameScreenHarvard.hpp"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<TableModel>("DataBaseModel", 1, 0, "DataBaseModel");
    qmlRegisterType<ServerListt>("ViewServerList", 1, 0, "ViewServerList");
    qmlRegisterType<WrapperForClientManager>("ClientWrapper", 1, 0, "ClientWrapper");
    qmlRegisterType<GameScreenHarvard>("GameHarvard", 1, 0, "GameHarvard");
    const QUrl url(u"qrc:/LittleBombers/Main.qml"_qs);
    //const QUrl url(u"qrc:/LittleBombers/View/ServerList/ServerList.qml"_qs);
    //const QUrl url(u"qrc:/LittleBombers/View/GameScreen/GameScreenHarvard.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
