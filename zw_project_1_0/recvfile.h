#ifndef RECVFILE_H
#define RECVFILE_H

#include <QObject>
#include <QTcpSocket>
#include <QHash>

const QString g_strPacketHeader = "msResult";
const QString g_strPacketTail1 = "\n\r";
const QString g_strPacketTail2 = "\r\n";
class RecvFile : public QObject
{
    Q_OBJECT
public:
    explicit RecvFile(QObject *parent = nullptr);

    ~RecvFile();
    void ConnectServer(QString strIp , unsigned short usPort);
    void SendMessageToServer(QString strMessage);

public:
    // 数据结构
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
        QString m_strPartID;  // 工件ID
        QString m_strDateTime;   // 测量时间
        QChar m_cQualified;  // 是否合格  G代表合格,B代表不合格
        QString m_strUnits;  // 测量单位
        QHash<QString ,STDimenSionData> m_mMeasuredValue; // 测量值
    };
    // 处理数据的函数
    void DealWithMessageData();
    // 获取一条完整的数据
    QString GetACompleteData();
    // 拆分处理一条完整的数据
    int SplitMessageData(QString strAComData,STDetailData& temData);
    // 获取一个数据类型 cSplitChar.....cSplitChar之间的数据
    QString GetADetailData(QString& strData, QChar cSplitChar);
    //拆分测量值
    bool GetDimensionData(QString &strDimension , STDimenSionData& stDimenSionData);
signals:
    void ConnectOk();
    void ConnectError();
    void MessageToUi(QByteArray szMessage);
    void ResultToUi(STDetailData stResult);
private slots:
    void RecieveData();

private:
    QTcpSocket* m_pTcpSocket = nullptr;

    QString m_strMessageData;

};

#endif // RECVFILE_H
