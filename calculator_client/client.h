#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr)
    {
        socket = new QTcpSocket(this);
        connect(socket, SIGNAL(readyRead()), this, SLOT(foo()));
        socket->connectToHost("127.0.0.1", 5678);
    }

public slots:
    void foo()
    {
        QString str(socket->readAll());
        qDebug() << str;
    }

private:
    QTcpSocket* socket = nullptr;

};

#endif // CLIENT_H
