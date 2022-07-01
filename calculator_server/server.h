#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

#include "calculator.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

private slots:
    void onNewConnection();
    void readSock();

private:
    QTcpServer* tcpServer = nullptr;
    QTcpSocket* clientSocket = nullptr;
};

#endif // SERVER_H
