#ifndef OPERATIONINTERFACE_H
#define OPERATIONINTERFACE_H

#include <QWidget>
#include <QTcpSocket>
#include "recvfile.h"
#include "excellprecess.h"
#include <QVector>
#include "httpnetobject.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class OperationInterface;
}
QT_END_NAMESPACE

class OperationInterface : public QWidget
{
    Q_OBJECT

public:
    OperationInterface(QWidget *parent = nullptr);
    ~OperationInterface();

    // 信号接收函数 链接服务器成功
    void ConncetServerSucces();
    // 信号接收函数 链接失败
    void ConnectServerFaild();

    // 信号接收函数 所有的消息显示
    void RecvSocketMessage(QByteArray szMessage);
    // 信号接收函数 解析后的数据
    void ShowDetailMesage(RecvFile::STDetailData stResult);

    // 设置excel写文件捕获异常
    void SetSlotExcelException(QAxObject *pWorkbook, QString strFile);

    void ShowMessageBoxInfo(QString strMessageType , QString strShowData);

    // 弹窗提示
    void MessageBoxInfomation(QString strType , QString strValue);

    // ui 显示接口
    void SetUIMessageInfo(QString strUiName , QString strData);

    // 保存上传文件名
    void SavePushFilePath(QString strFileName);

    // 获取ui指针
    Ui::OperationInterface * GetUiPointObject()
    {
        return ui;
    }
private slots:
    void on_connectButton_clicked();

    void on_GetDataButton_clicked();

    void RecieveData();
    void on_PathcomboBox_activated(int index);

    void on_TypecomboBox_activated(int index);

    void on_FilecomboBox_activated(int index);

    void on_WriteFilepushButton_clicked();

    void on_LoginPushButton_clicked();

    void on_GetInfoButton_clicked();

    void on_ClearDataButton_clicked();

    void handleExcelException(int code, const QString &source, const QString &desc, const QString &help);

    void on_pushFileButton_clicked();

    void on_ComCheckButton_clicked();

    void on_ShowDataButton_clicked();

    void on_MobanlujinEdit_editingFinished();
signals:
    void StartConnect(QString strIP,unsigned short usPort);
    void SendMessage(QString strMessage);
private:
    Ui::OperationInterface *ui;
    QThread* m_pSocketThread  ;
    RecvFile *m_pRecvFileWorker ;
    QString m_strLocalIp;

    // UI的相关初始化
    int UiInit();


    // 写文件相关
    QVector<RecvFile::STDetailData> m_vRecvData;
    ExcellPrecess* m_pExcellWork = nullptr;
    HttpNetObject* m_pHttpNetObject = nullptr;

    QString m_strPushFilePath; // 上传文件名

    // 根据第一层文件夹显示第二层文件夹
    int SetDirPathComboByDirPath(QString strDirPath);

    // 根据文件夹显示文件
    int SetFileComboByDirPath(QString strDirPath);

public:

private:
    void GetLocalIp();

};
#endif // OPERATIONINTERFACE_H
