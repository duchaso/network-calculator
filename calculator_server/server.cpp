#include "server.h"




Server::Server(QObject *parent)
    : QTcpServer(parent)
{}

void Server::startServer()
{
    if (!listen(QHostAddress::Any, 5678))
    {
        qDebug() << "Not working";
    } else {
        qDebug() << "Working fine";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    CalculatorThread* thread = new CalculatorThread(socketDescriptor);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}
