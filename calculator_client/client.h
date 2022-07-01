#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString input WRITE setInput)
    Q_PROPERTY(QString result READ result NOTIFY resultChanged)
public:
    explicit Client(QObject *parent = nullptr);

    QString result();
public slots:
    void setInput(QString i);
private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void readResult();
signals:
    void inputChanged();
    void resultChanged();

private:
    QTcpSocket* m_socket = nullptr;
    QString m_input;
    QString m_result;
};

#endif // CLIENT_H
