#include "httpnetobject.h"
#include <QHttpMultiPart>
#include <QFile>
#include <QJsonArray>
#include "operationinterface.h"
#include "globle.h"
#include "logger.h"

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

    LOG_DEBUG("http Login  %s", jsonData.data());

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


    QJsonObject json;
    json["chkResultUserListId"] = m_strBizid;
    json["FileIds"] = m_strFileId;
    json["ChkResult"] = "1";
    json["ChkQty"] = 3939;
    json["NGQty"] = 0;
    json["OKQty"] = 5;
    json["Remark"] = "";
    json["reportType"] = 0;
    json["OldUserCode"] = m_strUserName;

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();

    // 发送POST请求
    qDebug() <<"get data: " <<jsonData ;
    QNetworkReply *pReply = m_pManager->post(request, jsonData);

    return 0;
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
    int iArrary = jsonData.value("Total").toInt();
    for(int i = 0 ; i < iArrary ; ++i)
    {
        QJsonObject pageListData = pageListArray[i].toObject();
        // 目前取最后一个
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

    }


    qDebug()<< "jsonm_strBizid:  " << m_strBizid ;
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
    m_pOperationObject->MessageBoxInfomation("提示", "上传文件成功");
}

int HttpNetObject::GetJsonValueBykey(QJsonObject jsonObject,QString strKeyName)
{
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
    if (pReplay->error() == QNetworkReply::NoError) {
        // 处理成功响应
        strResponse = pReplay->readAll();
        qDebug() << "Response:" << strResponse;
        LOG_DEBUG(strResponse.toUtf8().data());
    } else {
        // 处理错误
        strResponse = pReplay->readAll();
        qDebug() << "Error:" << pReplay->errorString();
        LOG_DEBUG("http response error %d", pReplay->error());
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
        if( "true" == json.value("Success").toString() && "200" == json.value("Code").toString())
        {
            m_pOperationObject->MessageBoxInfomation("提示", "成功");
        }
        else
        {
            m_pOperationObject->MessageBoxInfomation("提示", "失败");
            LOG_ERROR("http response error1 %s" ,strResponse.toStdString().data() );
        }
    }
    else
    {
        m_pOperationObject->MessageBoxInfomation("提示", "失败");
        LOG_ERROR("http response error2 %s" ,strResponse.toStdString().data() );
    }
    pReplay->deleteLater();
}
