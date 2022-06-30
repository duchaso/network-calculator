#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr)
    {
        tcpServer = new QTcpServer(this);
        connect(tcpServer, SIGNAL(newConnection()),
                this, SLOT(foo()));
        if (!tcpServer->listen(QHostAddress::Any, 5678))
        {
            qDebug() << "Not working";
            return;
        }

    }

private slots:
    void foo()
    {
        QTcpSocket* clientSocket = tcpServer->nextPendingConnection();

        clientSocket->write("hello friend \r\n");
        clientSocket->flush();
        clientSocket->waitForBytesWritten(3000);
        clientSocket->close();
    }

private:
    void init();

    QTcpServer* tcpServer = nullptr;
};

#endif // SERVER_H
