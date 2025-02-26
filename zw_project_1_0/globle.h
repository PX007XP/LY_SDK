#ifndef GLOBLE_H
#define GLOBLE_H
#include<QString>
#include <QHash>

class Logger;
extern QString g_strReqNo ;
extern QString g_strReqUserName ;
extern QString g_strReqUnicom ; // 送检单位
extern QString g_strDeviceName ; // 项目名称
extern QString g_strDeviceNo ; // 机台
extern QString g_strReqTime ; // 申请时间
extern QString g_strTestCon ; // 检查要求
//QString g_strReqTime ; // 样品数量
//QString g_strReqTime; // 收件时间
extern QString g_strReportType ; // 检验类别
//QString g_strReqTime ; // 是否破坏
extern QString g_strProjectClassId ; // 检查项目
extern QString g_strProjectStageId ; // 工序
extern QString g_strSatageNo; // 夹具编号
extern QString g_strOrgCode ; // 模穴号
extern QString g_strRemark ; // 备注
extern QString g_strRevArtTime; // 收件时间
extern QString g_strIpAddressKey; // ip地址关键字

extern int g_iFileSaveFlag ; // 上传文件后是否保存文件  0 不保存 1 保存

extern QString g_strSaveFilePath;  // 下载文件自动保存路径

extern int g_iDelTxtFile;

extern QString g_strPluginPath;
extern QString g_strPluginConfigFilePath;
extern QString g_strDownloadFileSavePath;
extern qint64 g_lGaoduguiTimeInterval;
int CheckDirectoryExists(QString strPath);

QString GetFileSuffix(QString strFile);


// 数据结构
struct STDimenSionData1
{
    STDimenSionData1()
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
struct STDetailData1
{
    STDetailData1()
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
    QHash<QString ,STDimenSionData1> m_mMeasuredValue; // 测量值
};
#endif // GLOBLE_H
