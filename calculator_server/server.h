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
    explicit Server(QObject *parent = nullptr)
        : QTcpServer(parent)
    {}

    void startServer()
    {
        if (!listen(QHostAddress::Any, 5678))
        {
            qDebug() << "Not working";
        } else {
            qDebug() << "Working fine";
        }
    }

protected:
    void incomingConnection(qintptr socketDescriptor) override
    {
        CalculatorThread* thread = new CalculatorThread(socketDescriptor);
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
        thread->start();
    }
};

#endif // SERVER_H
