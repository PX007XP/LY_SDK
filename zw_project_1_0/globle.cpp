#include "globle.h"
#include <QDebug>
#include <QDir>
#include "logger.h"

QString g_strReqNo = QStringLiteral("ReqNO");
QString g_strReqUserName = QStringLiteral("CreatorName");
QString g_strReqUnicom = QStringLiteral("TestUserName"); // 送检单位
QString g_strDeviceName = QStringLiteral("DeviceName"); // 项目名称
QString g_strDeviceNo = QStringLiteral("DeviceNo"); // 机台
QString g_strReqTime = QStringLiteral("CreateTime"); // 申请时间
QString g_strTestCon = QStringLiteral("TestCon"); // 检查要求
//QString g_strReqTime = QStringLiteral("CreateTime"); // 样品数量
//QString g_strReqTime = QStringLiteral("CreateTime"); // 收件时间
QString g_strReportType = QStringLiteral("ReportType"); // 检验类别
//QString g_strReqTime = QStringLiteral("CreateTime"); // 是否破坏
QString g_strProjectClassId = QStringLiteral("ProjectClassId"); // 检查项目
QString g_strProjectStageId = QStringLiteral("ProjectStageId"); // 工序
QString g_strSatageNo = QStringLiteral("SatageNo"); // 夹具编号
QString g_strOrgCode = QStringLiteral("OrgCode"); // 模穴号
QString g_strRemark = QStringLiteral("Remark"); // 备注

Logger* g_pLogger = nullptr;

int g_iLogLevel = 5;

int CheckDirectoryExists(QString strPath)
{
    QDir dir(strPath);
    if (!dir.exists()) {
        if (dir.mkpath("."))
        {
            qDebug() << "目录已创建:" << strPath;
        } else
        {
            return -2;
            qDebug() << "创建目录失败:" << strPath;
        }
    } else
    {
        return -1;
        qDebug() << "目录已存在:" << strPath;
    }
    return 0;
}
