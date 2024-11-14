#ifndef HTTPNETOBJECT_H
#define HTTPNETOBJECT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QCoreApplication>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
class OperationInterface;


class HttpNetObject : public QObject
{
public:
    HttpNetObject();

    int Init(OperationInterface* pObject);
    // 登录网站
    int LoginPost(QString strUserName , QString strPassWord);

    // 获取基本信息
    int GetCheckTaskData(QString strMmsID);

    //上传文件
    int PostFileToNet(QString strFileName);
    //完成检测
    int CompeleteCheck( );
private:
    void DealWithLoginResponse(QJsonObject& json);
    void DealWithPageListResponse(QJsonObject& json);
    void DealWithFileResponse(QJsonObject& json);

    // 处理子单号详细信息
    int GetJsonValueBykey(QJsonObject jsonObject ,QString strKeyName);
private:
    QNetworkAccessManager* m_pManager = nullptr;

    QString m_strToken;
    QString m_strBizid;
    QString m_strFileId;
    QString m_strUserName;

    OperationInterface* m_pOperationObject;
    bool m_bLoginStatus = false;
public slots:
    void SlotsRecvReplayData(QNetworkReply* pReplay);

};

#endif // HTTPNETOBJECT_H
