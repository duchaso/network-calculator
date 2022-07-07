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
    CalculatorThread(qintptr socketDescriptor, QObject* parent = nullptr);

    void run() override;

private slots:
    void readyRead();
    void disconnected();

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    qintptr socketDescriptor;
    QTcpSocket* socket;
    Calculator calculator;
};

#endif // CALCULATORTHREAD_H
