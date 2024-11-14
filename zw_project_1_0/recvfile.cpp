#include "recvfile.h"
#include <QHostAddress>
#include <Qthread>

RecvFile::RecvFile(QObject *parent)
    : QObject{parent}
{
    m_strMessageData.clear();
}

RecvFile::~RecvFile()
{
    m_pTcpSocket->close();
    m_pTcpSocket->deleteLater();
    m_pTcpSocket = nullptr;
}

void RecvFile::ConnectServer(QString strIp, unsigned short usPort)
{
    qDebug()<<"子线程id:" << QThread::currentThreadId() << "ip :" << strIp <<"port:" << usPort;
    m_pTcpSocket = new QTcpSocket();
    m_pTcpSocket->connectToHost(QHostAddress(strIp),usPort);

    // 链接成功的处理
    connect(m_pTcpSocket,&QTcpSocket::connected,this,&RecvFile::ConnectOk);
    // 连接失败的处理
    connect(m_pTcpSocket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &RecvFile::ConnectError);
    // 接收消息
    connect(m_pTcpSocket,SIGNAL(readyRead()),this,SLOT(RecieveData()));
}

void RecvFile::SendMessageToServer(QString strMessage)
{
    m_pTcpSocket->write(strMessage.toStdString().c_str());
}

void RecvFile::DealWithMessageData()
{
    //1 .取出1条完整的数据 ， 并处理好后续的数据
    QString strData = GetACompleteData();
    if(strData.isEmpty())
    {
        return ;
    }
    //2.处理取出的数据
    qDebug()<< "获取到一条完整的数据:" << strData;
    STDetailData temData;
    int iRet = SplitMessageData(strData , temData);
    if(iRet < 0 )
    {
        // todo 输出日志
        return;
    }
    //3 .存储
    emit ResultToUi(temData);
}

QString RecvFile::GetACompleteData()
{
    QString strCompleteData;
    if(m_strMessageData.isEmpty())
    {
        return strCompleteData;
    }
    if(!m_strMessageData.startsWith(g_strPacketHeader))
    {
        // toso 输出异常日志  正确的数据都以 g_strPacketHeader 开始
        int iIndex = m_strMessageData.indexOf(g_strPacketHeader);
        if(-1 == iIndex)
        {
            m_strMessageData.clear();
            // todo 输出错误日志
            return strCompleteData;
        }

        // 让strCompleteData 恢复到以 g_strPacketHeader 开始
        m_strMessageData.remove(0 , iIndex);
    }
    qDebug()<<"消息内容:" << m_strMessageData;
    int iSecondIndex = m_strMessageData.indexOf(g_strPacketHeader , g_strPacketHeader.size() + 1);
    if(-1 == iSecondIndex)
    {
        if(m_strMessageData.endsWith(g_strPacketTail1) || m_strMessageData.endsWith(g_strPacketTail2))
        {
            strCompleteData = m_strMessageData;
            m_strMessageData.clear();
        }
    }
    else
    {
        strCompleteData = m_strMessageData.left(iSecondIndex);
        m_strMessageData.remove(0 , iSecondIndex);
    }

    return strCompleteData;
}

int RecvFile::SplitMessageData(QString strAComData,STDetailData& temData)
{
    if(!strAComData.startsWith(g_strPacketHeader))
    {
        return -1;
    }
    strAComData.remove(0 , g_strPacketHeader.size()+ 1);

    QChar cSplit = '$';
    //1 获取pardid;
    temData.m_strPartID = GetADetailData(strAComData,cSplit);
    if(temData.m_strPartID.isEmpty())
    {
        //to 日志输出
       // return -1;
    }
    //2 获取时间;
    temData.m_strDateTime = GetADetailData(strAComData,cSplit);
    if(temData.m_strDateTime.isEmpty())
    {
        //to 日志输出
        return -1;
    }
    // 3 获取结果状态
    QString strStaus = GetADetailData(strAComData,cSplit);
    if(1 != strStaus.size())
    {
        //to 日志输出
        return -1;
    }
    temData.m_cQualified = strStaus.at(0);
    // 4 获取单位
    temData.m_strUnits = GetADetailData(strAComData,cSplit);
    if(temData.m_strUnits.isEmpty())
    {
        //to 日志输出
        return -1;
    }

    // 5 获取测量值
    QString strDimension = GetADetailData(strAComData,cSplit);

    do
    {
        STDimenSionData stTemDimenSionData;
        while(GetDimensionData(strDimension ,  stTemDimenSionData))
        {
            temData.m_mMeasuredValue[stTemDimenSionData.strName] = stTemDimenSionData;
            stTemDimenSionData.Clear();
        }

        strDimension = GetADetailData(strAComData , cSplit);
    }while(!strDimension.isEmpty());

    return 0;
}

QString RecvFile::GetADetailData(QString& strData , QChar cSplitChar)
{
    QString strResult;
    int iIndex1 = strData.indexOf(cSplitChar);
    if(-1 != iIndex1)
    {
        int iIndex2 = strData.indexOf(cSplitChar, iIndex1 + 1);
        if(-1 != iIndex2)
        {
            strResult = strData.mid(iIndex1 + 1 , iIndex2 - iIndex1 - 1)  ;
            // 原始字符串移除这组数据
            strData.remove(0 , iIndex2 + 1);
        }
    }
    return strResult;
}

bool RecvFile::GetDimensionData(QString &strDimension , STDimenSionData& stDimenSionData)
{
    QChar cColon = ':';
    QChar cComma = ',';
    int iIndexColon = strDimension.indexOf(cColon);
    if(-1 == iIndexColon || 0 == iIndexColon)
    {
        return false;
    }
    stDimenSionData.strName = strDimension.left(iIndexColon);

    int iIndexCommaFirst = strDimension.indexOf(cComma);
    if(-1 == iIndexCommaFirst || iIndexCommaFirst <= iIndexColon)
    {
        return false;
    }
    QString strValue = strDimension.mid(iIndexColon+1 , iIndexCommaFirst - iIndexColon - 1 );
    bool bOk = false;
    stDimenSionData.dTheo = strValue.toDouble(&bOk);
    if(!bOk)
    {
        return false;
    }
    // 移除之前的内容
    strDimension.remove(0 , iIndexCommaFirst + 1);

    // 上偏差
    iIndexCommaFirst = strDimension.indexOf(cComma);
    if(-1 == iIndexCommaFirst )
    {
        return false;
    }
    strValue = strDimension.left(iIndexCommaFirst);
    bOk = false;
    stDimenSionData.dUpperLimit = strValue.toDouble(&bOk);
    if(!bOk)
    {
        return false;
    }
    strDimension.remove(0 , iIndexCommaFirst + 1);

    // 下偏差
    iIndexCommaFirst = strDimension.indexOf(cComma);
    if(-1 == iIndexCommaFirst )
    {
        return false;
    }
    strValue = strDimension.left(iIndexCommaFirst);
    bOk = false;
    stDimenSionData.dLowerLimit = strValue.toDouble(&bOk);
    if(!bOk)
    {
        return false;
    }

    strDimension.remove(0 , iIndexCommaFirst + 1);

    // 实际值

    iIndexCommaFirst = strDimension.indexOf(cComma);
    if(-1 == iIndexCommaFirst )
    {
        return false;
    }
    strValue = strDimension.left(iIndexCommaFirst);
    bOk = false;
    stDimenSionData.dActual = strValue.toDouble(&bOk);
    if(!bOk)
    {
        return false;
    }
    strDimension.remove(0 , iIndexCommaFirst + 1);

    return true;
}

void RecvFile::RecieveData()
{
    QByteArray szReData = m_pTcpSocket->readAll();
   // qDebug()<< szReData;
   // QString strText = QString::fromUtf8(szReData);
   // qDebug()<< "utf-8:   " <<strText;
    QString strGB2312Data = QString::fromLocal8Bit(szReData);
   // qDebug()<< "gb2312:  " <<strGB2312Data;
    emit MessageToUi(szReData);

    // 服务端过来的数据就是字符串
    m_strMessageData += strGB2312Data;
    qDebug()<< "detail:  " <<m_strMessageData;
    DealWithMessageData();
}




