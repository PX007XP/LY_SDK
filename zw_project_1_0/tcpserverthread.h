#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpServer>
#include <QTcpSocket>
#include <QObject>
#include <QHash>
#include "globle.h"

//#include "recvfile.h"


class OperationInterface;
class TcpServerThread:  public QObject
{
    Q_OBJECT
public:
    struct STDimenSionData
    {
        STDimenSionData()
        {
            Clear();
        }
        void Clear()
        {
            strName.clear();
            dTheo = 0.0;
            dUpperLimit = 0.0;
            dLowerLimit = 0.0;
            dActual = 0.0;
        }
        QString strName; // 名称
        double dTheo ; //理论值
        double dUpperLimit; // 上偏差
        double dLowerLimit; // 下偏差
        double dActual;  // 实测值
    };
    struct STDetailData
    {
        STDetailData()
        {
            m_strPartID.clear();
            m_strDateTime.clear();
            m_strUnits.clear();
            m_mMeasuredValue.clear();
        }
        void RestData()
        {
            m_strPartID.clear();
            m_strDateTime.clear();
            m_strUnits.clear();
            m_mMeasuredValue.clear();
        }
        QString m_strPartID;  // 工件ID
        QString m_strDateTime;   // 测量时间
        QChar m_cQualified;  // 是否合格  G代表合格,B代表不合格
        QString m_strUnits;  // 测量单位
        QHash<QString ,STDimenSionData> m_mMeasuredValue; // 测量值
    };
public:
    explicit TcpServerThread(QObject *parent = nullptr);
    void runServer();

private slots:
    void newConnection();
    void readClient();

    void CloseSocket();

    int DealWithData(QString strMessage , STDetailData& stResult);

public:
    void CloseServer();
signals:
    void CMMResultToUi(STDetailData stResult);
private:
    QTcpServer *server = nullptr;
    QList<QTcpSocket*> sockets;

    OperationInterface *m_pInterface;

};

#endif // TCPSERVERTHREAD_H
