#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

#include "calculator.h"
#include "calculatorthread.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

    void startServer();

protected:
    void incomingConnection(qintptr socketDescriptor) override;
};

#endif // SERVER_H
