#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QStandardItemModel>
#include <QVariant>
#include <QVector>
#include <QString>
#include <QDebug>

class TableModel: public QStandardItemModel
{
    Q_OBJECT
public:
    TableModel(QObject *parent = nullptr)
        : QStandardItemModel(parent)
    {
        // 初始化模型数据
        //data_.append({"Alice", 25});
        //data_.append({"Bob", 30});
        //data_.append({"Charlie", 35});
    }
    TableModel(int rows, int columns, QObject* parent = nullptr)
        : QStandardItemModel(rows, columns, parent) // 显式调用父类的构造函数
    {
        // 在这里可以添加其他初始化代码
    }
    /*
    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return rowCount();  // 返回行数
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return columnCount();  // 两列：姓名和年龄
    }
    */
    /*
    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid())
            return QVariant();

        if (role == Qt::DisplayRole) {
            // 显示数据
            return QVariant(item(index.row(),index.column())->text());
        }

        return QVariant();
    }
    */
    /*
    bool setData(const QModelIndex &index, const QVariant &value, int role) override {
        if (index.isValid() && role == Qt::EditRole) {
            // 获取现有的 QStandardItem
            QStandardItem *item = this->item(index.row(), index.column());
            if (item) {
                // 直接修改该单元格的文本内容
                if(value.toFloat() == item->text().toFloat()) return false;
                item->setText(value.toString());
            }else {
                //this->setData(index,value,role);
            }


            // 发出数据已更改的信号
            //emit dataChanged(index, index);

            return true;
        }

        return false;
    }*/

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
        if (index.isValid()) {
            return defaultFlags | Qt::ItemIsEditable;  // 使得单元格可编辑
        }
        return defaultFlags;
    }

private:
    //QVector<QVector<float>> data_;  // 存储数据，每一行是一个姓名和年龄的对
};

#endif // TABLEMODEL_H
