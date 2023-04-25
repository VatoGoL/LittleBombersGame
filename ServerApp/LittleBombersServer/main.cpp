#include <QCoreApplication>
#include "ServerApp.hpp"
#include "Model/NetWorker/NetWorker.hpp"
int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    printf("\nStart\n");
    ServerApp *application = new ServerApp();
    //NetWorker *a = new NetWorker;
    //a->execute();
    application->execute();
    //stdin
    //return a.exec();
}
