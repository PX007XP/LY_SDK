#include "configobject.h"
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include "logger.h"
#include "globle.h"
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTextStream>
#include "operationinterface.h"
#include "ui_operationinterface.h"
extern int g_iLogLevel;
ConfigObject::ConfigObject() {}


void ConfigObject::ReadConfig(OperationInterface* pObjcet)
{
    QString filePath = "./config.xml";
    QFileInfo fileInfo(filePath);
    if (!fileInfo.exists())
    {
        LOG_ERROR("File does not exist :%s " ,fileInfo.absoluteFilePath().toStdString().c_str());
        return;
    }
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Cannot open file config.xml" ;
        LOG_ERROR("Cannot open file config.xml");
        return;
    }

    QDomDocument document;
    if (!document.setContent(&file))
    {
        qWarning() << "Error parsing XML from file config.xml" ;
        LOG_ERROR("document Cannot open file config.xml");
        file.close();
        return;
    }
    file.close();

    QDomElement root = document.documentElement();
    qDebug() << "Root element:" << root.tagName();
    QDomNodeList elements = root.elementsByTagName("common");
    if (!elements.isEmpty())
    {
        QDomElement commonElement = elements.at(0).toElement();
        QString logLevel = commonElement.attribute("log_level", "1");

        g_iLogLevel = logLevel.toInt();
        g_strIpAddressKey = commonElement.attribute("ip_address_key" , "以太网");
        LOG_STATS("log level is = %d ,ip_address_key[%s]",g_iLogLevel,g_strIpAddressKey.toStdString().c_str());
    }
#if 0
    // 读取存储相关数据
    elements = root.elementsByTagName("datasave");
    if(!elements.isEmpty())
    {
        QDomElement DataSaveElement = elements.at(0).toElement();
        QString strUser = DataSaveElement.attribute("user", "");
        if(!strUser.isEmpty())
        {
            pObjcet->GetUiPointObject()->UserEdit->setText(strUser);
            LOG_STATS("配置文件初始化 user:%s",strUser.toStdString().c_str());
        }

        QString strPassword = DataSaveElement.attribute("password", "");
        if(!strPassword.isEmpty())
        {
            pObjcet->GetUiPointObject()->PasswordEdit->setText(strPassword);
            LOG_STATS("配置文件初始化 strPassword:%s",strPassword.toStdString().c_str());
        }

        QString strMubanpath = DataSaveElement.attribute("mubanpath", "");
        if(!strMubanpath.isEmpty())
        {
            pObjcet->GetUiPointObject()->MobanlujinEdit->setText(strMubanpath);
            LOG_STATS("配置文件初始化 strMubanpath:%s",strMubanpath.toStdString().c_str());
        }

        QString strCeliang = DataSaveElement.attribute("celiangrenyuan", "");
        if(!strCeliang.isEmpty())
        {
            pObjcet->GetUiPointObject()->celiangrenyuan_lineEdit->setText(strCeliang);
            LOG_STATS("配置文件初始化 strCeliang:%s",strCeliang.toStdString().c_str());
        }

        QString strShenHe = DataSaveElement.attribute("shenherenyuan", "");
        if(!strShenHe.isEmpty())
        {
            pObjcet->GetUiPointObject()->shenherenyuan_lineEdit->setText(strShenHe);
            LOG_STATS("配置文件初始化 strShenHe:%s",strShenHe.toStdString().c_str());
        }
    }
#endif
    InitJsonObject(pObjcet);
    qDebug() << "log_level:" << g_iLogLevel;
}


void ConfigObject::InitJsonObject(OperationInterface* pObjcet)
{

    QFile file("./config.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Cannot open file config.json for reading";
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject obj = doc.object();

    if (obj.contains("user"))
    {
        QString value1 = obj.value("user").toString();
        pObjcet->GetUiPointObject()->UserEdit->setText(value1);
        LOG_STATS("配置文件初始化 user:%s",value1.toStdString().c_str());
    }
    if (obj.contains("password"))
    {
        QString value1 = obj.value("password").toString();
        pObjcet->GetUiPointObject()->PasswordEdit->setText(value1);
        LOG_STATS("配置文件初始化 password:%s",value1.toStdString().c_str());
    }
    if (obj.contains("mubanpath"))
    {
        QString value1 = obj.value("mubanpath").toString();
        pObjcet->GetUiPointObject()->MobanlujinEdit->setText(value1);
        LOG_STATS("配置文件初始化 mubanpath:%s",value1.toStdString().c_str());
    }
    if (obj.contains("celiangrenyuan"))
    {
        QString value1 = obj.value("celiangrenyuan").toString();
        pObjcet->GetUiPointObject()->celiangrenyuan_lineEdit->setText(value1);
        LOG_STATS("配置文件初始化 celiangrenyuan:%s",value1.toStdString().c_str());
    }
    if (obj.contains("shenherenyuan"))
    {
        QString value1 = obj.value("shenherenyuan").toString();
        pObjcet->GetUiPointObject()->shenherenyuan_lineEdit->setText(value1);
        LOG_STATS("配置文件初始化 shenherenyuan:%s",value1.toStdString().c_str());
    }

    file.close();
    return;
}

int ConfigObject::SaveConfigData(QString strKey, QString strValue)
{
    QString strPath = "./config.json";
    QFile file(strPath);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        qWarning() << "Cannot open file config.json for reading";
        return -1 ;
    }

    QByteArray dataRead = file.readAll();
    LOG_INFO("read stream :%s",dataRead.toStdString().c_str());
    QJsonDocument docRead = QJsonDocument::fromJson(dataRead);
    QJsonObject obj = docRead.object();

    file.close();

    if (obj.contains(strKey))
    {
        QString value1 = obj.value(strKey).toString();
        if(value1 == strValue)
        {
            return 1;
        }
        obj[strKey] = strValue;
        LOG_INFO("保存 字段 :%s , 值: %s",strKey.toStdString().c_str(),strValue.toStdString().c_str());
    }
    else
    {
        obj["user"] = "";
        obj["password"] = "";
        obj["mubanpath"] = "";
        obj["celiangrenyuan"] = "";
        obj["shenherenyuan"] = "";
        LOG_INFO("新增 字段 :%s , 值: %s",strKey.toStdString().c_str(),strValue.toStdString().c_str());
    }
    QFile fileSave(strPath);
    if (!fileSave.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
    {
        qWarning() << "Cannot open file" << strPath << "for writing";
        return -2;
    }

    QJsonDocument docSave(obj);
    QTextStream outSave(&fileSave);
    outSave.setCodec("UTF-8");
    outSave << docSave.toJson(QJsonDocument::Indented);

    fileSave.close();
    return 0;
}


