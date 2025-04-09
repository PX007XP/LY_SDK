#ifndef TEMPDATA_H
#define TEMPDATA_H
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPainter>
#include <QColor>
#include <QStyledItemDelegate>
#include <QAxObject>
#include <QDebug>
#include "tablemodel.h"
#include <QObject>
#include <QRadioButton>
#include "recvfile.h"
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QFileSystemWatcher>
#include <QFuture>

class TempData;
class MyItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    MyItemDelegate(QObject *parent = nullptr ,TempData* tempData = nullptr) : QStyledItemDelegate(parent) , m_tempData(tempData){}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyleOptionViewItem options = option;
        initStyleOption(&options, index);
        // 设置文本居中
        QStyleOptionViewItem newOption(option);
        newOption.displayAlignment = Qt::AlignCenter;

        // 选择性地修改字体颜色
        /*
        if (index.row() % 2 == 0)  // 示例：偶数行设置红色字体
        {
            painter->setPen(QColor(255, 0, 0));  // 设置字体颜色为红色
        }
        else
        {
            painter->setPen(QColor(0, 0, 255));  // 设置字体颜色为蓝色
        }
        */
        // 绘制单元格内容
        QStyledItemDelegate::paint(painter, options, index);

        
    }
     // 重写createEditor方法控制编辑权限
     QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index) const override;
private:
    TempData* m_tempData;  // 保存TempData指针
};
class TempData  : public QObject
{
    Q_OBJECT

public:
     TempData(QTableView *tv);
    ~TempData();
    bool LoadData(QString filename,int showrow=33);
    void WriteData(QString filename);
    QString ReadData(int row,int col);
    QColor standFont(float measure,float stand,float up,float down);
    void ShowData(RecvFile::STDetailData datildata);
    void closefile();
    void recShowData(RecvFile::STDetailData datildata);
    int modelNumber();
    void showalldata(QVector<RecvFile::STDetailData> data);
    void showcoldata(RecvFile::STDetailData datildata,int col);
    void ReleaseObject();
    signals:
        void dataChanged(int num,QString key,double value);
        void pushData();
        void setLaybelText(QString text);
    public slots:
        void dataClear();
        void modslot();
        void getData();
        void SaveData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);
        void Setyangbenshuliang(int col);
        void onFileChanged(const QString &filePath);
public:
        //显示视图和模型
        TableModel* m_model;
private:

    QTableView *m_tableView;
    QAxObject *m_excel;
    QAxObject *m_workbooks;
    QAxObject *m_workbook;
    QAxObject *m_sheet;
    QString m_filepath;
    QQueue<RecvFile::STDetailData> m_queue;
    QMutex m_locker;
    QWaitCondition m_cond;
    QMap<QString,int> m_key;
    static int m_showcol;
    QFileSystemWatcher watcher;

    QFuture<void> future;

    std::atomic<bool> m_stopFlag{false};
public:
    bool m_globalEditEnabled = false;  // 新增成员变量保存全局编辑状态

//
public:
    // 选中某个单元格
    int ChoseCell(int iRow , int iColumn , QModelIndex &index);
    QModelIndex GetCellData(int iRow , int iColumn);
};

#endif // TEMPDATA_H
