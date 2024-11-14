#include "excellprecess.h"
#include <QVariant>
#include <QVariantList>
#include <QDebug>
#include <QColor>
#include <QFile>
#include <QDir>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include "operationinterface.h"
#include "globle.h"
#include "ui_operationinterface.h"
#include "logger.h"
#include <QAxBase>
#include <QAxObject>
#include <QAxWidget>
#include <objbase.h>
#include <QFileInfo>
#include <QVariant>
#include <QAxBase>


ExcellPrecess::ExcellPrecess() {}

ExcellPrecess::~ExcellPrecess()
{
    // 退出 Excel 应用
    m_pAxObject->dynamicCall("Quit()");
    delete m_pAxObject;
    m_pAxObject = nullptr;
}

int ExcellPrecess::Init(OperationInterface* pOperationInterFace)
{
    m_pAxObject = new QAxObject("KET.Application");
    m_pAxObject->dynamicCall("SetVisible(bool)", false);


   // if (m_pAxObject->setControl("Excel.Application"))
    {	// 加载 Microsoft Excel 控件
        LOG_INFO("load Excel.Application success");
    }
     if( m_pAxObject->setControl("kET.Application"))
    {
        LOG_INFO("load kET.Application success");
    }
    else
    {
        LOG_ERROR("加载excel控件失败");
    }
    m_pWorkBooks = m_pAxObject->querySubObject("Workbooks");
    if(nullptr == m_pWorkBooks)
    {
        return -1;
    }

    m_pSheetInfo = new CSheetFillDataRange();

    m_pSheetInfo->InitData();

    m_pOperationInterFace = pOperationInterFace;


    CheckDirectoryExists("./template");
    CheckDirectoryExists("./temporary");

    return 0;
}

int ExcellPrecess::WriteData(QVector<RecvFile::STDetailData> *pVectorData, QString &strFilePath)
{

    if(nullptr == m_pWorkBooks)
    {
        return -1;
    }
    // 1. 打开文件
    qDebug() << "WriteData 1 : filepath" << strFilePath ;
    if(0 != CheckFileExists(strFilePath))
    {
        // 模版文件不存在
        QString strError = "没有文件:";
        strError += strFilePath;
        m_pOperationInterFace->MessageBoxInfomation("错误",strError);
        return -2;
    }
    QAxObject *pWorkbook = m_pWorkBooks->querySubObject("Open(const QString&)", strFilePath);
    if(nullptr == pWorkbook)
    {
        return -2;
    }

    //新写文件
    QString currentPath = QDir::currentPath();
    std::string strFileName = "/temporary/880-GNT022-03-004.xlsm";
    QString strNewFile = QString::fromStdString(strFileName);
    strNewFile = currentPath + strNewFile;

    if(IsFileOpen(strNewFile))
    {
        m_pOperationInterFace->ShowMessageBoxInfo("错误", "目标文件已打开");
        return -3;
    }
    //捕获异常
    m_pOperationInterFace->SetSlotExcelException(pWorkbook , strFilePath);
    //2 .获取所有工作簿
     qDebug() << "WriteData 2 : filepath" << strFilePath ;
    QAxObject *pSheets = pWorkbook->querySubObject("Sheets");
    if(nullptr == pSheets)
    {
        return -4;
    }
    //3 . 打开工作簿
     qDebug() << "WriteData 3 : filepath" << strFilePath ;
    QAxObject *pSheet =pSheets->querySubObject("Item(int)", 1);
    if(nullptr == pSheet)
    {
        return -5;
    }

    QVariant sheetName = pSheet->dynamicCall("Name");
    qDebug() << "Sheet Name:" << sheetName.toString();

    // 读取位置信息
    ReadCellKey(pSheet);
    int iNowColumn = m_pSheetInfo->GetNowColumn();
    for(auto& it : *pVectorData)
    {
        for(auto& it_value : it.m_mMeasuredValue)
        {
            int iBeginRow =GetDataRow(it_value.strName);
            if(-1 == iBeginRow)
            {
                qDebug() << "writedata error key: " << it_value.strName << ", column: " << iBeginRow;
                LOG_ERROR("error writedata error key:%s ,column:%d",it_value.strName , iBeginRow);
                continue;
            }
            QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", iBeginRow, iNowColumn);
           // QVariant cellValue = pCell->dynamicCall("Value()");
            pCell->setProperty("Value", it_value.dActual);
            
            
            QVariant cellValue = pCell->dynamicCall("Value()");
          //  qDebug() << "fill cell :  " << iNowColumn << ": " << iBeginRow  << "value:" << cellValue.toString();
          LOG_ERROR("error writedata success row:%d ,column:%d,key:%s,value:%s ",iNowColumn , iBeginRow,it_value.strName.toStdString().c_str() ,cellValue.toString().toStdString().c_str());
        }
        iNowColumn++;
    }

    // 另保存 Excel 文件
    qDebug() << "new file: " << strNewFile;
    //strNewFile = "D:\\S_wroking/new/123.xlms";
    // 把 : 后的 / 改成 \\

    DealFilePath(strNewFile);
    qDebug() << "new file: " << strNewFile;
    QVariant result = pWorkbook->dynamicCall("SaveAs(const QString&)", strNewFile);
    if (!result.isValid() )
    {
        return -6;
    }
    if( result.isNull())
    {
        return -7;
    }
    else
    {
        // 关闭工作簿
        pWorkbook->dynamicCall("Close()");
        m_pOperationInterFace->SavePushFilePath(strNewFile);
        LOG_INFO("writedata save newfile success :%s",strNewFile.toStdString().c_str());
        
    }

    return 0;
}

int ExcellPrecess::ReadCellKey(QAxObject *pSheet)
{
    int iRow = 15;   // 目前确认从 2列 15 行开始
    int iColumn = 2;
    m_mFileCloumnHash.clear();
    QVariant cellValue;
    do
    {
        QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", iRow, iColumn);
        if(nullptr == pCell)
        {
            return -1;
        }
        cellValue = pCell->dynamicCall("Value()");
        if(cellValue.toString().isEmpty())
        {
            break;
        }
        m_mFileCloumnHash[cellValue.toString()] = iRow;
        qDebug()<< "key: " << cellValue.toString() << "value: " <<iRow;
        iRow++;
    }while(true);
    return 0;
}

int ExcellPrecess::GetDataRow(QString strName)
{
    auto it = m_mFileCloumnHash.find(strName);
    if(it == m_mFileCloumnHash.end())
    {
        return -1;
    }
    return it.value();
}

int ExcellPrecess::CleanSheetData(QString &strFile)
{
    if(nullptr == m_pWorkBooks)
    {
        return -1;
    }
    // 1. 打开文件
    //qDebug() << "WriteData 1 : filepath" << strFile ;
    QAxObject *pWorkbook = m_pWorkBooks->querySubObject("Open(const QString&)", strFile);
    if(nullptr == pWorkbook)
    {
        return -2;
    }
    //2 .获取所有工作簿
    //qDebug() << "WriteData 2 : filepath" << strFile ;
    QAxObject *pSheets = pWorkbook->querySubObject("Sheets");
    if(nullptr == pSheets)
    {
        return -3;
    }
    //3 . 打开工作簿
    //qDebug() << "WriteData 3 : filepath" << strFile ;
    QAxObject *pSheet =pSheets->querySubObject("Item(int)", 1);
    if(nullptr == pSheet)
    {
        return -4;
    }

    QVariant sheetName = pSheet->dynamicCall("Name");
    //qDebug() << "Sheet Name:" << sheetName.toString();

    // 清空一组连续单元格（例如：A1 到 C3）
     QAxObject *range = pSheet->querySubObject("Range(const QString&)", "J15:AO165");
     range->setProperty("Value", "");
    // 保存 Excel 文件
     pWorkbook->dynamicCall("Save()");
     // 关闭工作簿
     pWorkbook->dynamicCall("Close()");
     return 0;
}


bool ExcellPrecess::IsFileOpen(QString strFile)
{
    QFile file(strFile);
    if (file.exists() && !file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        file.close();
        return true;  // 文件已被锁定
    }
    file.close();
    return false;
}


int ExcellPrecess::ShowExeclData()
{
    /*
   // QTableView tableView;
    m_pOperationInterFace->GetUiPointObject()->ShowDataView->setWindowTitle("QTableView Example");

   // QStandardItemModel model(3, 3); // 创建3行3列的数据模型
    QStandardItemModel *model = new QStandardItemModel(3, 3);

    QStringList headers = {"Column 1", "Column 2", "Column 3"};
    //model->setHorizontalHeaderLabels(headers);
    model->setVerticalHeaderLabels(headers);

    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            QStandardItem *item = new QStandardItem(QString("Item %1-%2").arg(row+1).arg(col+1));
            model->setItem(row, col, item);
        }
    }

    //tableView.setModel(&model);
   // tableView.show();
    m_pOperationInterFace->GetUiPointObject()->ShowDataView->setModel(model);
    m_pOperationInterFace->GetUiPointObject()->ShowDataView->show();
*/
    return 0;
}






int ExcellPrecess::CheckFileExists(QString strFile)
{
     QFile file(strFile);
    if (file.exists())
    {
        return 0;
    }
    return -1;
}

int ExcellPrecess::DealFilePath(QString &inputPath)
{
    // 查找第一个 ':' 的位置
    int colonIndex = inputPath.indexOf(':');

    // 如果找到了 ':'，检查后面的第一个 '/'
    if (colonIndex != -1 && colonIndex + 1 < inputPath.length()) {
        // 找到 ':' 后面的第一个 '/'
        int firstSlashIndex = inputPath.indexOf('/', colonIndex + 1);

        // 如果找到了这个 '/', 则替换它前后
        if (firstSlashIndex != -1) {
            QString adjustedPath = inputPath;
            // 替换第一个 '/' 为 '\\'
            adjustedPath.replace(firstSlashIndex, 1, "\\");
            inputPath = adjustedPath;
        }
    }
    return 0;
}
