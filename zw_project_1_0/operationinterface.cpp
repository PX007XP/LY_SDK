#include "operationinterface.h"
#include "ui_operationinterface.h"
#include <QThread>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QVector>
#include <QColor>
#include "recvfile.h"
#include <QList>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QStandardPaths>
#include <QDir>
#include "globle.h"
#include "logger.h"
#include "configobject.h"
#include "tempdata.h"
#include <QTableView>
#include <QToolBar>


OperationInterface::OperationInterface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OperationInterface)
{
    ui->setupUi(this);

    qDebug()<<"主线程id:" << QThread::currentThreadId();

    // 在你的 main 函数或其他初始化代码中注册该类型
    qRegisterMetaType<RecvFile::STDetailData>("STDetailData");

    CheckDirectoryExists("./log");
    QString strLogFileName = "./log/logget.txt";
    Logger* pLogger = new Logger(strLogFileName);
    if(nullptr == pLogger)
    {
        qDebug()<< "Logger faild";
        QMessageBox::information(this,"提示","日志文件失败");
    }
    else
    {
        g_pLogger = pLogger;
    }

    // 读取配置文件
    ConfigObject config;
    config.ReadConfig();

    //创建子线程
    QThread* m_pSocketThread = new QThread;

    m_pRecvFileWorker = new RecvFile;

    m_pRecvFileWorker->moveToThread(m_pSocketThread);

    // 开启tcp线程
    m_pSocketThread->start();


    m_pExcellWork = new ExcellPrecess();
    if(m_pExcellWork)
    {
        m_pExcellWork->Init(this);
    }
    m_pHttpNetObject = new HttpNetObject();
    if(m_pHttpNetObject)
    {
        m_pHttpNetObject->Init(this);
    }

    // 点击连接按钮的信号函数
    connect(this,&OperationInterface::StartConnect , m_pRecvFileWorker , &RecvFile::ConnectServer);
    // socket 连接成功的信号函数
    connect(m_pRecvFileWorker ,&RecvFile::ConnectOk ,this,&OperationInterface::ConncetServerSucces );
    // socket 连接成功的信号函数
    connect(m_pRecvFileWorker ,&RecvFile::ConnectError ,this,&OperationInterface::ConnectServerFaild );
    // 接收消息的信号函数 测试使用
    connect(m_pRecvFileWorker ,&RecvFile::MessageToUi ,this,&OperationInterface::RecvSocketMessage );
    // 接收消息的信号函数 测试使用
    connect(m_pRecvFileWorker ,&RecvFile::ResultToUi ,this,&OperationInterface::ShowDetailMesage );
    // 点击获取消息的信号函数
    connect(this,&OperationInterface::SendMessage , m_pRecvFileWorker , &RecvFile::SendMessageToServer);




   // m_pSocket = new QTcpSocket();
    //connect(m_pSocket,SIGNAL(readyRead()),this,SLOT(RecieveData()));

    // HTTP测试

    //数据显示逻辑
    m_tempData=new TempData(ui->ShowtableView);
    connect(m_tempData,&TempData::dataChanged,this,&OperationInterface::DataChanged);
    connect(ui->radioButton,&QRadioButton::clicked,m_tempData,&TempData::modslot);
    connect(ui->ClearDataButton,&QPushButton::clicked,m_tempData,&TempData::dataClear);
    connect(m_tempData,&TempData::setLaybelText,this,&OperationInterface::LaybelText);
    UiInit();
    GetLocalIp();

    // 数据感知初始化
    InitWatcher();
}

OperationInterface::~OperationInterface()
{
   // m_pSocketThread->quit();
    //m_pSocketThread->wait();
    //m_pSocketThread->deleteLater();
   // m_pRecvFileWorker->deleteLater();

   if(m_pExcellWork)
   {
       delete m_pExcellWork;
       m_pExcellWork = nullptr;
   }
    delete ui;
}

void OperationInterface::ConncetServerSucces()
{
    QMessageBox::information(this,"提示","已经连接成功");
}

void OperationInterface::ConnectServerFaild()
{
    QMessageBox::information(this,"提示","连接失败");
}

void OperationInterface::RecvSocketMessage(QByteArray szMessage)
{
    QString strText1 = QString::fromLocal8Bit(szMessage);
    qDebug()<< "gb2312:  " <<strText1;

    QVector<QColor> colors = {Qt::red , Qt::blue ,Qt::black,Qt::cyan ,Qt::magenta ,Qt::darkRed,Qt::green};
    int iRandId = QRandomGenerator::global()->bounded(colors.size());
  //  ui->showdataEdit->setTextColor(colors[iRandId]);
  //  ui->showdataEdit->append(strText1);
}

void OperationInterface::ShowDetailMesage(RecvFile::STDetailData stResult)
{
    QVector<QColor> colors = {Qt::red , Qt::blue ,Qt::black,Qt::cyan ,Qt::magenta ,Qt::darkRed,Qt::green};
    QString strParid = "partid:" + stResult.m_strPartID;
   // ui->showdataEdit->append(strParid);
    QString strTime = "时间:" + stResult.m_strDateTime;
   // ui->showdataEdit->append(strTime);

    QString strHeGe = "合格:" + QString(stResult.m_cQualified);
   // ui->showdataEdit->append(strHeGe);

    QString strUnits = "测量单位:" + stResult.m_strUnits;
   // ui->showdataEdit->append(strUnits);
    qDebug() << "解析数据展示  :" << strParid << ", " << strTime << ", " << strHeGe << ", " << strUnits;

    auto it = stResult.m_mMeasuredValue.begin();
    for( it ; it !=stResult.m_mMeasuredValue.end();++it )
    {
        QString strKeyName = QString::fromUtf8("理论值:");
        QString strShow;
        strShow = it->strName;
        strShow += strKeyName;
        strShow +=  QString::number(it->dTheo);
        strShow += "上偏差:";
        strShow +=  QString::number(it->dUpperLimit);
        strShow += "下偏差:";
        strShow +=  QString::number(it->dLowerLimit);
        strShow += "实际值:";
        strShow +=  QString::number(it->dActual);
        int iRandId = QRandomGenerator::global()->bounded(colors.size());
     //   ui->showdataEdit->setTextColor(colors[iRandId]);
      //  ui->showdataEdit->append(strShow);
    }

    m_vRecvData.push_back(stResult);
    if(m_tempData){
        m_tempData->ShowData(stResult);
    }
}

void OperationInterface::SetSlotExcelException(QAxObject *pWorkbook, QString strFile)
{
    connect(pWorkbook, SIGNAL(exception(int, const QString&, const QString&, const QString&)),
            this, SLOT(handleExcelException(int, const QString&, const QString&, const QString&)));
}

void OperationInterface::ShowMessageBoxInfo(QString strMessageType, QString strShowData)
{
    QMessageBox::information(this,strMessageType,strShowData);
}

void OperationInterface::on_connectButton_clicked()
{
    QString strIp = ui->IpEdit->text();
    QString strPort = ui->PortEdit->text();

    emit StartConnect(strIp,strPort.toUShort());
   // m_pSocket->connectToHost(strIp,strPort.toInt());

   // m_pSocket->write("连接成功");
}


void OperationInterface::on_GetDataButton_clicked()
{
    //m_pSocket->write("mResult");
    //QString strMessage = "msResult";
    QString strMessage = g_strPacketHeader;
    emit SendMessage(strMessage);
}

// 接收消息的信号函数
void OperationInterface::RecieveData()
{
   /* QByteArray szReData = m_pSocket->readAll();
    qDebug()<< szReData;
    QString strText = QString::fromUtf8(szReData);
    qDebug()<< "utf-8:   " <<strText;
    QString strText1 = QString::fromLocal8Bit(szReData);
    qDebug()<< "gb2312:  " <<strText1;
    ui->showdataEdit->append(strText1);
*/
}

void OperationInterface::on_WriteFilepushButton_clicked()
{
    // 生成文件并上传
    //const char* pString = "./template/880-GNT022-03-003.xlsm";
    //const char* pString = "D:\\S_wroking\\123.xlsx";
    //QString strFilePath = QString::fromUtf8(pString);
    /*
    QString currentPath = QDir::currentPath();
    QString strFilePath = currentPath + "/template/880-GNT022-03-003.xlsm";
    */
    QString strFilePath;
    int iRet = GetMobanFileName(strFilePath);
    if(0 == iRet)
    {
        int iRet = m_pExcellWork->WriteData(&m_vRecvData , strFilePath);
        qDebug() << "WriteData return " << iRet;
        LOG_DEBUG("WriteData return %d",iRet);
    }
    else
    {
        LOG_ERROR("moban file is error:%s ",strFilePath.toStdString().c_str());
    }



    // 上传文件
    on_pushFileButton_clicked();
}





void OperationInterface::on_LoginPushButton_clicked()
{
    QString strPassword = ui->PasswordEdit->text();
    QString strUserName = ui->UserEdit->text();
    if(strPassword.isEmpty() || strUserName.isEmpty() )
    {
        QString strData = "123";
        QMessageBox::information(this,"错误",strData);
    }
    m_pHttpNetObject->LoginPost(strUserName , strPassword);

}


void OperationInterface::on_GetInfoButton_clicked()
{
    //QString strMmsID = "mmsdCY1241017157";
    QString strMmsID = ui->NumberEdit->text();
    if(strMmsID.isEmpty())
    {
       QMessageBox::information(this,"提示","请输入子单号");
        return;
    }
    m_pHttpNetObject->GetCheckTaskData(strMmsID);
}


void OperationInterface::on_pushFileButton_clicked()
{
    if(m_strPushFilePath.isEmpty())
    {
        QMessageBox::information(this,"提示","没有生成文件");
        return ;
    }
    m_pHttpNetObject->PostFileToNet(m_strPushFilePath);
}

int OperationInterface::GetMobanFileName(QString& strFilePath)
{
    QString strRootPath = ui->MobanlujinEdit->text();
    QString strProjectPath = ui->PathcomboBox->currentText();
    QString strTypePath = ui->TypecomboBox->currentText();
    QString strFileName = ui->FilecomboBox->currentText();
    if(strRootPath.isEmpty() || strProjectPath.isEmpty() || strTypePath.isEmpty() || strFileName.isEmpty())
    {
        QMessageBox::information(this,"错误","请先选择模版");
        return -1 ;
    }
    strFilePath = strRootPath /* + "\\"*/ + strProjectPath + "\\" + strTypePath + "\\" + strFileName;
    qDebug()<<"********************** " << strFilePath;
    return 0;
}

void OperationInterface::on_ComCheckButton_clicked()
{
    int iRet = m_pHttpNetObject->CompeleteCheck( );
    // 删除保存的文件
    QFile file(m_strPushFilePath);
    if(!file.exists())
    {
        LOG_ERROR("complete check is error :no file:%s",m_strPushFilePath.toStdString().c_str());
    }
    else
    {
        int iLastIndexName = m_strPushFilePath.lastIndexOf('/');
        if(-1 == m_strPushFilePath)
        {
            iLastIndexName = m_strPushFilePath.lastIndexOf('\\');
        }
        if(-1 == m_strPushFilePath)
        {
            //
            return ;
        }
        QString strFileName = m_strPushFilePath.mid(iLastIndexName+1);
        qDebug() << "file name is :" << strFileName;
        QString strNewFilePath = ui->saveFilePathEdit->text() + "/" + strFileName;
        file.rename(strNewFilePath);
        m_strPushFilePath.clear();

        //todo  调用清空显示界面数据接口

        LOG_INFO("complete check return=%d , filepath=%s ,%s",iRet,strNewFilePath.toStdString().c_str());
    }
}

void OperationInterface::MessageBoxInfomation(QString strType, QString strValue)
{
    QMessageBox::information(this,strType,strValue);
}

void OperationInterface::SetUIMessageInfo(QString strUiName, QString strData)
{
    if( g_strReqNo == strUiName)
    {
        ui->label_shenqingdanhao->setText(strData);
    }
    else if(g_strReqUserName == strUiName)
    {
        ui->lable_shenqingrenyuan->setText(strData);
    }
    else if(g_strReqUnicom == strUiName)
    {
        ui->label_songjiandanwei->setText(strData);
    }
    else if(g_strDeviceName == strUiName)
    {
        ui->label_xiangmmumingchen->setText(strData);
    }
    else if(g_strDeviceNo == strUiName)
    {
        ui->label_jitai->setText(strData);
    }
    else if(g_strReqTime == strUiName)
    {
        ui->label_shenqingshijian->setText(strData);
    }
    else if(g_strTestCon == strUiName)
    {
        ui->label_jianceyaoqiu->setText(strData);
    }
    else if(g_strReportType == strUiName)
    {
        ui->label_jianyanleibie->setText(strData);
    }
    else if(g_strProjectClassId == strUiName)
    {
        ui->label_jiancexiangmu->setText(strData);
    }
    else if(g_strProjectStageId == strUiName)
    {
        ui->label_gongxu->setText(strData);
    }
    else if(g_strSatageNo == strUiName)
    {
        ui->label_jiajubianhao->setText(strData);
    }
    else if(g_strOrgCode == strUiName)
    {
        ui->label_muxuehao->setText(strData);
    }
    else if(g_strRemark == strUiName)
    {
        ui->label_beizhu->setText(strData);
    }
    else if(g_strRevArtTime == strUiName)
    {
        ui->label_shoujianshijian->setText(strData);

        QDateTime dateTime = QDateTime::fromString(strData, "yyyy-MM-dd HH:mm:ss");
        ui->dateTimeEditStart->setDateTime(dateTime);
    }
    else if(g_strReqNo == strUiName)
    {

    }
    else
    {

    }
}

void OperationInterface::SavePushFilePath(QString strFileName)
{
    m_strPushFilePath = strFileName;
}

void OperationInterface::on_ClearDataButton_clicked()
{
   // const char* pString = "D:\\S_wroking\\880-GNT022-03-003.xlsm";
    QString currentPath = QDir::currentPath();
    QString strFile = currentPath + "/template/880-GNT022-03-003.xlsm";
    m_pExcellWork->CleanSheetData(strFile);
    QMessageBox::information(this,"提示","清理成功");
    m_vRecvData.clear();
}

void OperationInterface::handleExcelException(int code, const QString &source, const QString &desc, const QString &help)
{
    qDebug() << "Exception code:" << code;
    qDebug() << "Source:" << source;
    qDebug() << "Description:" << desc;
    qDebug() << "Help:" << help;
    QMessageBox::information(this,"错误","文件异常");

}

void OperationInterface::GetLocalIp()
{
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    QString strLocalIp ;
    foreach (const QNetworkInterface &interface, interfaces)
    {
        if (interface.flags().testFlag(QNetworkInterface::IsUp) &&
            interface.flags().testFlag(QNetworkInterface::IsRunning) &&
            !interface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            // 遍历每个接口，获取其IP地址
            QList<QNetworkAddressEntry> entries = interface.addressEntries();
            foreach (const QNetworkAddressEntry &entry, entries)
            {
                QHostAddress ip = entry.ip();
                // 过滤掉IPv6地址和本地回环地址
                if (ip.protocol() == QAbstractSocket::IPv4Protocol && ip != QHostAddress::LocalHost)
                {
                    qDebug() << "Interface efect:" << interface.humanReadableName() << "IP Address:" << ip.toString();
                    if(interface.humanReadableName().contains(g_strIpAddressKey))
                    {
                        m_strLocalIp = ip.toString();
                    }
                    // 如果没有找到WLAN或以太网接口，则选择第一个符合条件的IP地址
                    if (strLocalIp.isEmpty())
                    {
                        strLocalIp = ip.toString();
                    }
                    LOG_INFO("ip loop name:%s , ip:%s ",interface.humanReadableName().toStdString().c_str() , ip.toString().toStdString().c_str());
                }
            }
        }
    }
    if(m_strLocalIp.isEmpty() && !strLocalIp.isEmpty())
    {
        m_strLocalIp = strLocalIp;
        LOG_ERROR("选择第一个ip作为连接地址，%s",m_strLocalIp.toStdString().c_str());
    }
    ui->IpEdit->setText(m_strLocalIp);
    LOG_STATS("ip chose name:%s , ip:%s ",m_strLocalIp.toStdString().c_str() , strLocalIp.toStdString().c_str());
}

QFileInfo OperationInterface::FindLatestFile(const QString &strPath)
{
    QDir directory(strPath);
    if (!directory.exists())
    {
        LOG_ERROR("FindLatestFile path[%s] is null",strPath.toStdString().c_str());
        return QString();
    }

    // 获取所有文件
    QFileInfoList fileList = directory.entryInfoList(QDir::Files);

    if (fileList.isEmpty())
    {
        LOG_ERROR("FindLatestFile path[%s] 目录中没有文件",strPath.toStdString().c_str());
        return QString();
    }

    // 找出最新的文件
    QFileInfo latestFile;
    foreach (const QFileInfo &fileInfo, fileList)
    {
        if (!latestFile.exists() || fileInfo.lastModified() > latestFile.lastModified())
        {
            latestFile = fileInfo;
        }
    }

    return latestFile;
}

int OperationInterface::InitWatcher()
{
    m_strListeningPath = ui->zhidongganzhi_lineEdit->text();
    //
   // if(m_strListeningPath.isEmpty())
   // {
   //     QMessageBox::information(this,"提示","请输入自动感知路径");
    //    return -1;
    //}
    //QDir directory(m_strListeningPath);
   // if(!directory.exists())
   // {
   //     QMessageBox::information(this,"提示","自动感知文件夹不存在");
   //     return -2;
   // }
   // m_Watcher.addPath(m_strListeningPath);
    m_bListening = false;

    connect(&m_Watcher, &QFileSystemWatcher::directoryChanged, this, &OperationInterface::onDirectoryChanged);
    return 0;
}

void OperationInterface::StartListening()
{
    if(!m_bListening)
    {
        m_strListeningPath = ui->zhidongganzhi_lineEdit->text();
        if(m_strListeningPath.isEmpty())
        {
            QMessageBox::information(this,"提示","请输入路径");
            LOG_ERROR("开始文件感知时 没有输入文件路径");
            return ;
        }
        QDir directory(m_strListeningPath);
        if(!directory.exists())
        {
            QMessageBox::information(this,"提示","文件夹不存在");
            LOG_ERROR("开始文件感知时 路径不存在");
            return ;
        }
        m_Watcher.addPath(m_strListeningPath);
        m_bListening = true;
        LOG_INFO("开始文件感知:%s",m_strListeningPath.toStdString().c_str());
    }
}

void OperationInterface::StopListening()
{
    if(m_bListening)
    {
        m_Watcher.removePath(m_strListeningPath);
        m_bListening = false;
        m_strListeningPath.clear();
        LOG_INFO("停止文件感知:%s",m_strListeningPath.toStdString().c_str());
    }

}
#if 0
bool isFileInUse(const QString &filePath) {
    HANDLE handle = CreateFile(
        filePath.toStdWString().c_str(),
        GENERIC_READ,
        FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
        );
    if (handle == INVALID_HANDLE_VALUE) {
        DWORD errorCode = GetLastError();
        if (errorCode == ERROR_SHARING_VIOLATION) {
            qDebug() << "文件被占用:" << filePath;
            return true;
        } else {
            qWarning() << "无法打开文件:" << filePath << "错误码:" << errorCode;
        }
    } else {
        CloseHandle(handle);
    }

    return false;
}
#endif
void OperationInterface::onDirectoryChanged(const QString &strPath)
{
    LOG_DEBUG("感知到文件变化");
    if(!m_bListening)
    {
        return;
    }
    QDir directory(strPath);
    if(!directory.exists())
    {
        return ;
    }
    QFileInfo FileInfo =FindLatestFile(strPath);

    // 检查文件是否被占用
   // if (!isFileInUse(FileInfo.filePath()))
   // {
   //     LOG_ERROR("");
   // }

    // 去重
    if(RemoveRepetiton(FileInfo))
    {
        return;
    }
    // 处理文件 todo
    if(nullptr == m_pExcellWork)
    {
        LOG_ERROR("onDirectoryChanged m_pExcellWork is null");
        return ;
    }
    int iFileType = GetSheBeiType();
    if(0 == iFileType )
    {
        LOG_ERROR("onDirectoryChanged iFileType is error :%d",iFileType);
        return;
    }
    //QString strFilePathName = FileInfo.filePath()
    int iRet = m_pExcellWork->ReadFileData(FileInfo.absoluteFilePath() , m_vRecvData , iFileType);
    LOG_INFO("自动感知到文件:%s,iFielType:%d ,iRet=%d",FileInfo.absoluteFilePath().toStdString().c_str(), iFileType,iRet);
}


void OperationInterface::on_ShowDataButton_clicked()
{
    QString strFilePath;
    int iRet = GetMobanFileName(strFilePath);
    if(0 == iRet)
    {
        m_tempData->LoadData(strFilePath,ui->label_yangpingshuliang->text().toInt());
    }
    else
    {
        LOG_ERROR("moban file is error :%s",strFilePath.toStdString().c_str());
    }

}


void OperationInterface::on_MobanlujinEdit_editingFinished()
{
    // 读取路径下的文件
    QString strMoBanRootPath = ui->MobanlujinEdit->text();
    if(strMoBanRootPath.isEmpty())
    {
        return ;
    }

    // 读取路径
    // 创建 QDir 对象
    QDir firstDir(strMoBanRootPath);
    if(!firstDir.exists())
    {
        QMessageBox::information(this,"提示","文件夹不存在");
    }

    // 设置过滤器，只获取目录
    firstDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    ui->PathcomboBox->clear();
    // 获取目录列表
    QStringList directories = firstDir.entryList();

    ui->PathcomboBox->addItems(directories);
    for (const QString &dirName : directories)
    {
        qDebug() << dirName;
    }
    QString strPath = ui->PathcomboBox->currentText();
    strPath = strMoBanRootPath + "/" + strPath;
    SetDirPathComboByDirPath(strPath);

}

void OperationInterface::DataChanged(int num, QString key, double value)
{
    if(num<0||num>=m_vRecvData.size()||m_vRecvData.empty()) return;
    auto& item=m_vRecvData[num];
    for(auto it=item.m_mMeasuredValue.begin();it!=item.m_mMeasuredValue.end();it++){
        if(it.key() == key){
            it.value().dActual=value;
            //m_tempData->ShowData(item);
        }
    }
}

void OperationInterface::LaybelText(QString text)
{
    if(text == "OK"){
        ui->label_21->setText(text);
        // 设置字体颜色和字体大小
        ui->label_21->setStyleSheet("color: green;");
    }else if (text == "NG"){
        ui->label_21->setText(text);
        // 设置字体颜色和字体大小
        ui->label_21->setStyleSheet("color: red;");
    }
}

int OperationInterface::UiInit()
{
    //ui->dateTimeEditStart->setCalendarPopup(true);
    //ui->dateTimeEditStart->setDateTime(QDateTime::currentDateTime());  // 设置当前日期时间
    //ui->dateTimeEditStart->setDisplayFormat("yyyy-MM-dd HH:mm:ss");  // 设置显示格式

    //ui->dateTimeEditEnd->setDateTime(QDateTime::currentDateTime());  // 设置当前日期时间
    //ui->dateTimeEditEnd->setDisplayFormat("yyyy-MM-dd HH:mm:ss");  // 设置显示格式
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    ui->saveFilePathEdit->setText(desktopPath);

    return 0;
}

int OperationInterface::SetDirPathComboByDirPath(QString strDirPath)
{
    if(strDirPath.isEmpty())
    {
        return -1;
    }
    QDir secondDir(strDirPath);

    secondDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    QStringList directories;
    directories = secondDir.entryList();
    ui->TypecomboBox->clear();
    ui->TypecomboBox->addItems(directories);
    QString strPath = ui->TypecomboBox->currentText();
    strPath = strDirPath + "/" + strPath;
    SetFileComboByDirPath(strPath);
    return 0;
}

int OperationInterface::SetFileComboByDirPath(QString strDirPath)
{
    // 设置第层目录
    if(strDirPath.isEmpty())
    {
        return -1;
    }

    // 创建 QDir 对象
    QDir fileDir(strDirPath);

    // 获取文件夹下的所有文件
    QStringList fileList = fileDir.entryList(QDir::Files);
    if(fileList.isEmpty())
    {
        return -2;
    }
    ui->FilecomboBox->clear();
    ui->FilecomboBox->addItems(fileList);
    return 0;
}

void OperationInterface::on_PathcomboBox_activated(int index)
{
    QString strText = ui->PathcomboBox->currentText();
    QString strPath = ui->MobanlujinEdit->text();
    strPath = strPath + "/" + strText;
    SetDirPathComboByDirPath(strPath);
}


void OperationInterface::on_TypecomboBox_activated(int index)
{
    QString strText = ui->PathcomboBox->currentText();
    QString strPath = ui->MobanlujinEdit->text();
    QString strSecondPath = ui->TypecomboBox->currentText();
    strPath = strPath + "/" + strText + "/" + strSecondPath;
    SetFileComboByDirPath(strPath);
}


void OperationInterface::on_FilecomboBox_activated(int index)
{

}


void OperationInterface::on_caijiTypecomboBox_activated(int index)
{
    QString strText = ui->caijiTypecomboBox->currentText();
    if(strText == "自动感知")
    {
        StartListening();
    }
    else
    {
        StopListening();
    }

}


int OperationInterface::GetSheBeiType()
{
    QString strText = ui->sehbeicomboBox->currentText();
    int iFileType = 0;
    // 文件感知类型 1 老兆丰 2 新兆丰 3 MIV
    if(strText == "兆丰1")
    {
        iFileType = 1;
    }
    else if(strText == "兆丰2")
    {
        iFileType = 2;
    }
    else if(strText == "MIV")
    {
        iFileType = 3;
    }
    //LOG_STATS("文件感知文件类型发生变化：%d",iFileType);
    return iFileType;
}

bool OperationInterface::RemoveRepetiton(QFileInfo fileInfo)
{
    QString strFileName  = fileInfo.fileName();
    auto it = m_mDealFile.find(strFileName);
    if(it != m_mDealFile.end())
    {
        if(*it = fileInfo.size())
        {
            return true;
        }
    }
    else
    {
        m_mDealFile[strFileName] = fileInfo.size();
    }
    return false;
}


void OperationInterface::on_zhidongganzhi_lineEdit_editingFinished()
{
    if(m_bListening)
    {
        StopListening();
    }
    QString strText = ui->caijiTypecomboBox->currentText();
    if(strText == "自动感知")
    {
        StartListening();
    }
}

