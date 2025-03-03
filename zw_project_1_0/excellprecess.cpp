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
//#include <objbase.h>
#include <QFileInfo>
#include <QVariant>
#include <QThread>



ExcellPrecess::ExcellPrecess() {}

ExcellPrecess::~ExcellPrecess()
{

}

int ExcellPrecess::Init(OperationInterface* pOperationInterFace)
{

    m_pSheetInfo = new CSheetFillDataRange();

    m_pSheetInfo->InitData();

    m_pOperationInterFace = pOperationInterFace;


    CheckDirectoryExists("./template");
    CheckDirectoryExists("./temporary");

    QDir dir("./temporary");

    // 获取目录下所有文件和子目录的列表
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot);

    foreach (const QFileInfo &fileInfo, fileList)
    {
        // 删除文件
        dir.remove(fileInfo.fileName());
    }

    return 0;
}

std::shared_ptr<CExcellPointMgr> ExcellPrecess::InitExcellObject()
{
    QAxObject* pAxObject = new QAxObject("Excel.Application");
    if (nullptr == pAxObject)
    {
        LOG_ERROR("创建 Excel QAxObject 失败");
        return nullptr;
    }
    
    pAxObject->dynamicCall("SetVisible(bool)", false);


    if (pAxObject->setControl("Excel.Application"))
    {	// 加载 Microsoft Excel 控件
        LOG_INFO("load Excel.Application success");
    }
    else if( pAxObject->setControl("KET.Application"))
    {
        LOG_INFO("load kET.Application success");
    }
    else
    {
        LOG_ERROR("加载excel控件失败");
    }
    QAxObject* pWorkBooks = pAxObject->querySubObject("Workbooks");
    if(nullptr == pWorkBooks)
    {
        pAxObject->dynamicCall("Quit()");
        delete pAxObject;
        pAxObject = nullptr;
        LOG_ERROR("get workbooks faild");
        return nullptr;
    }

    std::shared_ptr<CExcellPointMgr> pAxObjectMgr =  make_shared<CExcellPointMgr>(pAxObject , pWorkBooks);

    return pAxObjectMgr;
}

int ExcellPrecess::WriteData(QVector<RecvFile::STDetailData> *pVectorData, QString &strFilePath)
{
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
   // qDebug() << "文件路径：" << strFilePath;
   // if(IsFileOpen(strFilePath))
   // {
       // m_pOperationInterFace->ShowMessageBoxInfo("错误", "目标文件已打开");
       // return 1;
   // }
    shared_ptr<CExcellPointMgr> pExcellPtr = InitExcellObject();
    if(nullptr == pExcellPtr || nullptr == pExcellPtr->m_pWorkBooks)
    {
        return -3;
    }

    QAxObject *pWorkbook = pExcellPtr->m_pWorkBooks->querySubObject("Open(const QString&)", strFilePath);
    if(nullptr == pWorkbook)
    {
        return -4;
    }

    //新写文件
    QString currentPath = QDir::currentPath();
    QString strSubNumber = m_pOperationInterFace->GetUiPointObject()->NumberEdit->text();
    if(strSubNumber.isEmpty())
    {
        m_pOperationInterFace->ShowMessageBoxInfo("错误", "无法");
        return -5;
    }

    std::string strFileName = "/temporary/";
    QString strSuffix = GetFileSuffix(strFilePath);
    if(strSuffix.isEmpty())
    {
        pWorkbook->dynamicCall("Close()");
        return -6;
    }
    // 新文件名
    QString strNewFile = QString::fromStdString(strFileName);
    strNewFile = currentPath + strNewFile + strSubNumber + "." +strSuffix;

    if(IsFileOpen(strNewFile))
    {
        m_pOperationInterFace->ShowMessageBoxInfo("错误", "目标文件已打开");
        pWorkbook->dynamicCall("Close()");
        return -7;
    }
    //捕获异常
    m_pOperationInterFace->SetSlotExcelException(pWorkbook , strFilePath);
    //2 .获取所有工作簿
    // qDebug() << "WriteData 2 : filepath" << strFilePath ;
    QAxObject *pSheets = pWorkbook->querySubObject("Sheets");
    if(nullptr == pSheets)
    {
        pWorkbook->dynamicCall("Close()");
        return -8;
    }
    //3 . 打开工作簿
    // qDebug() << "WriteData 3 : filepath" << strFilePath ;
    QAxObject *pSheet =pSheets->querySubObject("Item(int)", 1);
    if(nullptr == pSheet)
    {
        pWorkbook->dynamicCall("Close()");
        return -9;
    }

    QVariant sheetName = pSheet->dynamicCall("Name");
    qDebug() << "Sheet Name:" << sheetName.toString();

    // 读取位置信息
    FillBasicInfomation(pSheet , pVectorData->size());
    ReadCellKey(pSheet);
    int iNowColumn = m_pSheetInfo->GetNowColumn();
    for(auto& it : *pVectorData)
    {
        for(auto& it_value : it.m_mMeasuredValue)
        {
            int iBeginRow =GetDataRow(it_value.strName);
            if(-1 == iBeginRow)
            {
               // qDebug() << "writedata error key: " << it_value.strName << ", column: " << iBeginRow;
                LOG_ERROR("error writedata error key:%s ,column:%d",it_value.strName.toStdString().c_str() , iBeginRow);
                continue;
            }
            QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", iBeginRow, iNowColumn);
           // QVariant cellValue = pCell->dynamicCall("Value()");
            pCell->setProperty("Value", it_value.dActual);
            
            
            QVariant cellValue = pCell->dynamicCall("Value()");
          //  qDebug() << "fill cell :  " << iNowColumn << ": " << iBeginRow  << "value:" << cellValue.toString();
          LOG_DEBUG("error writedata success row:%d ,column:%d,key:%s,value:%s ",iNowColumn , iBeginRow,it_value.strName.toStdString().c_str() ,cellValue.toString().toStdString().c_str());
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
    if (!result.isValid() || result.isNull())
    {
        pWorkbook->dynamicCall("Close()");
        LOG_ERROR("保存文件失败");
        return -10;
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

int ExcellPrecess::FillBasicInfomation(QAxObject *pSheet,int iCloumNum)
{
     bool bInt = false;
    // 回填时间
    QString strBeginTime = m_pOperationInterFace->GetUiPointObject()->dateTimeEditStart->text();
    QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", 6, 6);
    // QVariant cellValue = pCell->dynamicCall("Value()");
    pCell->setProperty("Value", strBeginTime);


    pCell = pSheet->querySubObject("Cells(int, int)", 8, 113);
    // QVariant cellValue = pCell->dynamicCall("Value()");
    pCell->setProperty("Value", strBeginTime);

    pCell = pSheet->querySubObject("Cells(int, int)", 8, 115);
    // QVariant cellValue = pCell->dynamicCall("Value()");
    pCell->setProperty("Value", strBeginTime);

    // 结束时间
    QString strEndTime = m_pOperationInterFace->GetUiPointObject()->dateTimeEditEnd->text();
    pCell = pSheet->querySubObject("Cells(int, int)", 7, 6);
    // QVariant cellValue = pCell->dynamicCall("Value()");
    pCell->setProperty("Value", strEndTime);

    pCell = pSheet->querySubObject("Cells(int, int)", 9, 113);
    // QVariant cellValue = pCell->dynamicCall("Value()");
    pCell->setProperty("Value", strBeginTime);

    pCell = pSheet->querySubObject("Cells(int, int)", 9, 115);
    // QVariant cellValue = pCell->dynamicCall("Value()");
    pCell->setProperty("Value", strBeginTime);

    // 检查类别
    QString strCheckType = m_pOperationInterFace->GetUiPointObject()->jianceleibie_comboBox->currentText();
    pCell = pSheet->querySubObject("Cells(int, int)", 8, 6);
    // QVariant cellValue = pCell->dynamicCall("Value()");
    pCell->setProperty("Value", strCheckType);

    // 样品数量：
   // QString strSampleNum =  m_pOperationInterFace->GetUiPointObject()->label_yangpingshuliang->text();
   // strSampleNum.toInt(&bInt);
    QString strSampleNum = QString::number(iCloumNum);
    //if(bInt)
    {
        pCell = pSheet->querySubObject("Cells(int, int)",11, 6);
        // QVariant cellValue = pCell->dynamicCall("Value()");
        pCell->setProperty("Value", strSampleNum);
    }

    QVariant cellValue = pCell->dynamicCall("Value()");
   // qDebug() << "basic infomation fill cell :  " << cellValue.toString();
   // LOG_INFO("basic infomation writedata success row:%d ,column:%d,key:%s,value:%s ",11 , 6 ,cellValue.toString().toStdString().c_str());

    // 送检单位：
    QString strCompany = "成都领益";
    pCell = pSheet->querySubObject("Cells(int, int)", 5, 2);
    pCell->setProperty("Value", strCompany);

    QString strCeliang = m_pOperationInterFace->GetUiPointObject()->celiangrenyuan_lineEdit->text();
    pCell = pSheet->querySubObject("Cells(int, int)", 10, 113);
    // QVariant cellValue = pCell->dynamicCall("Value()");
    pCell->setProperty("Value", strCeliang);


    QString strShehe = m_pOperationInterFace->GetUiPointObject()->shenherenyuan_lineEdit->text();
    pCell = pSheet->querySubObject("Cells(int, int)", 11, 113);
    QVariant shenherenyuan = pCell->dynamicCall("Value()");
    //LOG_INFO("shenherenyuan is %s  ,%s",shenherenyuan.toString().toStdString().c_str() ,strShehe.toStdString().c_str() );
    pCell->setProperty("Value", strShehe);


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
#if 0
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
#endif
     return 0;
}

int ExcellPrecess::ReadFileData(QString strFilePath, QVector<RecvFile::STDetailData> &VectorData, int iFileType)
{
    QThread::sleep(2);
    int iRet = 0;
    if(0 != CheckFileExists(strFilePath))
    {
        // 模版文件不存在
        QString strError = "没有文件:";
        strError += strFilePath;
       // m_pOperationInterFace->MessageBoxInfomation("错误",strError);
        return -1;
    }
    if(1 == iFileType)
    {
        // 验证文件后缀为 excel
        QString strSuffix = GetFileSuffix(strFilePath);
        if(strSuffix != "xlsx" && strSuffix != "xls")
        {
            LOG_DEBUG("自动感知文件后缀错误,file:%s,iFileType:%d",strFilePath.toStdString().c_str(),iFileType);
            return -98;
        }

        iRet = ReadExcelData(strFilePath , VectorData);
    }
    else if(2 == iFileType)
    {
        QString strSuffix = GetFileSuffix(strFilePath);
        if(strSuffix != "xlsx" && strSuffix != "xls")
        {
            LOG_DEBUG("自动感知文件后缀错误,file:%s,iFileType:%d",strFilePath.toStdString().c_str(),iFileType);
            return -98;
        }
        iRet = ReadExcelDataNew(strFilePath , VectorData);
    }
    else if(3 == iFileType)
    {
        // 验证文件后缀为 txt
        QString strSuffix = GetFileSuffix(strFilePath);
        if(strSuffix != "txt" && strSuffix != "TXT")
        {
            LOG_DEBUG("自动感知文件后缀错误,file:%s,iFileType:%d",strFilePath.toStdString().c_str(),iFileType);
            return -98;
        }
        iRet = ReadTxtData(strFilePath , VectorData);
    }
    else
    {
        LOG_ERROR("ReadFileData iFileType is error :%d" ,iFileType);
        return -2;
    }
    LOG_INFO("ReadFileData return = %d ,iFileType=%d ,file:%s",iRet , iFileType, strFilePath.toStdString().c_str());
    return 0;
}

int ExcellPrecess::ReadExcelData(QString strFilePath, QVector<RecvFile::STDetailData> &VectorData)
{
    shared_ptr<CExcellPointMgr> pExcellPtr = InitExcellObject();
    if(nullptr == pExcellPtr || nullptr == pExcellPtr->m_pWorkBooks)
    {
        return -1;
    }

    QAxObject *pWorkbook = pExcellPtr->m_pWorkBooks->querySubObject("Open(const QString&)", strFilePath);
    if(nullptr == pWorkbook)
    {
        return -2;
    }

     //捕获异常
    m_pOperationInterFace->SetSlotExcelException(pWorkbook , strFilePath);
    //2 .获取所有工作簿
     qDebug() << "read  : filepath" << strFilePath ;
    QAxObject *pSheets = pWorkbook->querySubObject("Sheets");
    if(nullptr == pSheets)
    {
        pWorkbook->dynamicCall("Close()");
        return -3;
    }
    //3 . 打开工作簿
    qDebug() << "WriteData 3 : filepath" << strFilePath ;
    QAxObject *pSheet =pSheets->querySubObject("Item(int)", 1);
    if(nullptr == pSheet)
    {
        pWorkbook->dynamicCall("Close()");
        return -4;
    }

    // 4 .找出开始数据行列
    int iColumn = 1 ; // 在第一类 查找关键字 "序号"
    int iRow = 1;
    QVariant cellValue;
    while(true)
    {
        if(iRow > 100)
        {
            LOG_ERROR("获取 序号 关键字 失败 %d",iRow);
            return -5;
        }
        QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", iRow, iColumn);
        if(nullptr == pCell)
        {
            ++iRow;
            continue;
        }
        cellValue = pCell->dynamicCall("Value()");
        QString strValue = cellValue.toString();
        if(strValue.isEmpty())
        {
            ++iRow;
            continue;
        }
        if (strValue == "序号")
        {
            LOG_INFO("找到关键字 序号 行：%d",iRow);
            // 再找出数据开始列
            for(iColumn = 2; iColumn < 100 ; ++iColumn )
            {
                QAxObject *pCellInfo = pSheet->querySubObject("Cells(int, int)", iRow, iColumn);
                if (nullptr == pCellInfo)
                {
                    continue;
                }
                cellValue = pCellInfo->dynamicCall("Value()");
                QString strVauleData = cellValue.toString();
                if (strVauleData.isEmpty())
                {
                    continue;
                }
                if(strVauleData == "1")
                {
                    LOG_INFO("找到数据列 row=%d , column=%d",iRow , iColumn);
                    break;
                }
            }
            break;
        }
        ++iRow;
    }

    LOG_DEBUG("开始读取关键字：[%d,%d]",iRow,iColumn);
    // 5 开始读关键字
    int iKeyColumn = 2 ; // key 所在列 固定第2列
    QHash<int ,QString> m_mKeyHash;
    int ikeyRow = iRow + 1;
    while(true)
    {
        if(ikeyRow > 1000)
        {
            LOG_ERROR("获取关键key时 ikerrow error :%d",ikeyRow);
            break;
        }
        QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", ikeyRow, iKeyColumn);
        if(nullptr == pCell)
        {
            continue;
        }
        cellValue = pCell->dynamicCall("Value()");
        QString strValue = cellValue.toString();
        if(strValue.isEmpty())
        {
            break;
        }
        m_mKeyHash[ikeyRow] = strValue;
        ikeyRow++;
    }
    // 6 开始读数据
    LOG_DEBUG("开始读取测量数据：[%d,%d]",iRow,iColumn);
    int iValueCloumn = iColumn;
    while(true)
    {
        QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", iRow, iValueCloumn);
        if (nullptr == pCell)
        {
            continue;
        }
        cellValue = pCell->dynamicCall("Value()");
        QString strNum = cellValue.toString();
        if (strNum.isEmpty())
        {
            break;
        }

        int iValueRow = iRow + 1;
        RecvFile::STDetailData Value;
        for (iValueRow = iRow + 1 ; iValueRow < iRow + m_mKeyHash.size() + 1; ++iValueRow)
        {
            QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", iValueRow, iValueCloumn);
            if (nullptr == pCell)
            {
                continue;
            }
            cellValue = pCell->dynamicCall("Value()");
            QString strValue = cellValue.toString();
            if (strValue.isEmpty())
            {
                break;
            }
            auto it = m_mKeyHash.find(iValueRow);
            if(it == m_mKeyHash.end())
            {
                LOG_ERROR("获取key 错误 row:%d ,cloumn:%d,beginrow[%d,%d]",iValueRow, iValueCloumn,iRow,iColumn);
                continue;
            }
            RecvFile::STDimenSionData data;
            bool ok = false;
            data.strName = *it;
            data.dActual = strValue.toDouble(&ok);
            if(!ok)
            {
                LOG_ERROR("获取key 错误 row:%d ,cloumn:%d,beginrow[%d,%d],strvalue:%s",iValueRow, iValueCloumn,iRow,iColumn,strValue.toStdString().c_str());
                continue;
            }
            Value.m_mMeasuredValue[*it] = data;
            LOG_INFO("insert zhaofen data cell[%d,%d],%f",iValueRow, iValueCloumn,data.dActual);
        }
        VectorData.push_back(Value);
        ++iValueCloumn;
    }

    return 0;
}

int ExcellPrecess::ReadExcelDataNew(QString strFilePath, QVector<RecvFile::STDetailData> &VectorData)
{
    shared_ptr<CExcellPointMgr> pExcellPtr = InitExcellObject();
    if(nullptr == pExcellPtr || nullptr == pExcellPtr->m_pWorkBooks)
    {
        return -1;
    }

    QAxObject *pWorkbook = pExcellPtr->m_pWorkBooks->querySubObject("Open(const QString&)", strFilePath);
    if(nullptr == pWorkbook)
    {
        return -2;
    }

    //捕获异常
    m_pOperationInterFace->SetSlotExcelException(pWorkbook , strFilePath);
    //2 .获取所有工作簿
    qDebug() << "read  : filepath" << strFilePath ;
    QAxObject *pSheets = pWorkbook->querySubObject("Sheets");
    if(nullptr == pSheets)
    {
        pWorkbook->dynamicCall("Close()");
        return -3;
    }
    //3 . 打开工作簿
    qDebug() << "WriteData 3 : filepath" << strFilePath ;
    QAxObject *pSheet =pSheets->querySubObject("Item(int)", 1);
    if(nullptr == pSheet)
    {
        pWorkbook->dynamicCall("Close()");
        return -4;
    }

    // 4 . 在100行 100列内找出关键字  "元素"
    int iKeyColumn = 1 ; // key 所在列 固定第2列
    int iColumn = 1 ;
    int iRow = 1;
    QVariant cellValue;
    bool bFind = false;
    for(  ; iColumn < 100 ; ++iColumn)
    {
        for(  int i = 1; i < 100 ; ++i)
        {
           // LOG_DEBUG("开始读取单元格[%d ,%d]",i , iColumn);
            QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", i, iColumn);
            if(nullptr == pCell)
            {
                continue;
            }
            cellValue = pCell->dynamicCall("Value()");
            QString strValue = cellValue.toString();
            if(strValue.isEmpty())
            {
                continue;
            }

            if (strValue == "元素")
            {
                bFind = true;
                iRow = i;
                break;
            }
        }
        if(bFind)
        {
            iKeyColumn = iColumn;
            break;
        }
    }
    LOG_DEBUG("find  yuan su hang:%d",iRow);
    // 5 .找出开始数据列
    for( iColumn = iColumn + 1; iColumn < 100 ; ++iColumn )
    {
        QAxObject *pCellInfo = pSheet->querySubObject("Cells(int, int)", iRow, iColumn);
        if (nullptr == pCellInfo)
        {
            continue;
        }
        cellValue = pCellInfo->dynamicCall("Value()");
        QString strVauleData = cellValue.toString();
        if (strVauleData.isEmpty())
        {
            continue;
        }
        if(strVauleData == "LSL")
        {
            iColumn ++;
            QAxObject *pCellInfo = pSheet->querySubObject("Cells(int, int)", iRow, iColumn);
            if (nullptr == pCellInfo)
            {
                LOG_ERROR("pSheet->querySubObject eturn null :[%d,%d]",iRow , iColumn);
                return -10;
            }
            cellValue = pCellInfo->dynamicCall("Value()");
            QString strVauleData = cellValue.toString();
            if(strVauleData == "测量值")
            {
                LOG_INFO("找到数据列 row=%d , column=%d",iRow , iColumn);

            }
            else
            {
                iColumn ++;
            }
             break;
        }
    }

    // 5 开始读关键字
    int ikeyRow = iRow + 1;
    LOG_DEBUG("开始读取关键字：[%d,%d]",ikeyRow,iKeyColumn);

    QHash<int ,QString> m_mKeyHash;

    while(true)
    {
        if(ikeyRow > 1000)
        {
            LOG_ERROR("获取关键key时 ikerrow error :%d",ikeyRow);
            break;
        }
        QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", ikeyRow, iKeyColumn);
        if(nullptr == pCell)
        {
            ikeyRow++;
            continue;
        }
        cellValue = pCell->dynamicCall("Value()");
        QString strValue = cellValue.toString();
        if(strValue.isEmpty())
        {
            break;
        }
        m_mKeyHash[ikeyRow] = strValue;
        ikeyRow++;
    }
    // 6 开始读数据
    LOG_DEBUG("开始读取测量数据：[%d,%d]",iRow,iColumn);
    int iValueCloumn = iColumn;
    int iLoopCount = 0;
    while(true)
    {
        if(++iLoopCount > 1000)
        {
            LOG_ERROR("loop is too more");
            break;
        }
        QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", iRow + 1, iValueCloumn);  // 读取第一个数据
        if (nullptr == pCell)
        {
            continue;
        }
        cellValue = pCell->dynamicCall("Value()");
        QString strNum = cellValue.toString();
        if (strNum.isEmpty())
        {
            break;
        }

        int iValueRow = iRow + 1;
        RecvFile::STDetailData Value;
        for (iValueRow = iRow + 1 ; iValueRow < iRow + m_mKeyHash.size() + 1; ++iValueRow)
        {
            QAxObject *pCell = pSheet->querySubObject("Cells(int, int)", iValueRow, iValueCloumn);
            if (nullptr == pCell)
            {
                continue;
            }
            cellValue = pCell->dynamicCall("Value()");
            QString strValue = cellValue.toString();
            if (strValue.isEmpty())
            {
                break;
            }
            auto it = m_mKeyHash.find(iValueRow);
            if(it == m_mKeyHash.end())
            {
                LOG_ERROR("获取key 错误 row:%d ,cloumn:%d,beginrow[%d,%d]",iValueRow, iValueCloumn,iRow,iColumn);
                continue;
            }
            RecvFile::STDimenSionData data;
            bool ok = false;
            data.strName = *it;
            data.dActual = strValue.toDouble(&ok);
            if(!ok)
            {
                LOG_ERROR("获取key 错误 row:%d ,cloumn:%d,beginrow[%d,%d],strvalue:%s",iValueRow, iValueCloumn,iRow,iColumn,strValue.toStdString().c_str());
                continue;
            }
            Value.m_mMeasuredValue[*it] = data;
            LOG_INFO("insert zhaofen data cell[%d,%d],%f",iValueRow, iValueCloumn,data.dActual);
        }
        VectorData.push_back(Value);
        ++iValueCloumn;
    }
    LOG_DEBUG("ReadExcelDataNew read data count[%d]",VectorData.size());
    return 0;
}

int ExcellPrecess::ReadTxtData(QString strFilePath, QVector<RecvFile::STDetailData> &VectorData)
{
    QFile file(strFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text| QIODevice::ExistingOnly))
    {
        LOG_ERROR("ReadTxtData open file faild %s",strFilePath.toStdString().c_str()) ;
        return -1 ;
    }

    QTextStream in(&file);
    QString line;

    enum State { Idle, InBlock };
    State state = Idle;
    RecvFile::STDetailData TempData;
    while (!in.atEnd())
    {
        line = in.readLine().trimmed();

        if (line == ":BEGIN")
        {
            TempData.RestData();
            state = InBlock;
        } else if (line == ":END")
        {
            state = Idle;
            if(!TempData.m_mMeasuredValue.isEmpty())
            {
                VectorData.push_back(TempData);
                LOG_INFO("txt data 测量一件样本完成");
            }
        } else if (state == InBlock)
        {
            if (line.startsWith("FAI") || line.startsWith("\"FAI"))
            {
                RecvFile::STDimenSionData TemCeLiangValue;
                QStringList parts = line.split(QRegExp("\\s+")); // 正则匹配 空格 一个或多个
                if (parts.size() >= 2)
                {
                    QString faiKey = parts[0];
                    if(faiKey.startsWith("\""))
                    {
                        // 删除首尾两个引号
                        faiKey = faiKey.mid(1 , faiKey.size() - 2);

                    }
                    QString faiValue = parts[1];
                    qDebug() << "FAI Key:" << faiKey << "FAI Value:" << faiValue;
                    double dActual = faiValue.toDouble();
                    TemCeLiangValue.dActual = dActual;
                    TemCeLiangValue.strName = faiKey;
                    TempData.m_mMeasuredValue[faiKey] = TemCeLiangValue;
                    LOG_DEBUG("txt insert data key:%s ,value:%f",faiKey.toStdString().c_str(),TemCeLiangValue.dActual);
                }
            }
        }
    }

    file.close();

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
