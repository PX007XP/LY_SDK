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
class MyItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    MyItemDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QStyleOptionViewItem options = option;
        initStyleOption(&options, index);

        // 选择性地修改字体颜色
        if (index.row() % 2 == 0)  // 示例：偶数行设置红色字体
        {
            painter->setPen(QColor(255, 0, 0));  // 设置字体颜色为红色
        }
        else
        {
            painter->setPen(QColor(0, 0, 255));  // 设置字体颜色为蓝色
        }

        // 绘制单元格内容
        QStyledItemDelegate::paint(painter, options, index);
    }
};
class TempData
{
public:
    TempData(QTableView *tv);
    virtual ~TempData();
    bool LoadData(QString filename);
    void WriteData(QString filename);
    QString ReadData(int row,int col);
    QColor standFont(int measure,int stand,int up,int down);
private:
    //显示视图和模型
    TableModel* m_model;
    QTableView *m_tableView;
    QAxObject *m_excel;
    QAxObject *m_workbooks;
    QAxObject *m_workbook;
};

#endif // TEMPDATA_H
