#include "tempdata.h"
#include <QAxBase>
#include "readpoint.h"
#include <QDir>
#include <QRadioButton>
TempData::TempData(QTableView* tv) {
    m_tableView = tv;
    m_model = new TableModel;
    // 创建一个WPS 应用程序对象
    m_excel = new QAxObject("Ket.Application");
    if (!m_excel) {
        qDebug() << "无法启动 Excel 应用程序!";
        m_excel = new QAxObject("Excel.Application");
        if (!m_excel) {
            qDebug() << "Failed to create WPS COM object!";
        }

    }

    // 设置 Excel 为不可见
    m_excel->setProperty("Visible", false);

    // 打开 Excel 文件
    m_workbooks = m_excel->querySubObject("Workbooks");
}

TempData::~TempData()
{
    // 关闭工作簿
    m_workbooks->dynamicCall("Close()");

    // 退出 Excel
    m_excel->dynamicCall("Quit()");

    delete m_excel;
}
bool TempData::LoadData(QString filename, int showrow){
    if(m_workbooks == nullptr){
        m_workbooks = m_excel->querySubObject("Workbooks");
    }
    QFile file(filename);
    if(filename.isEmpty()||(!(file.exists()&& file.isReadable()))){
        filename="F:\\zw_project_1_0\\880-GNT022-03-00.xlsm";
    }
    m_filepath=filename;
    if(m_workbook== nullptr){
        m_workbook->dynamicCall("Save()");
        m_workbook->dynamicCall("Close()");
    }
    m_workbooks->querySubObject("Open(const QString&)", filename);

    // 获取第一个工作表（sheet）
    if (m_excel ==nullptr) return false;
    m_workbook= m_excel->querySubObject("ActiveWorkBook");
    QAxObject *sheets = m_workbook->querySubObject("Sheets");
    m_sheet = m_workbook->querySubObject("WorkSheets(int)", 1);  // 获取第一个工作表，索引从 1 开始
    QAxObject *range = m_sheet->querySubObject("UsedRange");
    QVariant var = range->dynamicCall("Value");
    delete range;
    QVariantList varRows= var.toList();


    //获取路径加载xml配置文件
    /*
    QDir dir;
    QString currentDir = dir.absolutePath();
    QString xmlFile = currentDir+"/"+"modelpoint.xml";
    ReadPoint rp;
    std::vector<std::vector<int>> points= rp.readXml(xmlFile,"coordinates");
    */
    QStringList headList;
    /*
    for (size_t i = 0; i < points.size(); ++i) {
        QAxObject *cell = sheet->querySubObject("Cells(int, int)", points[i][0], points[i][1]);  // 获取 A1 单元格
        QVariant value = cell->property("Value");
        qDebug() << "A1 Cell Value:" << value.toString();  // 输出 A1 单元格的值
        headList.append(value.toString());
    }
    */
    // 设置表头 14行，数据是15行
    //m_model->setHorizontalHeaderLabels(QStringList() << "Name" << "Age" << "City");
    QAxObject *cell = m_sheet->querySubObject("Cells(int, int)", 14, 1);  // 获取 A1 单元格
    QVariant value = cell->property("Value");
    // 使用 replace 方法删除所有换行符
    QString str=varRows[12].toList()[0].toString();
    str.replace(QRegExp("[\r\n]"), "");
    headList<<(str);
    //获取设置的显示行数或者默认的32行
    int row=160;
    QStringList numStr;
    int isvalue=9;
    while(true){
        if(!varRows[14].toList()[isvalue].isNull()){
            headList<<QString::number(isvalue-8);
        }else{
            break;
        }
        isvalue++;
    }
    if(m_model == nullptr){
        m_model = new TableModel(row,headList.size());
    }
    m_model->setColumnCount(headList.size());
    if(showrow != 0){
        row=showrow;
    }
    m_model->setRowCount(row);
    m_model->setHorizontalHeaderLabels(headList);

    //points.clear();
    //points= rp.readXml(xmlFile,"");
    //读取标准计算字体颜色

    // 填充数据
    int startRow=14;
    int modelcol=1;
    while(true){
        //QAxObject *cell = sheet->querySubObject("Cells(int, int)", points[i][0], points[i][1]);  // 获取 A1 单元格
        //QVariant value = cell->property("Value");
        /*
        QString rowString=QString("A%1:Z%2").arg(QString::number(row)).arg(QString::number(row));
        // 获取第 1 行的数据
        QAxObject *range = sheet->querySubObject("Range(const QString&)", "A1:Z1");  // A1 到 Z1 的范围
        if (!range) {
            qDebug() << "Range not found!";
            break;  // 或者返回 false，具体看你的需求
        }
        QVariant result = range->dynamicCall("Value");
        */
        // 输出整行数据
        if(startRow >= varRows.size()|| startRow>= row+14)break;
        QVariantList rowData= varRows[startRow].toList() ;//result.toList();
        float stand=0,measure=0,ups=0,downs=0;
        if(rowData.size()>5){
            stand=rowData[4].toFloat();
        }
        if(rowData.size()>6){
            ups=rowData[5].toFloat();
        }
        if(rowData.size()>7){
            downs=rowData[6].toFloat();
        }
        if (rowData.size()>10){
            if(rowData[9].isNull()){
                startRow++;
                continue;
            }
            measure=rowData[9].toFloat();
        }
        for (const QVariant &value : rowData) {
            qDebug() << value.toString();
        }
        qDebug() << "A1 Cell Value:" << value.toString();  // 输出 A1 单元格的值
        //QStandardItem *item=new QStandardItem(QString::number(measure));
        // 设置字体颜色为红色
        //item->setForeground(QBrush(standFont(measure,stand,ups,downs)));
        m_model -> setItem(startRow-14,1,new QStandardItem(QString::number(modelcol++)));
        //m_model->setItem(startRow-14,2,item);
        for (int i=9;i<rowData.size();i++){
            if(rowData[i].isNull())break;
            measure=rowData[i].toFloat();
            QStandardItem *item=new QStandardItem(QString::number(measure));
            // 设置字体颜色为红色
            item->setForeground(QBrush(standFont(measure,stand,ups,downs)));
            m_model->setItem(startRow-14,i-7,item);
        }
        startRow++;
        if(startRow-14>row){
            break;
        }
    }

    // 设置代理
    MyItemDelegate *delegate = new MyItemDelegate(m_tableView);
    m_tableView->setItemDelegate(delegate);

    m_tableView->setModel(&*m_model);  // 将模型绑定到视图

    // 显示表格
    m_tableView->show();
    // 禁用所有编辑操作
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //m_tableView->setEditTriggers(QAbstractItemView::SelectedClicked);
    return true;
}

void TempData::WriteData(QString filename)
{
    QAxObject *workbook = m_workbooks->querySubObject("Open(const QString&)", filename);

    if (!workbook) {
        qDebug() << "无法打开 Excel 文件!";
        return ;
    }

    qDebug() << "Excel 文件打开成功!";

    // 获取工作表
    QAxObject *sheet = workbook->querySubObject("Worksheets(int)", 1); // 获取第1个工作表

    // 向 A1 单元格写入数据
    QAxObject *cell = sheet->querySubObject("Cells(int, int)", 1, 1); // A1 单元格
    cell->setProperty("Value", "Hello, Excel!");

    // 向 B2 单元格写入数据
    QAxObject *cell2 = sheet->querySubObject("Cells(int, int)", 2, 2); // B2 单元格
    cell2->setProperty("Value", 12345);

    // 保存并关闭文件
    workbook->dynamicCall("Save()");
    workbook->dynamicCall("Close()");
}

QString TempData::ReadData(int row, int col)
{
    return QString("");
}

QColor TempData::standFont(float measure,float stand, float up, float down)
{
    //（测量值-标准值）/公差 *100%  算出百分比 按颜色输出
    /*
     * <65%	黑色
    65 - 80 不包含80%	绿色
    80-90 不包含90%	紫色
    90-100 包含100%	黄色
    100	红色
    */
    QColor res;
    float dv=measure-stand;
    float k;
    if(dv>=0){
        k=dv/up*100;
    }else{
        k=dv/down*100;
    }
    if(k==100){
        res=Qt::red;
    }else if(k>=90){
        res=Qt::yellow;
    }else if(k>=80){
        res=Qt::blue;//无紫色
    }else if(k>=65){
        res=Qt::green;
    }else if(k<65){
        res=Qt::black;
    }
    return res;
}

void TempData::modslot()
{
    QRadioButton *button = qobject_cast<QRadioButton *>(sender());
    if(!m_tableView) return;
    if(button->isChecked()){
        m_tableView->setEditTriggers(QAbstractItemView::SelectedClicked);
        //修改数据
        connect(m_model,&QAbstractItemModel::dataChanged,this,&TempData::SaveData);
    }else{
        m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        //修改数据
        disconnect(m_model,&QAbstractItemModel::dataChanged,this,&TempData::SaveData);
    }
}

void TempData::SaveData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    if (!m_sheet) return;
    QAxObject *cell = m_sheet->querySubObject("Cells(int, int)", topLeft.row()+14, topLeft.column()+9); // A1 单元格
    cell->setProperty("Value", m_model->data(topLeft));
    // 保存文件
    m_workbook->dynamicCall("Save()");
}
