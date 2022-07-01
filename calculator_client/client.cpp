#include "client.h"

Client::Client(QObject *parent)
    : QObject{parent}
    , m_socket{new QTcpSocket(this)}
{
    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readResult()));
    connect(m_socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
}

QString Client::result()
{
    return m_result;
}

void Client::setInput(QString i)
{
    m_input = i;
    m_socket->abort();
    m_socket->connectToHost("127.0.0.1", 5678);
    m_socket->write(i.toStdString().c_str());
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError)
    {
    case QAbstractSocket::RemoteHostClosedError:
        qDebug() << "The host was not found.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer";
        break;
    default:
        qDebug() << "ERROR: " << m_socket->errorString();
    }
}

void Client::readResult()
{
    m_result = {m_socket->readAll()};
    emit resultChanged();
}
