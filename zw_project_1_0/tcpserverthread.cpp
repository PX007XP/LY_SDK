#include "tcpserverthread.h"
#include <QDebug>
#include <QDateTime>
#include "logger.h""

TcpServerThread::TcpServerThread(QObject *parent)
    : QThread(parent)
{
    server = new QTcpServer(this);
}

void TcpServerThread::run()
{
    qDebug() << "Starting server thread..." << QThread::currentThreadId();
    if (!server->listen(QHostAddress::Any, 32145))
    {
        LOG_ERROR("Server could not start");
        return;
    }
    connect(server, &QTcpServer::newConnection, this, &TcpServerThread::newConnection);
    qDebug() << "Server started!";
    //exec();
}

void TcpServerThread::newConnection()
{
    QTcpSocket *clientConnection = server->nextPendingConnection();
    if(clientConnection)
    {
        connect(clientConnection, &QTcpSocket::readyRead, this, &TcpServerThread::readClient);
        //connect(clientConnection, &QTcpSocket::disconnected, clientConnection, &QTcpSocket::deleteLater);
        connect(clientConnection, &QTcpSocket::disconnected, this, &TcpServerThread::CloseSocket);
        sockets.append(clientConnection);
        qDebug() << "New client connected:" << clientConnection->peerAddress().toString();
    }
}

void TcpServerThread::readClient()
{
    QTcpSocket *client = qobject_cast<QTcpSocket*>(sender());
    if (client) {
        QString message = QString::fromUtf8(client->readAll());
        qDebug() << "Message from client:" << message;
        // 可以在这里添加逻辑来处理接收到的消息
    }
}

void TcpServerThread::CloseSocket()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (clientSocket) {
        sockets.removeOne(clientSocket);
        clientSocket->deleteLater();
        qDebug() << "Client disconnected: " << clientSocket->peerAddress().toString();
    }
}

void TcpServerThread::CloseServer()
{
    // 关闭所有sockets.
}
