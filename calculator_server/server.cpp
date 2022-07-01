#include "server.h"

Server::Server(QObject *parent)
    : QObject{parent}
{
    tcpServer = new QTcpServer(this);
    connect(tcpServer, SIGNAL(newConnection()),
            this, SLOT(onNewConnection()));
    if (!tcpServer->listen(QHostAddress::Any, 5678))
    {
        qDebug() << "Not working";
        return;
    }
}

void Server::onNewConnection()
{
    clientSocket = tcpServer->nextPendingConnection();
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(readSock()));
}

void Server::readSock()
{
    QString example(clientSocket->readAll());
    Calculator calculator(std::move(example));
    if (calculator.isCorrect())
    {
        auto out = QString::number(calculator.result()).toStdString();
        clientSocket->write(out.c_str());
    } else {
        clientSocket->write("#");
    }
}
