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

enum PostType
{
    PostType_Begin = 0,
    PostType_GetCheckMachineList = 1, // 获取机台列表
    PostType_GetmmsTaskDetail = 2, // 获取任务信息
    PostType_CancleTask1 = 3, // 取消任务检查 第一步获取id
    PostType_CancleTask2 = 4, // 取消任务检查 第二步取消
    PostType_CancleRecieve = 5, // 取消收件
    PostType_ConfirRevieve = 6, // 确认收件
    PostType_BeginTask = 7, // 开始检测
};

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
    // 提交审核
    int SubmitForView();
    // 下载文件  bPlugin 是否调用第三方插件
    int DownloadFile(QString strMmsID,int iFileType = 0 , bool bPlugin = false);
    // 取消检查任务
    int CancleCheckTask(QString strMmsID);
    // 取消检查任务 第二步
    int CancleCheckTask2( QString strTaskId);
    //取消收件
    int CancleRecieve(QString strMmsId);
    // 检测设备查询
    int GetCheckMechineList();
    // 确认收件 检测任务
    int ConfirmTask(QString strMmsID);
    // 开始检测
    int BeginCheck(QString strMmsID);
private:
    void DealWithLoginResponse(QJsonObject& json);
    void DealWithPageListResponse(QJsonObject& json);
    // 处理获取机器列表的响应
    void DealWithGetCheckMachineResponse(QJsonObject& json);
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

    int m_iStatus = 0;  // 单号状态  1 上传文件  2 完成检测 3 提交审核

    int m_iFileData = 0; // 文件接收

    PostType m_iPostType = PostType_Begin; // 请求类型  目前 m_iStatus  和 m_iFileData 都表示请求类型 这里 不整合 重新排列

    bool m_bDownFilePlugin = false;

    QString m_strDownloadFile;
    QString m_strMmsID; // 单号
    QString m_strTaskId;// 任务id

public slots:
    void SlotsRecvReplayData(QNetworkReply* pReplay);

public:
    // 调用外部插件前的配置处理
    int ModifyPluginConfig();
    // 调用外部插件
    int ExePlugin(QString strPluginPath);

    QString m_strCPKFilePath = "";
    QString m_strFAIFilePath = "";

};

#endif // HTTPNETOBJECT_H
