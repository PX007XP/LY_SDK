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
#include <QMenuBar>
#include <QPushButton>
#include "tcpserverthread.h"

QMenuBar *menuBar = nullptr;

QString g_strZidonggaanzhi = "数据接口2";
QString g_strShujuduijie = "数据接口1";

OperationInterface::OperationInterface(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OperationInterface)
{
    ui->setupUi(this);

    qDebug()<<"主线程id:" << QThread::currentThreadId();
   // LoadingDialog* ldd=new LoadingDialog(this);
   // ldd->move(this->pos().x() + 50, this->pos().y() + 500); // 在父窗口的右下角偏移 50 像素
    //ldd->show();

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
    config.ReadConfig(this);


    //创建子线程
    m_pSocketThread = new QThread;

    m_pRecvFileWorker = new RecvFile;

    m_pRecvFileWorker->moveToThread(m_pSocketThread);

    // 开启tcp线程
    m_pSocketThread->start();

    // 开启tcpserver

    TcpServerThread* pServerThread = new TcpServerThread;
    if( pServerThread)
    {
        m_pServerObject = pServerThread;
    }

    m_pSocketThreadServer = new QThread;

    if(m_pSocketThreadServer && m_pServerObject)
    {
        m_pServerObject->moveToThread(m_pSocketThreadServer);
    }
    else
    {
        LOG_ERROR("m_pSocketThreadServer or m_pServerThread is null  ");
    }

    m_pSocketThreadServer->start();
    m_pServerObject->runServer();

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
    // 接收消息的信号函数 测试使用 oMM
    connect(m_pRecvFileWorker ,&RecvFile::ResultToUi ,this,&OperationInterface::ShowDetailMesage );
    // 接收消息的信号函数 测试使用 CMM
    connect(m_pServerObject ,&TcpServerThread::CMMResultToUi ,this,&OperationInterface::ShowDetailMesageCMM );
    // 点击获取消息的信号函数
    connect(this,&OperationInterface::SendMessage , m_pRecvFileWorker , &RecvFile::SendMessageToServer);




   // m_pSocket = new QTcpSocket();
    //connect(m_pSocket,SIGNAL(readyRead()),this,SLOT(RecieveData()));

    // HTTP测试

    //数据显示逻辑
    // 创建菜单栏
    menuBar = new QMenuBar(this);


    // 创建文件菜单
    QMenu *fileMenu = menuBar->addMenu("设置");
    // 创建菜单项
    QAction *newAction = new QAction("子界面", this);
    // 将菜单项添加到文件菜单
    fileMenu->addAction(newAction);
    m_widget=new QWidget();
    m_widget->hide();
    ui->radioButton->setParent(m_widget);
    ui->radioButton->hide();
    ui->label_6->setParent(m_widget);
    ui->lineEdit_3->setParent(m_widget);
    ui->lineEdit_3->setMinimumWidth(500);
    // 创建一个栅格布局
    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(ui->radioButton,0,0);
    layout->addWidget(ui->label_6,1,0);
    layout->addWidget(ui->lineEdit_3,1,1);
    // 设置窗口的布局
    m_widget->setLayout(layout);
    m_widget->setWindowModality(Qt::ApplicationModal);

    config.InitJsonObject(this);
    // 连接信号和槽
    connect(newAction, &QAction::triggered, this, &OperationInterface::sonWidget);

    ui->verticalLayout_2->setContentsMargins(0, 30, 0, 0); // 留出30像素的顶部空间给菜单栏
    m_tempData=new TempData(ui->ShowtableView);
    connect(m_tempData,&TempData::dataChanged,this,&OperationInterface::DataChanged);
    connect(ui->radioButton,&QRadioButton::clicked,m_tempData,&TempData::modslot);
    connect(ui->ClearDataButton,&QPushButton::clicked,m_tempData,&TempData::dataClear);
    connect(m_tempData,&TempData::setLaybelText,this,&OperationInterface::LaybelText);
    connect(ui->ShowtableView ,&QTableView::clicked,this, &OperationInterface::ClikedInfoCell);
    setLayout(ui->verticalLayout_2);
    UiInit();
    GetLocalIp();

    // 数据感知初始化
    InitWatcher();
}

OperationInterface::~OperationInterface()
{
    LOG_INFO("程序 主动释放");

    if(m_pSocketThread)
    {
        QMetaObject::invokeMethod(m_pRecvFileWorker, "stopWorking",
                                  Qt::QueuedConnection);
        m_pSocketThread->quit();
        m_pSocketThread->wait();
        m_pSocketThread->deleteLater();
        m_pSocketThread = nullptr;
    }

    LOG_INFO("程序 主动释放1");
    if(m_pRecvFileWorker)
    {
        delete m_pRecvFileWorker;
        m_pRecvFileWorker = nullptr;
    }

    if(m_pSocketThreadServer)
    {
        if(m_pServerObject)
        {
            m_pServerObject->CloseServer();
        }
       // QMetaObject::invokeMethod(m_pServerObject, "stopWorking",Qt::QueuedConnection);
        m_pSocketThreadServer->quit();
        m_pSocketThreadServer->wait();
        m_pSocketThreadServer->deleteLater();
        m_pSocketThreadServer = nullptr;
    }
    if(m_pServerObject)
    {
        delete m_pServerObject;
        m_pServerObject = nullptr;
    }

    LOG_INFO("程序 主动释放2");
   if(m_pExcellWork)
   {
       delete m_pExcellWork;
       m_pExcellWork = nullptr;
   }
   LOG_INFO("程序 主动释放3");
   if(menuBar)
   {
       delete menuBar;
       menuBar = nullptr;
   }
    LOG_INFO("程序 主动释放4");

   if(m_tempData)
   {
       delete m_tempData;
       m_tempData = nullptr;
   }
    LOG_INFO("程序 主动释放5");
   if(g_pLogger)
   {
       delete g_pLogger;
   }
    LOG_INFO("程序 主动释放6");
    delete ui;
}

void OperationInterface::ConncetServerSucces()
{
    QMessageBox::information(this,"提示","已经连接成功");
}

void OperationInterface::ConnectServerFaild()
{
    //HideLoading();
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

int OperationInterface::DealMerageMessage(RecvFile::STDetailData &stResult)
{
    int iNowTestCount = m_vRecvData.size(); // 现有的测量件的数量
    if(0 == iNowTestCount)
    {
        m_vRecvData.push_back(stResult);
        LOG_DEBUG("插入第一条数据");
        return 0;
    }
    // 判断这次的数据是否需要新开一列
    if(m_vRecvData.size() == m_iLastInsertDataColumn + 1)
    {
        //1. 数据和最后一列重复 继续新增列
        //2.数据部重复 代表是新的数据 需要从第0 列开始 融合
        RecvFile::STDetailData &LastData = m_vRecvData.last();
        // 验证一个指标就可以了
        auto it_insert_first = stResult.m_mMeasuredValue.begin();
        auto it = LastData.m_mMeasuredValue.find(it_insert_first.key());
        if(it == LastData.m_mMeasuredValue.end())
        {
            auto it_first =  m_vRecvData.begin();
            if(it_first == m_vRecvData.end())
            {
                LOG_ERROR("插入数据时  数据发生错乱，结束插入");
                return -1;
            }
            for(auto it_insert= stResult.m_mMeasuredValue.begin(); it_insert != stResult.m_mMeasuredValue.end();++it_insert )
            {
                it_first->m_mMeasuredValue[it_insert.key()] = it_insert.value();
            }

            m_iLastInsertDataColumn = 0;
            LOG_DEBUG("新的数据开始融合[%d]",m_iLastInsertDataColumn);
        }
        else
        {
            m_vRecvData.push_back(stResult);
            m_iLastInsertDataColumn++;
            LOG_DEBUG("插入新的列数据[%d]",m_iLastInsertDataColumn);
        }
    }
    else if(m_vRecvData.size() > m_iLastInsertDataColumn + 1)
    {
        auto& it_data = m_vRecvData[ m_iLastInsertDataColumn + 1];
        for(auto it_insert= stResult.m_mMeasuredValue.begin(); it_insert != stResult.m_mMeasuredValue.end();++it_insert )
        {
            it_data.m_mMeasuredValue[it_insert.key()] = it_insert.value();
        }
        m_iLastInsertDataColumn++;
        LOG_DEBUG("新的数据融合插入[%d]",m_iLastInsertDataColumn);
    }
    else
    {
        LOG_ERROR("插入数据时上次插入的记录错误:%d ,%d，结束插入",m_iLastInsertDataColumn , m_vRecvData.size());
    }
    return m_iLastInsertDataColumn;
}

int OperationInterface::DealMerageMessage(QVector<RecvFile::STDetailData> VRecvData)
{
    int i = 0;
    foreach (RecvFile::STDetailData stResult, VRecvData)
    {
        if(m_vRecvData.size() == i)
        {
            m_vRecvData.push_back(stResult);
            LOG_INFO("文件感知插入数据");
        }
        else if(m_vRecvData.size() > i)
        {
            auto& OldData =  m_vRecvData[i];
            for(auto it_insert= stResult.m_mMeasuredValue.begin(); it_insert != stResult.m_mMeasuredValue.end();++it_insert )
            {
                OldData.m_mMeasuredValue[it_insert.key()] = it_insert.value();
            }
        }
        else
        {
            LOG_ERROR("DealMerageMessage  error m_vRecvData.size=%d , i =%d",m_vRecvData.size() , i);
        }
        ++i;
    }
    return 0;
}

void OperationInterface::ShowDetailMesage(RecvFile::STDetailData stResult)
{
    // 开关检查 如果是自动感知 则不进行操作
    if(IsFileWorkType())
    {
        return;
    }
#if 0
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
#endif
    // 对数据做处理 确认是新增列数 还是在原有数据里面补足数据
   // m_vRecvData.push_back(stResult);
    if(m_vRecvData.size() >= 100)
    {
        LOG_ERROR("数据大于100条，不在插入");
    }
    else
    {
        int iCloum = DealMerageMessage(stResult);  // iCloum 是写入数据列数 从0 开始
        int iSize = m_vRecvData.size();
        if(iCloum < iSize + 1)
        {
            if(m_tempData)
            {
               m_tempData->showcoldata(stResult,iCloum + 1);
            }
        }
        else
        {
            LOG_ERROR("DealMerageMessage return error :%d > %d",iCloum, iSize);
        }
    }
}

void OperationInterface::ShowDetailMesageCMM(TcpServerThread::STDetailData stCmmResult)
{
    // 开关检查 如果是自动感知 则不进行操作
    if(IsFileWorkType())
    {
        return;
    }
    if(5 != GetSheBeiType())
    {
        return;
    }
    if(stCmmResult.m_mMeasuredValue.isEmpty())
    {
        return;
    }

    // 对数据做处理 确认是新增列数 还是在原有数据里面补足数据
    // m_vRecvData.push_back(stResult);
    if(m_vRecvData.size() >= 100)
    {
        LOG_ERROR("数据大于100条，不在插入");
    }
    else
    {
        // 由于信号问题 兼容之前的接口  这里做类型转换
        RecvFile::STDetailData stResult;
        auto it = stCmmResult.m_mMeasuredValue.begin();
        for( ; it != stCmmResult.m_mMeasuredValue.end() ; ++it)
        {
            RecvFile::STDimenSionData emDimenSion;
            emDimenSion.strName = it->strName;
            emDimenSion.dActual = it->dActual;
            emDimenSion.dTheo = it->dTheo;
            emDimenSion.dUpperLimit = it->dUpperLimit;
            emDimenSion.dLowerLimit = it->dLowerLimit;
            stResult.m_mMeasuredValue[emDimenSion.strName] = emDimenSion;
            qDebug() << "insert file data :" << emDimenSion.strName << "-" << emDimenSion.dActual;
        }


        int iCloum = DealMerageMessage(stResult);  // iCloum 是写入数据列数 从0 开始
        int iSize = m_vRecvData.size();
        LOG_DEBUG("Merage info mation :[%d , %d]",iCloum , iSize);

        if(iCloum < iSize + 1)
        {
            if(m_tempData)
            {
                m_tempData->showcoldata(stResult,iCloum + 1);
            }
        }
        else
        {
            LOG_ERROR("DealMerageMessage return error :%d > %d",iCloum, iSize);
        }
    }

    LOG_INFO("ShowDetailMesageCMM is:%d" , stCmmResult.m_mMeasuredValue.size());
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
    if( false == CheckWorkCondition())
    {
        return;
    }
   // ShowLoading();

    // 如果是自动感知时 直接弹出提示框成功
    QString strText = ui->caijiTypecomboBox->currentText();
    if(strText == g_strZidonggaanzhi)
    {
        QThread::sleep(1);
        QMessageBox::information(this,"提示","连接成功");
        return;
    }

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
   // QString strMessage = g_strPacketHeader;
   // emit SendMessage(strMessage);

   // m_pHttpNetObject->ExePlugin("D:\\S_wroking\\三方插件\\测试程序\\Derive.exe");
    int iRet = m_pHttpNetObject->ModifyPluginConfig();
    qDebug() << "ModifyPluginConfig return :" << iRet ;
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
    ShowLoading();
    QApplication::processEvents();  // 手动刷新界面
    QString strFilePath;
    int iRet = GetMobanFileName(strFilePath);
    if(0 == iRet)
    {
       // ShowLoading();

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
    if( false == CheckWorkCondition())
    {
        return;
    }
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
        HideLoading();
        QMessageBox::information(this,"提示","没有生成文件");
        return ;
    }
    int iRet = m_pHttpNetObject->PostFileToNet(m_strPushFilePath);
    if(0 != iRet)
    {
        HideLoading();

    }
    LOG_INFO("PostFileToNet return :%d ,filename:%s",iRet , m_strPushFilePath.toStdString().c_str());
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
   // int iRet = m_pHttpNetObject->CompeleteCheck( );
    int iRet = m_pHttpNetObject->SubmitForView();
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

        if(1 == g_iFileSaveFlag)
        {
            QString strFileName = m_strPushFilePath.mid(iLastIndexName+1);
            qDebug() << "file name is :" << strFileName;
            QString strNewFilePath = g_strSaveFilePath + "/" + strFileName;

            file.rename(strNewFilePath);
        }
        else
        {
            QFile::remove(m_strPushFilePath);
        }

        m_strPushFilePath.clear();
        //todo  调用清空显示界面数据接口

       // m_bFileReading = false;

        LOG_INFO("complete check return=%d ",iRet);
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

    m_vRecvData.clear();
   // m_bFileReading = false;
    m_iLastInsertDataColumn = 0;
    QMessageBox::information(this,"提示","清理成功");
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

void OperationInterface::FindLatestFile(const QString &strPath , QVector<QFileInfo>& vNewFiles)
{
    QDir directory(strPath);
    if (!directory.exists())
    {
        LOG_ERROR("FindLatestFile path[%s] is null",strPath.toStdString().c_str());
        return ;
    }

    QStringList NameFilters;

    int iFileType = GetSheBeiType();
    if(1 == iFileType || 2 == iFileType)
    {
        NameFilters.append("*.xlsx");
        NameFilters.append("*.xls");
    }
    else if(3 == iFileType)
    {
        QString name = "*.txt";
        NameFilters.append(name);
    }
    else
    {
        LOG_ERROR("file type is error :%d",iFileType);
        return;
    }

    // 获取所有文件
    QFileInfoList fileList = directory.entryInfoList(NameFilters ,QDir::Files , QDir::Time /*| QDir::Reversed*/);

    if (fileList.isEmpty())
    {
        LOG_ERROR("FindLatestFile path[%s] 目录中没有文件",strPath.toStdString().c_str());
        return ;
    }


    // 找出更新的文件
   // QFileInfo latestFile;
    foreach (const QFileInfo &fileInfo, fileList)
    {
        LOG_DEBUG("file info find:[%s],time:%s",fileInfo.fileName().toStdString().c_str(),fileInfo.lastModified().toString().toStdString().c_str());
    }
    auto& it = fileList.first();
    if(m_LastFileInfo.lastModified() >= it.lastModified())
    {
        LOG_DEBUG("file not new last:%s,%s , new:%s,%s",m_LastFileInfo.lastModified().toString().toStdString().c_str(),m_LastFileInfo.absoluteFilePath().toStdString().c_str()
                    , it.lastModified().toString().toStdString().c_str(),it.absoluteFilePath().toStdString().c_str());
        return;
    }
    vNewFiles.push_back(it);

    // 对新的文件进行监听
    if(!m_LastFileInfo.absoluteFilePath().isEmpty())
    {
        m_Watcher.removePath(m_LastFileInfo.absoluteFilePath());
    }
    m_Watcher.addPath(it.absoluteFilePath());
    m_LastFileInfo = it;
    LOG_DEBUG("file info find last insert :[%s]",it.fileName().toStdString().c_str());

#if 0
    foreach (const QFileInfo &fileInfo, fileList)
    {
        auto it = m_sSetOldFiles.find(fileInfo.fileName());
        if(it == m_sSetOldFiles.end())
        {
            vNewFiles.push_back(fileInfo);
            LOG_INFO("感知到文件 :%s",fileInfo.fileName().toStdString().c_str());
        }
    }
#endif
  //  return latestFile;
}

int OperationInterface::InitWatcher()
{
    m_strListeningPath = ui->lineEdit_3->text();
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
    m_bFileReadtype = false;
    connect(&m_Watcher, &QFileSystemWatcher::directoryChanged, this, &OperationInterface::onDirectoryChanged);
    connect(&m_Watcher, &QFileSystemWatcher::fileChanged, this, &OperationInterface::onFileChanged);
    return 0;
}

void OperationInterface::StartListening()
{
    if(!m_bListening)
    {
        m_strListeningPath = ui->lineEdit_3->text();
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

        // 记录文件夹下面的所有文件
       // m_sSetOldFiles.clear();
        QFileInfoList listFiles = directory.entryInfoList(QDir::Files);
        if(!listFiles.isEmpty())
        {
            m_LastFileInfo = listFiles.first();
            for(auto it_list = listFiles.begin() ; it_list != listFiles.end() ; ++it_list)
            {
                if(m_LastFileInfo.lastModified() <  it_list->lastModified())
                {
                    m_LastFileInfo = *it_list;
                }
               // m_sSetOldFiles.insert(*it_list);
                LOG_DEBUG("OperationInterface::StartListening dir:%s , filename:%s",m_strListeningPath.toStdString().c_str(), it_list->fileName().toStdString().c_str());
            }
        }

        m_Watcher.addPath(m_strListeningPath);
        m_bListening = true;
        LOG_INFO("开始文件感知:%s , lastfile:%s",m_strListeningPath.toStdString().c_str(),m_LastFileInfo.lastModified().toString().toStdString().c_str());
    }
}

void OperationInterface::StopListening()
{
    if(m_bListening)
    {
        m_Watcher.removePath(m_strListeningPath);
        m_Watcher.removePaths(m_Watcher.files());
        m_bListening = false;
        m_strListeningPath.clear();
        m_sSetOldFiles.clear();
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
    LOG_DEBUG("感知到文件目录变化");
    if(!m_bListening)
    {
        return;
    }
    QDir directory(strPath);
    if(!directory.exists())
    {
        return ;
    }
    int iFileType = GetSheBeiType();
    QVector<QFileInfo> vNewFiles;
    FindLatestFile(strPath,vNewFiles );

    if(vNewFiles.isEmpty())
    {
        return;
    }

    // 检查文件是否被占用
    //if (!isFileInUse(FileInfo.filePath()))
    //{
    //    LOG_ERROR("");
    //}

    // 去重
    //if(RemoveRepetiton(FileInfo))
   // {
    //    LOG_ERROR("文件读取中");
    //    return;
   // }
    // 处理文件 todo
    if(nullptr == m_pExcellWork)
    {
        LOG_ERROR("onDirectoryChanged m_pExcellWork is null");
        return ;
    }

    if(0 == iFileType )
    {
        LOG_ERROR("onDirectoryChanged iFileType is error :%d",iFileType);
        return;
    }
    //QString strFilePathName = FileInfo.filePath()

    QVector<RecvFile::STDetailData> VRecvData;
    foreach (QFileInfo FileInfo , vNewFiles)
    {
        int iRet = m_pExcellWork->ReadFileData(FileInfo.absoluteFilePath() , VRecvData , iFileType);
#if 0
        if(0 == iRet && 3 == iFileType && 0 == g_iDelTxtFile )
        {
            if( ui->sehbeicomboBox->currentText() == "MicroVu")
            {
                QFile::remove(FileInfo.absoluteFilePath());
            }
        }
#endif
       // m_sSetOldFiles.insert(FileInfo.fileName());
        LOG_INFO("自动感知到文件完成读取:%s,iFielType:%d ,iRet=%d , data_size=%d",FileInfo.absoluteFilePath().toStdString().c_str(), iFileType,iRet,VRecvData.size());
    }
    if(VRecvData.isEmpty())
    {
        return;
    }

    DealMerageMessage(VRecvData);

    // 验证数据数量
    CheckDataCount();
    // 显示数据
    if(m_tempData)
    {
        m_tempData->showalldata(m_vRecvData);
    }
}

void OperationInterface::onFileChanged(const QString &strPath)
{
    QFileInfo fileinfo(strPath);
    LOG_DEBUG("感知到文件变化：%s ,%s now:%s,%s",m_LastFileInfo.absoluteFilePath().toStdString().c_str(),m_LastFileInfo.lastModified().toString().toStdString().c_str(),
               strPath.toStdString().c_str() , fileinfo.lastModified().toString().toStdString().c_str() );
    if(fileinfo.lastModified() <= m_LastFileInfo.lastModified())
    {
        return ;
    }
    int iFileType = GetSheBeiType();
    QVector<RecvFile::STDetailData> VRecvData;
    int iRet = m_pExcellWork->ReadFileData(m_LastFileInfo.absoluteFilePath() , VRecvData , iFileType);
    LOG_INFO("自动感知到文件完成读取:%s,iFielType:%d ,iRet=%d , data_size=%d",m_LastFileInfo.absoluteFilePath().toStdString().c_str(), iFileType,iRet,VRecvData.size());
    if(VRecvData.isEmpty())
    {
        return;
    }

    DealMerageMessage(VRecvData);
    CheckDataCount();
    // 显示数据
    if(m_tempData)
    {
        m_tempData->showalldata(m_vRecvData);
    }
    m_LastFileInfo = fileinfo;
}


void OperationInterface::on_ShowDataButton_clicked()
{
    if( false == CheckWorkCondition())
    {
        return;
    }
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

    // 保存
    ConfigObject config;
    QString strText = ui->MobanlujinEdit->text();
    int iRet = config.SaveConfigData("mubanpath" , strText);
    if(iRet < 0)
    {
        LOG_ERROR("OperationInterface save faild :%d ,%s ",iRet , strText.toStdString().c_str());
        return ;
    }
    LOG_INFO("OperationInterface save mubanpath :%d ,%s ",iRet , strText.toStdString().c_str());

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

void OperationInterface::sonWidget()
{
    m_widget->show();
}

int OperationInterface::UiInit()
{
    //ui->dateTimeEditStart->setCalendarPopup(true);
    //ui->dateTimeEditStart->setDateTime(QDateTime::currentDateTime());  // 设置当前日期时间
    //ui->dateTimeEditStart->setDisplayFormat("yyyy-MM-dd HH:mm:ss");  // 设置显示格式

    //ui->dateTimeEditEnd->setDateTime(QDateTime::currentDateTime());  // 设置当前日期时间
    //ui->dateTimeEditEnd->setDisplayFormat("yyyy-MM-dd HH:mm:ss");  // 设置显示格式
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    ui->GetDataButton->setVisible(false);
    ui->GetDataButton->setEnabled(false);
    ui->label_11->setVisible(false);
    ui->label_11->setEnabled(false);

    ui->IpEdit->setVisible(false);
    ui->IpEdit->setEnabled(false);

    ui->label_13->setVisible(false);
    ui->label_13->setEnabled(false);

    ui->PortEdit->setVisible(false);
    ui->PortEdit->setEnabled(false);

    // 设置字体颜色（使用 QPalette）
    QPalette palette = ui->labelLoading->palette();
    palette.setColor(QPalette::WindowText, Qt::red);  // 设置字体颜色为蓝色
    ui->labelLoading->setPalette(palette);

    QFont font = ui->labelLoading->font();
    font.setPointSize(14);
    ui->labelLoading->setFont(font);
    ui->labelLoading->setVisible(false);

    // 高度规
   // ui->gaoduguilineEdit->setVisible(false);
   // ui->gaoduguilineEdit->setEnabled(false);
    ui->gaoduguilineEdit->move(-1000,-1000);
    ui->gaoduguilineEdit->setFixedSize(1,1); //把高度规输入框移除可视区域
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


// 数据感知槽函数
void OperationInterface::on_caijiTypecomboBox_activated(int index)
{
    QString strText = ui->caijiTypecomboBox->currentText();
    if(strText == g_strZidonggaanzhi)
    {
        StartListening();
        m_bFileReadtype = true;
    }
    else
    {
        StopListening();
        m_bFileReadtype = false;
    }

}


int OperationInterface::GetSheBeiType()
{
    QString strText = ui->sehbeicomboBox->currentText();
    int iFileType = 0;
    // 文件感知类型 1 老兆丰 2 新兆丰 3 MIV
    if(strText == "老兆丰")
    {
        iFileType = 1;
    }
    else if(strText == "新兆丰")
    {
        iFileType = 2;
    }
    else if(strText == "MicroVu" /*|| strText == "海克斯康CMM"*/)
    {
        iFileType = 3;
    }
    else if(strText == "高度规")
    {
        iFileType = 4;
    }
    else if(strText == "海克斯康CMM")
    {
        iFileType = 5;
    }
    //LOG_STATS("文件感知文件类型发生变化：%d",iFileType);
    return iFileType;
}

bool OperationInterface::RemoveRepetiton(QFileInfo fileInfo)
{

    // 方式2 强制规定 第一个文件读取完成后 需要完成检测 或者清除数据后 才能继续读 期间的文件不感知
    return m_bFileReading;
}


void OperationInterface::on_zhidongganzhi_lineEdit_editingFinished()
{
    if(m_bListening)
    {
        StopListening();
    }
    QString strText = ui->caijiTypecomboBox->currentText();
    if(strText == g_strZidonggaanzhi)
    {
        StartListening();
    }
}

bool OperationInterface::CheckWorkCondition()
{
    QString strValue = ui->celiangrenyuan_lineEdit->text();
    if(strValue.isEmpty())
    {
        QMessageBox::information(this,"提示","请先填写测量人员");
        return false;
    }

    QString strshenhe = ui->shenherenyuan_lineEdit->text();
    if(strshenhe.isEmpty())
    {
        QMessageBox::information(this,"提示","请先填写审核人员");
        return false;
    }

    return true;
}

void OperationInterface::CheckDataCount()
{
    if(m_vRecvData.size() > 100)
    {
        m_vRecvData.remove(100 , m_vRecvData.size() - 100);
    }
}

void OperationInterface::ShowLoading()
{
#if 0
    if(nullptr == pLoad)
    {
        //pLoad = new LoadingDialog(NULL);
        pLoad = new LoadingDialog(this);

       // pLoad->move_to_center(this);
    }
    pLoad->move(this->pos().x() , this->pos().y() ); // 在父窗口的右下角偏移 50 像素
    pLoad->show();
    pLoad->move_to_center(this);
#endif
#if 0
    if(msgBox)
    {
        msgBox->close();
        delete msgBox;
    }
    msgBox = new QMessageBox(QMessageBox::Information, "提示", "文件上传中", QMessageBox::Ok, this);
    // 禁用关闭按钮
    msgBox->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);

    // 禁用 OK 按钮
    QPushButton *okButton = qobject_cast<QPushButton*> (msgBox->button(QMessageBox::Ok));
    if (okButton)
    {
        okButton->setEnabled(false);
    }
    //msgBox->show();
     msgBox->open();

    // 使用定时器在2秒后关闭消息框
    QTimer::singleShot(20000, msgBox, &QMessageBox::close);
     // 确保消息框在关闭时被删除
    // msgBox->setAttribute(Qt::WA_DeleteOnClose);

    msgBox->repaint();
#endif
    ui->labelLoading->setVisible(true);
}

void OperationInterface::HideLoading()
{
#if 0
    if(pLoad)
    {
        pLoad->hide();
        pLoad->close();
        LOG_INFO("禁用窗口");
    }


    if(msgBox)
    {
        msgBox->close();
        delete msgBox;
        msgBox = nullptr;
    }
#endif
    ui->labelLoading->setVisible(false);
}


# if 0

void OperationInterface::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    if(g_pLogger)
    {
        delete g_pLogger;
    }

}
#endif

void OperationInterface::on_UserEdit_editingFinished()
{
    ConfigObject config;
    QString strText = ui->UserEdit->text();
    int iRet = config.SaveConfigData("user" , strText);
    if(iRet < 0)
    {
        LOG_ERROR("OperationInterface save faild :%d ,%s ",iRet , strText.toStdString().c_str());
        return ;
    }
    LOG_INFO("OperationInterface save user :%d ,%s ",iRet , strText.toStdString().c_str());
}


void OperationInterface::on_PasswordEdit_editingFinished()
{
    ConfigObject config;
    QString strText = ui->PasswordEdit->text();
    int iRet = config.SaveConfigData("password" , strText);
    if(iRet < 0)
    {
        LOG_ERROR("OperationInterface save faild :%d ,%s ",iRet , strText.toStdString().c_str());
        return ;
    }
    LOG_INFO("OperationInterface save password :%d ,%s ",iRet , strText.toStdString().c_str());
}




void OperationInterface::on_celiangrenyuan_lineEdit_editingFinished()
{
    // 保存
    ConfigObject config;
    QString strText = ui->celiangrenyuan_lineEdit->text();
    int iRet = config.SaveConfigData("celiangrenyuan" , strText);
    if(iRet < 0)
    {
        LOG_ERROR("OperationInterface save faild :%d ,%s ",iRet , strText.toStdString().c_str());
        return ;
    }
    LOG_INFO("OperationInterface save celiangrenyuan :%d ,%s ",iRet , strText.toStdString().c_str());
}


void OperationInterface::on_shenherenyuan_lineEdit_editingFinished()
{
    // 保存
    ConfigObject config;
    QString strText = ui->shenherenyuan_lineEdit->text();
    int iRet = config.SaveConfigData("shenherenyuan" , strText);
    if(iRet < 0)
    {
        LOG_ERROR("OperationInterface save faild :%d ,%s ",iRet , strText.toStdString().c_str());
        return ;
    }
    LOG_INFO("OperationInterface save shenherenyuan :%d ,%s ",iRet , strText.toStdString().c_str());
}



void OperationInterface::on_DownLoadFileButton_clicked()
{
    qDebug()<< " 下载文件开始";
    QString strNumberEdit = ui->NumberEdit->text();
    if(strNumberEdit.isEmpty())
    {
        QMessageBox::information(this,"提示","请输入单号");
        return ;
    }
    m_pHttpNetObject->DownloadFile(ui->NumberEdit->text());
}


void OperationInterface::on_lineEdit_3_editingFinished()
{
    // 保存
    ConfigObject config;
    QString strText = ui->lineEdit_3->text();
    int iRet = config.SaveConfigData("zidongganzhilujing" , strText);
    if(iRet < 0)
    {
        LOG_ERROR("OperationInterface save zidongganzhilujing faild :%d ,%s ",iRet , strText.toStdString().c_str());
        return ;
    }
    LOG_INFO("OperationInterface save zidongganzhilujing :%d ,%s ",iRet , strText.toStdString().c_str());
}



void OperationInterface::on_NumberEdit_editingFinished()
{
    // 保存
    ConfigObject config;
    QString strText = ui->NumberEdit->text();
    int iRet = config.SaveConfigData("zidanhao" , strText);
    if(iRet < 0)
    {
        LOG_ERROR("OperationInterface save zidanhao faild :%d ,%s ",iRet , strText.toStdString().c_str());
        return ;
    }
    LOG_INFO("OperationInterface save zidanhao :%d ,%s ",iRet , strText.toStdString().c_str());
}


// 槽函数
void OperationInterface::ClikedInfoCell(const QModelIndex &index)
{
    if(4 != GetSheBeiType())
    {
        return;
    }
    qDebug()<< "ClikedInfoCell " << index.row() << " 列:" << index.column() << "内容：" << index.data().toString();
    // 获取key值
    if(index.column() < 6)
    {
        return;
    }
    m_indexCell = index;
    ui->gaoduguilineEdit->clear();
    ui->gaoduguilineEdit->setFocus();

}

void OperationInterface::on_gaoduguilineEdit_editingFinished()
{
    if(4 != GetSheBeiType())
    {
        return;
    }

    // 时间验证
    qint64 lTimeNowMsec = QDateTime::currentDateTime().toMSecsSinceEpoch();

    if(0 == m_lGaoduguiLineStatTime )
    {
        LOG_ERROR("m_lGaoduguiLineStatTime error");
        return;
    }

    if(m_lGaoduguiLineStatTime > lTimeNowMsec)
    {
        LOG_ERROR("m_lGaoduguiLineStatTime error %lu > %lu",m_lGaoduguiLineStatTime , lTimeNowMsec);
        return ;
    }
    qint64 lInterval = lTimeNowMsec - m_lGaoduguiLineStatTime;
    if(lInterval > g_lGaoduguiTimeInterval)
    {
        LOG_DEBUG("lTimeNowMsec[%lu] - m_lGaoduguiLineStatTime[%lu] = [%lu] > g_lGaoduguiTimeInterval[%lu]",lTimeNowMsec , m_lGaoduguiLineStatTime ,lInterval,g_lGaoduguiTimeInterval);
        return;
    }

    qDebug()<< "on_gaoduguilineEdit_editingFinished begin" <<lTimeNowMsec << "-" << m_lGaoduguiLineStatTime << "=" << lInterval << "<"<<  g_lGaoduguiTimeInterval;
    //1 .开始写入数据
    QString strValue = ui->gaoduguilineEdit->text();
    if(strValue.isEmpty())
    {
        return;
    }

    // 获取key值
    if(!m_indexCell.isValid() || m_indexCell.column() < 6)
    {
        QMessageBox::information(this,"提示","选择正确单元格");
    }

    if(nullptr == m_tempData)
    {
        LOG_ERROR("on_gaoduguilineEdit_editingFinished error m_tempData is nullptr");
        return;
    }
    QModelIndex indexKey =m_tempData->GetCellData(m_indexCell.row() , 1);

    QString strKey = indexKey.data().toString();
    if(strKey.isEmpty() )
    {
        QMessageBox::information(this,"提示","请选择高度规所在行");
        LOG_ERROR("on_gaoduguilineEdit_editingFinished strKey iserror : [%d < %d]",m_indexCell.row() , 1);
        return;
    }
    QModelIndex indexType =m_tempData->GetCellData(m_indexCell.row() , 2);
    QString strType = indexType.data().toString();
    if(strType != "HG")
    {
        QMessageBox::information(this,"提示","请选择高度规所在行");
        return;
    }

    // 台头有6列信息列 从第7 列  开始 为数据列
    int iDataSize = m_indexCell.column() - 6;
    if(m_vRecvData.size() < iDataSize + 1  || iDataSize < 0)
    {
        LOG_ERROR("on_gaoduguilineEdit_editingFinished size iserror :[%d < %d]",m_vRecvData.size() , iDataSize);
        return ;
    }

    RecvFile::STDetailData& DataInfo = m_vRecvData[iDataSize];
    DataInfo.m_mMeasuredValue[strKey].dActual = strValue.toDouble();

    // 显示：
    m_tempData->showcoldata(DataInfo , iDataSize + 1 );

    // 转到下一行
    int iNextRow = m_indexCell.row() + 1;
    int iColumn = m_indexCell.column();
    m_indexCell = QModelIndex();
    int iRet = m_tempData->ChoseCell(iNextRow, iColumn ,m_indexCell);
    if(0 != iRet)
    {
        LOG_INFO("ChoseCell faild  iRet:%d", iRet);
    }
    else
    {
        LOG_INFO("高度规跳到下一单元格： [%d,%d]",m_indexCell.row(),m_indexCell.column());
    }
    ui->gaoduguilineEdit->clear();
    ui->gaoduguilineEdit->setFocus();
}


void OperationInterface::on_gaoduguilineEdit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty())
    {
        m_lGaoduguiLineStatTime = 0;
    }
    else
    {
        if(0 == m_lGaoduguiLineStatTime)
        {
            m_lGaoduguiLineStatTime = QDateTime::currentDateTime().toMSecsSinceEpoch();
            LOG_INFO("on_gaoduguilineEdit_textChanged time begin:[%llu] ,text[%s]",m_lGaoduguiLineStatTime , arg1.toStdString().c_str());
        }
    }
}

