#ifndef CALCULATORTHREAD_H
#define CALCULATORTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QObject>

#include <memory>

#include "calculator.h"

class CalculatorThread : public QThread
{
    Q_OBJECT
public:
    CalculatorThread(qintptr socketDescriptor, QObject* parent = nullptr)
        : QThread(parent)
        , socketDescriptor(socketDescriptor)
    {}

    void run() override
    {
        socket = new QTcpSocket();

        if (!socket->setSocketDescriptor(socketDescriptor))
        {
            emit error(socket->error());
            return;
        }

        connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()), Qt::DirectConnection);
        connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));

        qDebug() << socketDescriptor << " Client connected";

        exec();
    }

private slots:
    void readyRead()
    {
        QByteArray data = socket->readAll();
        qDebug() << "Example: " << data;

        QString ex(data);
        calculator.calculate(ex);
        if (!calculator.isCorrect())
        {
            qDebug() << "wrong example";
            socket->write("#");
            return;
        }
        auto out = QString::number(calculator.result()).toStdString();
        socket->write(out.c_str());
    }
    void disconnected()
    {
        qDebug() << socketDescriptor << " Disconnected";

        socket->deleteLater();
        exit(0);
    }

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    qintptr socketDescriptor;
    QTcpSocket* socket;
    Calculator calculator;
};

#endif // CALCULATORTHREAD_H
