#ifndef EXCELLPRECESS_H
#define EXCELLPRECESS_H

#include <QObject>
#include <QVector>
#include <QAxObject>
#include "recvfile.h"
#include "sheetfilldatarange.h"
#include <QHash>

class OperationInterface;
class ExcellPrecess
{
public:
    ExcellPrecess();
    ~ExcellPrecess();

    int Init(OperationInterface* pOperationInterFace);

    int WriteData(QVector<RecvFile::STDetailData> *pVectorData, QString& strFilePath);

    // 从模版文件中读取数据 建立数据与行号的映射关系
    int ReadCellKey(QAxObject *pCell);

    // 根据名称获取行号
    int GetDataRow(QString strName);

    // 清空文件 的填写数据部分
    int CleanSheetData(QString &strFile);

    // 显示表格内容
    int ShowExeclData();

private:
    QAxObject* m_pAxObject = nullptr;
    QAxObject* m_pWorkBooks = nullptr;

    CSheetFillDataRange* m_pSheetInfo = nullptr;

    QHash<QString, int> m_mFileCloumnHash;
    QString m_strFileName;

    OperationInterface* m_pOperationInterFace = nullptr;

    bool IsFileOpen(QString strFile);

    QString m_strtoken;

   // int CheckDirectoryExists(QString strPath);
    int CheckFileExists(QString strFile);
    int DealFilePath(QString &strFile);

};

#endif // EXCELLPRECESS_H
