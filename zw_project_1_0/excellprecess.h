#ifndef EXCELLPRECESS_H
#define EXCELLPRECESS_H

#include <QObject>
#include <QVector>
#include <QAxObject>
#include "recvfile.h"
#include "sheetfilldatarange.h"
#include <QHash>
#include <memory>

class OperationInterface;
using namespace std;

class CExcellPointMgr
{
public:
    CExcellPointMgr(QAxObject* pExcellWork,QAxObject* pWorkBooks)
    {
        m_pExcellWork = pExcellWork;
        m_pWorkBooks = pWorkBooks;
    }
    ~CExcellPointMgr()
    {
        if(m_pExcellWork)
        {
            m_pWorkBooks->dynamicCall("Close()");
            m_pExcellWork->dynamicCall("Quit()");
            delete m_pExcellWork;
            m_pExcellWork = nullptr;
            qDebug()<< "销毁 excelK控件";

        }
    }
public:
    QAxObject* m_pExcellWork = nullptr;
    QAxObject* m_pWorkBooks = nullptr;
};
class ExcellPrecess
{
public:
    ExcellPrecess();
    ~ExcellPrecess();

    int Init(OperationInterface* pOperationInterFace);

    // 初始化excel控件
    std::shared_ptr<CExcellPointMgr> InitExcellObject();

    int WriteData(QVector<RecvFile::STDetailData> *pVectorData, QString& strFilePath);

    int FillBasicInfomation(QAxObject *pshell ,int iCloumuNum);
    // 从模版文件中读取数据 建立数据与行号的映射关系
    int ReadCellKey(QAxObject *pCell);

    // 根据名称获取行号
    int GetDataRow(QString strName);

    // 清空文件 的填写数据部分
    int CleanSheetData(QString &strFile);

    // 加载文件完成后，更新模型内容
    bool LoadData();


    // 数据感知部分
    int ReadFileData(QString strFilePath , QVector<RecvFile::STDetailData> &VectorData,int iFileType);

    // 读取兆丰的excel文件  老兆丰
    int ReadExcelData(QString strFilePath , QVector<RecvFile::STDetailData> &VectorData);

    // 读取兆丰的excel文件  老兆丰
    int ReadExcelDataNew(QString strFilePath , QVector<RecvFile::STDetailData> &VectorData);

    // 读取MIV的 txt文件s
    int ReadTxtData(QString strFilePath , QVector<RecvFile::STDetailData> &VectorData);

private:
   // shared_ptr<QAxObject> m_pAxObject = nullptr;
   // QAxObject* m_pWorkBooks = nullptr;

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
