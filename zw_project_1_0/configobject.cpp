#include "configobject.h"
#include <QFile>
#include <QDomDocument>
#include <QDebug>
#include "logger.h"
#include "globle.h""

extern int g_iLogLevel;
ConfigObject::ConfigObject() {}

void ConfigObject::ReadConfig()
{
    QFile file("./config.xml");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Cannot open file config.xml" ;
        LOG_ERROR("Cannot open file config.xml")
        return;
    }

    QDomDocument document;
    if (!document.setContent(&file))
    {
        qWarning() << "Error parsing XML from file config.xml" ;
        LOG_ERROR("document Cannot open file config.xml")
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
    qDebug() << "log_level:" << g_iLogLevel;
}
