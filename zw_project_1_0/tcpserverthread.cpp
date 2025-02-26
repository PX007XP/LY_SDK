#include "tcpserverthread.h"
#include <QDebug>
#include <QDateTime>
#include "logger.h"
#include "globle.h"

QString g_strMessageHead = "msResult:";
TcpServerThread::TcpServerThread(QObject *parent)
    : QObject(parent)
{
    server = new QTcpServer(this);
}

void TcpServerThread::runServer()
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
        STDetailData temData;

        int iRet = DealWithData(message , temData);
        if(0 == iRet)
        {

            emit CMMResultToUi(temData);
        }

        else
        {
            LOG_ERROR(" CMM DealWithData error iret=%d",iRet);
        }
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

int TcpServerThread::DealWithData(QString strAComData, STDetailData& stResult)
{
    if(!strAComData.startsWith(g_strMessageHead))
    {
        return -1;
    }
    strAComData.remove(0 , g_strMessageHead.size());

    QStringList listResult = strAComData.split("$" , Qt::SkipEmptyParts);

    if(listResult.isEmpty())
    {
        return -2;
    }

    foreach (const QString &strData, listResult)
    {
        if(strData.isEmpty())
        {
            continue;
        }

        int commaPos = strData.indexOf(',');
        if(-1 == commaPos)
        {
            continue;
        }

        QString strKey = strData.left(commaPos).trimmed(); // 去除空格
        QString strValue = strData.mid(commaPos+1).trimmed();
        bool conversionOk = false;
        double dValue = strValue.toDouble(&conversionOk);
        if(conversionOk == false || strKey.isEmpty())
        {
            continue;
        }
        STDimenSionData stValue;
        stValue.dActual = dValue;
        stValue.strName = strKey;
        stResult.m_mMeasuredValue[strKey] = stValue;

        LOG_INFO("CMM recvice data and insert [%s,%f]",strKey.toStdString().c_str(),dValue);

    }


    return 0;
}

void TcpServerThread::CloseServer()
{
    // 关闭所有sockets.
}
