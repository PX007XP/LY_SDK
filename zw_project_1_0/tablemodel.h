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

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return data_.count();  // 返回行数
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 2;  // 两列：姓名和年龄
    }

    QVariant data(const QModelIndex &index, int role) const override {
        if (!index.isValid())
            return QVariant();

        if (role == Qt::DisplayRole) {
            // 显示数据
            const auto &row = data_.at(index.row());
            if (index.column() == 0) {
                return row[index.column()];  // 姓名
            } else if (index.column() == 1) {
                return row[index.column()];  // 年龄
            }
        }

        return QVariant();
    }

    bool setData(const QModelIndex &index, const QVariant &value, int role) override {
        if (index.isValid() && role == Qt::EditRole) {
            auto &row = data_[index.row()];

            if (index.column() == 0) {
                  qDebug()<<QString("不可更改") ;//更新姓名
            } else if (index.column() >= 1) {
                row[index.column()]=value.toFloat();  // 更新年龄
            }

            // 发出数据已更改的信号
            emit dataChanged(index, index);

            return true;
        }

        return false;
    }

    Qt::ItemFlags flags(const QModelIndex &index) const override {
        Qt::ItemFlags defaultFlags = QStandardItemModel::flags(index);
        if (index.isValid()) {
            return defaultFlags | Qt::ItemIsEditable;  // 使得单元格可编辑
        }
        return defaultFlags;
    }

private:
    QVector<QVector<float>> data_;  // 存储数据，每一行是一个姓名和年龄的对
};

#endif // TABLEMODEL_H
