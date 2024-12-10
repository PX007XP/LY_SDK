#ifndef CONFIGOBJECT_H
#define CONFIGOBJECT_H

#include<QString>
class OperationInterface;
class ConfigObject
{
public:
    ConfigObject();

    void ReadConfig(OperationInterface* pObject);
    void InitJsonObject(OperationInterface* pObject);

    // 根据节点名字保存
    int SaveConfigData(QString strKey ,QString strValue);
};

#endif // CONFIGOBJECT_H
