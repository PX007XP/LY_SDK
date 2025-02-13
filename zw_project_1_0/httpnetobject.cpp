#include "httpnetobject.h"
#include <QHttpMultiPart>
#include <QFile>
#include <QJsonArray>
#include <QStandardPaths>
#include "operationinterface.h"
#include "ui_operationinterface.h"
#include "globle.h"
#include "logger.h"
#include <QProcess>
#include <QSettings>
#include <QDir>

HttpNetObject::HttpNetObject() {}

int HttpNetObject::Init(OperationInterface* pObject)
{
    m_pManager = new QNetworkAccessManager();
    if(nullptr == m_pManager)
    {
        return -1;
    }
   // connect(m_pManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(SlotsRecvReplayData(QNetworkReply *pReplay)));
    connect(m_pManager, &QNetworkAccessManager::finished, this, &HttpNetObject::SlotsRecvReplayData);
    m_pOperationObject = pObject;

    return 0;
}

int HttpNetObject::LoginPost(QString strUserName , QString strPassword)
{
    // 定义请求的URL（假设这是登录接口的地址）
    QUrl url("https://mom.lingyiitech.com:8092/api/Base/home/SubmitLogin");

    // 创建请求对象
    QNetworkRequest request(url);

    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    // 设置请求头部信息（如果需要）
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 准备POST请求的数据
    QJsonObject json;
    json["userCode"] = strUserName.toUtf8().constData();  // 替换成实际用户名
    json["password"] = strPassword.toUtf8().constData();   // 替换成实际密码

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    // 发送POST请求
    QNetworkReply *pReply = m_pManager->post(request, jsonData);
    m_strUserName = strUserName;
    m_strBizid.clear();

    LOG_DEBUG("user[:%s] Login  %s",m_strUserName.toStdString().c_str(), jsonData.data());

     /*
    // 创建事件循环，以便等待请求完成
    QEventLoop loop;
    // 连接信号和槽，以处理服务器的响应
    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            // 处理成功响应
            QString response = reply->readAll();
            qDebug() << "Response:" << response;
        } else {
            // 处理错误
            qDebug() << "Error:" << reply->errorString();
        }
        reply->deleteLater();
        loop.quit();  // 退出事件循环
    });
*/

    return 0;
}

int HttpNetObject::GetCheckTaskData(QString strMmsID)
{

    if( false == m_bLoginStatus || m_strToken.isEmpty())
    {
        m_pOperationObject->MessageBoxInfomation("提示","请先登录");
        return -1;
    }
    // 定义请求的URL（假设这是登录接口的地址）
    QUrl url("https://mom.lingyiitech.com:8092/api/Quality/MMS_ChkResultList/GetChkTaskDataList");

    // 创建请求对象
    QNetworkRequest request(url);

    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_strToken).toUtf8());
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    // 设置请求头部信息（如果需要）
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 准备POST请求的数据
    QJsonObject json;
    json["PageIndex"] = 1;
    json["PageRows"] = 100;
    json["SortField"] = "CreateTime";
    json["SortType"] = "asc";

    QJsonObject searchData;
    searchData["ReqDetailNo"] = strMmsID.toUtf8().constData();
    json["Search"] = searchData;

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    // 发送POST请求
    qDebug() <<"get data: " <<jsonData ;
    QNetworkReply *pReply = m_pManager->post(request, jsonData);

    return 0;
}

int HttpNetObject::PostFileToNet(QString strFilePath)
{
    if( false == m_bLoginStatus || m_strToken.isEmpty())
    {
        m_pOperationObject->MessageBoxInfomation("提示","请先登录");
        return -1;
    }
    if(m_strBizid.isEmpty())
    {
        //m_pOperationObject->MessageBoxInfomation("提示",QStringLiteral("请先输入子单号获取关键信息"));
        m_pOperationObject->MessageBoxInfomation("提示","请先获取信息");
        return -2;
    }
    // 创建请求 URL
    QString url = QString("https://mom.lingyiitech.com:8092/api/Base/File/Upload?bizId=%1").arg(m_strBizid);
    QNetworkRequest request(QUrl(url.toStdString().c_str()));
    qDebug() << "PostFileToNet: " << url ;
    // 设置请求头中的 Token
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_strToken).toUtf8());

    // 创建 multipart/form-data
    QHttpMultiPart* multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    //QString strFilePath = "D:\\S_wroking\\new\\880-GNT022-03-004.xlsm";
   // QString strFilePath = "D://S_wroking\code\zw_project_1_0\build\Desktop_Qt_5_15_0_MSVC2019_64bit-Release\temporary\880-GNT022-03-004.xlsm";
    // 添加文件字段
    QFile* file = new QFile(strFilePath);
    if (!file->open(QIODevice::ReadOnly))
    {
        qWarning() << "无法打开文件:" << strFilePath;
        m_pOperationObject->MessageBoxInfomation("提示","无法打开文件");
        return -3;
    }

    // 构建文件内容体
    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"880-GNT022-03-004.xlsm\""));
    filePart.setBodyDevice(file);  // 绑定文件流
    file->setParent(multiPart);    // 确保 multipart 释放时也会释放文件

    // 将文件部分加入 multipart
    multiPart->append(filePart);

    // 发送 POST 请求
    QNetworkReply* reply = m_pManager->post(request, multiPart);
    multiPart->setParent(reply);  // 确保 reply 释放时释放 multipart

    return 0;
}

int HttpNetObject::CompeleteCheck()
{
    if(m_strFileId.isEmpty())
    {
        m_pOperationObject->MessageBoxInfomation("提示", "请先上传文件");
    }
    // 定义请求的URL（假设这是登录接口的地址）
    QUrl url("https://mom.lingyiitech.com:8092/api/Quality/MMS_ChkResultList/CompeteTesting");

    // 创建请求对象
    QNetworkRequest request(url);

    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_strToken).toUtf8());
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    // 设置请求头部信息（如果需要）
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    qDebug() << "m_strToken: " << m_strToken;

    QJsonObject json;
    json["chkResultUserListId"] = m_strBizid;
    json["FileIds"] = m_strFileId;
    json["ChkResult"] = "1";
    json["ChkQty"] = 3939;
    json["NGQty"] = 0;
    json["OKQty"] = 5;
    json["Remark"] = "";
    json["reportType"] = 0;
    json["OldUserCode"] = m_strUserName; // todo 账号

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    // 发送POST请求
    LOG_INFO("comelete check :%s",jsonData.data());
    QNetworkReply *pReply = m_pManager->post(request, jsonData);

    m_iStatus = 2; // 完成检测 待提交审核

    return 0;
}


int HttpNetObject::DownloadFile(QString strMmsID,int iFileType /*= 0*/)
{
    //QUrl url("http://100.0.4.37:8080/Quality/MMS_QCChkSummary/GetQCCPKFAIExcel");
    QUrl url("https://mom.lingyiitech.com:8092/api/Quality/MMS_QCChkSummary/GetQCCPKFAIExcel");
    QNetworkRequest request(url);

    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_strToken).toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json;charset=UTF-8");
    //request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject jsonObject;
    jsonObject["Type"] = iFileType;

    if(0 == iFileType)
    {
        m_strDownloadFile = "CPK";
    }
    else
    {
        m_strDownloadFile="FAI";
    }

    QJsonArray reqDetailNoArray;
    reqDetailNoArray.append(strMmsID);
    jsonObject["ReqDetailNo"] = reqDetailNoArray;

    QJsonDocument jsonDocument(jsonObject);
    QByteArray jsonData = jsonDocument.toJson();

    //QNetworkReply *reply = networkManager->post(request, jsonData);
    //qDebug() << jsonData;
    m_iFileData++;
    LOG_INFO("Http DownLoadFile request : %s",jsonData.data());
    QNetworkReply *pReply = m_pManager->post(request, jsonData);
    if(NULL == pReply)
    {
        LOG_ERROR("DownloadFile post error :%s",strMmsID.toStdString().c_str());
    }

    return 0;

}

int HttpNetObject::SubmitForView()
{
    if(2 != m_iStatus)
    {
        return -1;
    }
    // 定义请求的URL（假设这是登录接口的地址）
    QUrl url("https://mom.lingyiitech.com:8092/api/Quality/MMS_ChkResultList/UpdateStatus");

    // 创建请求对象
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", QString("Bearer %1").arg(m_strToken).toUtf8());
    request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
    // 设置请求头部信息（如果需要）
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["ReqDetailNo"] = m_pOperationObject->GetUiPointObject()->NumberEdit->text();
    json["DetailSchedule"] = 3;

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    // 发送POST请求
    qDebug() <<"get data: " <<jsonData ;
    QNetworkReply *pReply = m_pManager->post(request, jsonData);

    // 提交审核后重置测量数据

    m_iStatus = 3;
}

void HttpNetObject::DealWithLoginResponse(QJsonObject &json)
{
    QJsonObject jsonData = json.value("Data").toObject();

    m_strToken = jsonData.value("Token").toString();
    qDebug()<< "jsontoken:  " << m_strToken ;
    m_pOperationObject->MessageBoxInfomation("提示","登录成功");
    m_bLoginStatus = true;
}

// 单号获取详情
void HttpNetObject::DealWithPageListResponse(QJsonObject &json)
{
    QJsonObject jsonData = json.value("Data").toObject();
    QJsonArray pageListArray = jsonData.value("PageList").toArray();
    if(pageListArray.isEmpty())
    {
        return ;
    }
    m_strBizid.clear();
    int iArrary = jsonData.value("Total").toInt();
    for(int i = 0 ; i < iArrary ; ++i)
    {
        QJsonObject pageListData = pageListArray[i].toObject();

        QString strTestUserNo = pageListData.value("TestUserNo").toString();

        if(strTestUserNo == m_strUserName)
        {
            m_strBizid = pageListData.value("Id").toString();

            GetJsonValueBykey(pageListData , g_strReqNo);
            GetJsonValueBykey(pageListData , g_strReqUserName);
            GetJsonValueBykey(pageListData , g_strReqUnicom);
            GetJsonValueBykey(pageListData , g_strDeviceName);
            GetJsonValueBykey(pageListData , g_strDeviceNo);
            GetJsonValueBykey(pageListData , g_strReqTime);
            GetJsonValueBykey(pageListData , g_strTestCon);
            GetJsonValueBykey(pageListData , g_strReportType);
            GetJsonValueBykey(pageListData , g_strProjectClassId);
            GetJsonValueBykey(pageListData , g_strProjectStageId);
            GetJsonValueBykey(pageListData , g_strSatageNo);
            GetJsonValueBykey(pageListData , g_strOrgCode);
            GetJsonValueBykey(pageListData , g_strRemark);
            GetJsonValueBykey(pageListData, g_strRevArtTime);
            LOG_INFO(" get mms detail user[%s] ,bizid[%s]" , m_strUserName.toStdString().c_str() ,  m_strBizid.toStdString().c_str());
        }
    }
    if(m_strBizid.isEmpty())
    {
        m_pOperationObject->MessageBoxInfomation("提示","子单号信息错误");
    }
}

void HttpNetObject::DealWithFileResponse(QJsonObject &json)
{
    QJsonObject jsonData = json.value("Data").toObject();
    QJsonArray filesArray = jsonData.value("Files").toArray();
    if(filesArray.isEmpty())
    {
        return ;
    }
    // 目前只处理第一个
    QJsonObject FilesData = filesArray[0].toObject();
    m_strFileId = FilesData.value("FileId").toString();

    // 上传文件成功后  完成检查
    CompeleteCheck();

  //  m_pOperationObject->MessageBoxInfomation("提示", "上传文件成功");
}

int HttpNetObject::GetJsonValueBykey(QJsonObject jsonObject,QString strKeyName)
{
    if(!jsonObject.contains(strKeyName))
    {
        return -2;
    }
    QJsonValue jsonValue = jsonObject.value(strKeyName);
    if(jsonValue.isUndefined())
    {
        return -1;
    }
    QString strValue = jsonValue.toString();
    m_pOperationObject->SetUIMessageInfo(strKeyName , strValue);
    return 0;
}

void HttpNetObject::SlotsRecvReplayData(QNetworkReply *pReplay)
{
    QString strResponse ;
    if (pReplay->error() == QNetworkReply::NoError)
    {
        // 处理成功响应
        if(0 == m_iFileData)
        {
            strResponse = pReplay->readAll();
        }
        LOG_INFO("httpnet response is :%s ",strResponse.toStdString().c_str());
    }
    else
    {
        // 处理错误
        strResponse = pReplay->readAll();
        m_pOperationObject->HideLoading();
        LOG_ERROR("http response error %d , %s", pReplay->error(),strResponse.toUtf8().data());
        return ;
    }
    if(m_iFileData > 0)
    {
        QByteArray fileData = pReplay->readAll();
       // QString filePath = "./123file.xlsx" ;
        QString fileName = m_pOperationObject->GetUiPointObject()->NumberEdit->text();
        QString strFilePath ;
        if(g_strDownloadFileSavePath.isEmpty())
        {
            strFilePath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
        }
        else
        {
            strFilePath = g_strDownloadFileSavePath;
        }
        QString filePath = strFilePath + "/" + fileName + "_"+ m_strDownloadFile +".xlsm";
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly))
        {
            qint64 bytesWritten = file.write(fileData);
            file.close();
            LOG_INFO("File downloaded and saved to %s [%d,%d]", filePath.toStdString().c_str() ,fileData.size(),bytesWritten);
            if(2 == m_iFileData)
            {
                //m_pOperationObject->MessageBoxInfomation("提示", "下载成功");
                LOG_INFO("下载成功[%s][%s]",m_strCPKFilePath.toStdString().c_str(), filePath.toStdString().c_str());
            }
        }
        else
        {
           // LOG_ERROR("Unable to save file %s", strMmsID.toStdString().c_str());
        }
        if(1 == m_iFileData)
        {
            DownloadFile(fileName ,1);
            m_strCPKFilePath = filePath;
        }
        else
        {
            m_iFileData = 0;
            m_strFAIFilePath = filePath;

            // 文件下载完成  需要调用 外部插件  插件路径以及插件名通过外部配置配置
            QString strPlugin = "";
            if(g_strPluginPath.isEmpty())
            {
                strPlugin = "./Derive.exe";
            }
            else
            {
                strPlugin =  g_strPluginPath;
            }
            int iRet = ModifyPluginConfig();
            if(iRet < 0)
            {
                LOG_ERROR("ModifyPluginConfig faild return :%d",iRet);
            }
            iRet = ExePlugin(strPlugin);
            if(iRet < 0)
            {
                LOG_ERROR("ExePlugin faild return :%d",iRet);
            }
        }
        return;
    }

    QJsonObject json;

    QJsonDocument jsonDoc = QJsonDocument::fromJson(strResponse.toUtf8());

    // 检查 JSON 文档是否是对象
    if (jsonDoc.isObject())
    {
        // 获取 JSON 对象
        json = jsonDoc.object();

    } else {
        qWarning() << "The input JSON string is not a valid JSON object.";

    }
    if(json.contains("Success"))
    {
        bool bResult = json.value("Success").toBool();
        if(bResult == false)
        {
            QString strMsg = json.value("Msg").toString();
            m_pOperationObject->MessageBoxInfomation("错误",strMsg);
        }
    }
    else
    {
        m_pOperationObject->MessageBoxInfomation("通用错误", "失败");
    }
    if(json.contains("Data"))
    {
        QJsonObject jsonData = json.value("Data").toObject();
        if(jsonData.contains("Token"))
        {
            DealWithLoginResponse(json);
        }
        else if(jsonData.contains("PageList"))
        {
            DealWithPageListResponse(json);
        }
        else if(jsonData.contains("Files"))
        {
            DealWithFileResponse(json);
        }
        else
        {

        }
    }
    else if(json.contains("Success"))
    {
        qDebug()<<"http resopnse data is : " << json.value("Success").toString() << ", code :" << json.value("Code").toInt();
        LOG_INFO("收到网页系统回复 status=%d , %s , %s",m_iStatus,json.value("Success").toString().toStdString().c_str(),json.value("Code").toString().toStdString().c_str() );
        if( true == json.value("Success").toBool() && 200 == json.value("Code").toInt())
        {
            if(2 == m_iStatus)
            {
                // 提交审核
               // SubmitForView();
                m_pOperationObject->HideLoading();
                m_pOperationObject->MessageBoxInfomation("提示", "上传文件成功");
            }
            else
            {
                m_pOperationObject->MessageBoxInfomation("提示", "成功");
            }
        }
        else
        {
            m_pOperationObject->MessageBoxInfomation("提示", "失败1");
            m_pOperationObject->HideLoading();
            LOG_ERROR("http response error1 %s" ,strResponse.toStdString().data() );
        }
    }
    else
    {
        m_pOperationObject->MessageBoxInfomation("提示", "失败2");
        m_pOperationObject->HideLoading();
        LOG_ERROR("http response error2 %s" ,strResponse.toStdString().data() );
    }
    pReplay->deleteLater();
}

int HttpNetObject::ModifyPluginConfig()
{
    QString strConfigFile = "";
    if(g_strPluginConfigFilePath.isEmpty())
    {
        strConfigFile = "./Configuration.ini";
    }
    else
    {
        strConfigFile =  g_strPluginConfigFilePath;
    }

    if(!QFile::exists(strConfigFile))
    {
        LOG_ERROR("HttpNetObject::ModifyPluginConfig strPluginpath is null :%s",strConfigFile.toStdString().c_str());
        return -1;
    }

    // 读取配置
    LOG_INFO("ini file path :%s",strConfigFile.toStdString().c_str());
    QSettings settings(strConfigFile, QSettings::IniFormat);
    settings.setIniCodec("UTF-8");

    // 获取修改的内容
    if(nullptr == m_pOperationObject || nullptr == m_pOperationObject->GetUiPointObject())
    {
        return -2;
    }
    QString strRootPath = m_pOperationObject->GetUiPointObject()->MobanlujinEdit->text();
    QString strProjectPath = m_pOperationObject->GetUiPointObject()->PathcomboBox->currentText();
    QString strTypePath = m_pOperationObject->GetUiPointObject()->TypecomboBox->currentText();

    QString strConfigPath = strRootPath  + strProjectPath + "\\" + strTypePath + "\\" + "CPK&FAI" + "\\";

   // qDebug() << "strConfigPath: " <<strConfigPath ;
    // 创建 QDir 对象
    QDir fileDir(strConfigPath);

    // 获取文件夹下的所有文件
    QStringList fileList = fileDir.entryList(QDir::Files);
    if(fileList.isEmpty())
    {
        return -3;
    }

   // qDebug() << "KH_FAI_Path :" << settings.value("Document/KH_FAI_Path");

    QString strFaiFileName ="";
    QString strCpkFileName ="";
    foreach (const QString& strFileName, fileList)
    {
        if(strFileName.contains("CPK"))
        {
            strCpkFileName = fileDir.absoluteFilePath(strFileName);
           // strCpkFileName = QDir::toNativeSeparators(strCpkFileName);
        }
        else if(strFileName.contains("FAI"))
        {
            strFaiFileName = fileDir.absoluteFilePath(strFileName);
           // strFaiFileName = QDir::toNativeSeparators(strFaiFileName);
        }
    }
    // qDebug() << "status 1 :" << settings.status();
   // qDebug() << "strFaiFileName :" << strCpkFileName;

    // 修改配置
    settings.beginGroup("Document");
    settings.setValue("KH_CPK_Path", strCpkFileName);
    settings.setValue("KH_FAI_Path", strFaiFileName);

    settings.setValue("NB_CPK_Path", m_strCPKFilePath);
    settings.setValue("NB_FAI_Path", m_strFAIFilePath);
    settings.endGroup();


    settings.sync(); // 强制保存

    //qDebug() << "status 4:" << settings.status();

    LOG_INFO("ModifyPluginConfig status:%d",settings.status());
    return 0;
}

int HttpNetObject::ExePlugin(QString strPluginPath)
{
    // 1 检查 strPluginPath 路径是否正确
    if(strPluginPath.isEmpty())
    {
        m_pOperationObject->MessageBoxInfomation("错误", "插件路径不正确");
        return -1;
    }
    if(!QFile::exists(strPluginPath))
    {
        LOG_ERROR("HttpNetObject::ExePlugin strPluginpath is null :%s",strPluginPath.toStdString().c_str());
        m_pOperationObject->MessageBoxInfomation("错误", "插件路径不正确");
        return -1;
    }

    QProcess process;

    // 将输出重定向到标准输出
    process.setProcessChannelMode(QProcess::MergedChannels);

    // 启动外部程序
    process.start(strPluginPath);

    // 等待程序启动
    if (!process.waitForStarted())
    {
        LOG_ERROR("HttpNetObject::ExePlugin Failed to start process");
        return 1;
    }

    // 等待程序完成执行
    if (!process.waitForFinished())
    {
        LOG_ERROR("HttpNetObject::ExePlugin crashed or timed out");
        return 2;
    }

    // 获取程序的标准输出和标准错误
    QByteArray output = process.readAllStandardOutput();
    QByteArray errorOutput = process.readAllStandardError();


    // 获取程序的退出代码
    int exitCode = process.exitCode();
    // 打印输出
    LOG_INFO("HttpNetObject::ExePlugin output[%s] ,Error Output[%s] returncode[%d] ",output.data(),errorOutput.data(),exitCode);

    return 0;
}
