#include <QtCore/QCoreApplication>
#include "SDK/Network/Server.h"
#include "SDK/Singleton/Singleton.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    TCPServer* lServer = &TCPServer::instance();
    lServer->startServer(3350);



    return a.exec();
}
