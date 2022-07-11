#include "server.h"

namespace {
    constexpr auto PORT = 5678;
}

Server::Server(QObject *parent)
    : QTcpServer(parent)
{}

void Server::startServer()
{
    if (!listen(QHostAddress::Any, PORT))
    {
        qDebug() << "Not working";
    } else {
        qDebug() << "Working fine";
    }
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    CalculatorThread* thread = new CalculatorThread(socketDescriptor);
    connect(thread, &CalculatorThread::finished, thread, &CalculatorThread::deleteLater);
    thread->start();
}
