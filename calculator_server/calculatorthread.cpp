#include "calculatorthread.h"

CalculatorThread::CalculatorThread(qintptr socketDescriptor, QObject *parent)
    : QThread(parent)
    , socketDescriptor(socketDescriptor)
{}

void CalculatorThread::run()
{
    socket = new QTcpSocket();

    if (!socket->setSocketDescriptor(socketDescriptor))
    {
        emit error(socket->error());
        return;
    }

    connect(socket, &QTcpSocket::readyRead, this, &CalculatorThread::readyRead, Qt::DirectConnection);
    connect(socket, &QTcpSocket::disconnected, this, &CalculatorThread::disconnected);

    qDebug() << socketDescriptor << " Client connected";

    exec();
}

void CalculatorThread::readyRead()
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

void CalculatorThread::disconnected()
{
    qDebug() << socketDescriptor << " Disconnected";

    socket->deleteLater();
    exit(0);
}
