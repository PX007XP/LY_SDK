#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServerThread:public QThread
{

public:
    explicit TcpServerThread(QObject *parent = nullptr);
    void run() override;

private slots:
    void newConnection();
    void readClient();

    void CloseSocket();

public:
    void CloseServer();
private:
    QTcpServer *server = nullptr;
    QList<QTcpSocket*> sockets;
};

#endif // TCPSERVERTHREAD_H
