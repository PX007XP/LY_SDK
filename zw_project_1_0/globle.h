#ifndef GLOBLE_H
#define GLOBLE_H
#include<QString>

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

int CheckDirectoryExists(QString strPath);
#endif // GLOBLE_H
