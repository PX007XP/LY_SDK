#include "tempdata.h"
#include <QAxBase>
#include "readpoint.h"
#include <QDir>
#include <logger.h>
#include <excellprecess.h>
#include <QtConcurrent/QtConcurrent>
#include <QMessageBox>
#include <QSet>
int TempData::m_showcol=6;
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
    if (m_excel->setControl("Excel.Application"))
    {	// 加载 Microsoft Excel 控件
        LOG_INFO("load Excel.Application success");
    }
    else if( m_excel->setControl("KET.Application"))
    {
        LOG_INFO("load kET.Application success");
    }
    else
    {
        LOG_ERROR("加载excel控件失败");
    }
    // 设置 Excel 为不可见
    m_excel->setProperty("Visible", false);

    // 打开 Excel 文件
    m_workbooks = m_excel->querySubObject("Workbooks");
    QtConcurrent::run(this,&TempData::getData);
}

TempData::~TempData()
{
    // 关闭工作簿
    //m_workbooks->dynamicCall("Close()");

    // 退出 Excel
    //m_excel->dynamicCall("Quit()");

    //delete m_excel;
}
bool TempData::LoadData(QString filename, int showrow){
    bool setModel=true;
    if (m_excel == nullptr){
        m_excel = new QAxObject("Excel.Application");
        // 打开 Excel 文件
        m_workbooks = m_excel->querySubObject("Workbooks");
        //m_workbooks = m_excel->querySubObject("Workbooks");
        setModel=false;
    }
    QFile file(filename);
    if(filename.isEmpty()||!((file.exists()))){
        filename="F:\\zw_project_1_0\\880-GNT022-03-00.xlsm";
    }
    m_filepath=filename;
    LOG_INFO("打开文件路径：%s",filename.toStdString().c_str());
    m_workbooks->querySubObject("Open(const QString&)", filename);
    if(nullptr == m_workbooks)
    {
        LOG_ERROR("open file faild :%s",filename.toStdString().c_str());
    }

    // 获取第一个工作表（sheet）
    if(m_excel == nullptr) return false;
    m_workbook= m_excel->querySubObject("ActiveWorkBook");
    //m_workbook= m_workbooks->querySubObject("ActiveWorkBook");
    if(nullptr == m_workbook)
    {
        return false;
    }
    QAxObject *sheets = m_workbook->querySubObject("Sheets");
    m_sheet = m_workbook->querySubObject("WorkSheets(int)", 1);  // 获取第一个工作表，索引从 1 开始
    QAxObject *range = m_sheet->querySubObject("UsedRange");
    QVariant var = range->dynamicCall("Value");
    delete range;
    QVariantList varRows= var.toList();
    //关闭文件


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
    //QAxObject *cell = m_sheet->querySubObject("Cells(int, int)", 14, 1);  // 获取 A1 单元格
    //QVariant value = cell->property("Value");
    // 使用 replace 方法删除所有换行符
    QString str=varRows[12].toList()[0].toString();
    QList modlist=varRows[12].toList();
    QStringList modString;
    for(int i=0;i<4;i++){
        if(i == 2)continue;
        modString<<modlist[i].toString();
    }
    modlist=varRows[13].toList();
    for(int i=4;i<7;i++){
        modString<<modlist[i].toString();
    }
    for(int i=0;i<modString.size();i++){
        //m_model->setItem(0,i,new QStandardItem(modString[i]));
    }
    //str.replace(QRegExp("[\r\n]"), "");
    headList<<modString;
    //获取设置的显示行数或者默认的32行
    int row=160;
    QStringList numStr;
    int isvalue=9;

    if(m_model == nullptr){
        m_model=qobject_cast<TableModel*>(m_tableView->model());
        setModel=true;
        if(m_model == nullptr){
            m_model = new TableModel(row,headList.size());
        }
    }
    m_model->clear();
    //m_model->setColumnCount(headList.size());
    if(showrow != 0){
        row=showrow;
    }else{
        row=32;
    }
    for(int i=1;i<=row;i++){
        headList<<QString::number(i);
    }
    //结果列和判定列
    headList<<"结果\n判定";
    m_model->setRowCount(varRows.size());
    m_model->setColumnCount(row+6+1);
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
        if(startRow >= varRows.size())break;
        QVariantList rowData= varRows[startRow].toList() ;//result.toList();
        if (rowData.size()<9) break;
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
        //qDebug() << "A1 Cell Value:" << value.toString();  // 输出 A1 单元格的值
        //QStandardItem *item=new QStandardItem(QString::number(measure));
        // 设置字体颜色为红色
        //item->setForeground(QBrush(standFont(measure,stand,ups,downs)));
        m_model -> setItem(startRow-14,0,new QStandardItem(rowData[0].toString()));
        m_model -> setItem(startRow-14,1,new QStandardItem(rowData[1].toString()));
        m_key[rowData[1].toString()]=startRow-14;
        m_model -> setItem(startRow-14,2,new QStandardItem(rowData[3].toString()));
        m_model -> setItem(startRow-14,3,new QStandardItem(rowData[4].toString()));
        m_model -> setItem(startRow-14,4,new QStandardItem(rowData[5].toString()));
        m_model -> setItem(startRow-14,5,new QStandardItem(rowData[6].toString()));
        //m_model -> setItem(startRow-14,6,new QStandardItem(rowData[0].toString()));
        //m_model -> setItem(startRow-13,1,new QStandardItem(QString::number(modelcol++)));
        //m_model->setItem(startRow-14,2,item);
        for (int i=0;i<6;i++){
            m_model->item(startRow-14,i)->setTextAlignment(Qt::AlignCenter);
        }
        startRow++;
    }




    if(setModel){
        // 设置代理
        m_tableView->setModel(&*m_model);  // 将模型绑定到视图
        MyItemDelegate *delegate = new MyItemDelegate(m_tableView);
        m_tableView->setItemDelegate(delegate);
        //m_tableView->resizeColumnsToContents();  // 自动调整列宽以适应内容

    }


    // 显示表格
    m_tableView->update();
    // 禁用所有编辑操作
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //m_tableView->setEditTriggers(QAbstractItemView::SelectedClicked);
    closefile();
    m_cond.wakeOne();
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
    if(k>=100){
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

void TempData::ShowData(RecvFile::STDetailData datildata)
{
    QMutexLocker lock(&m_locker);
    LOG_INFO("数据放入队列");
    m_queue.enqueue(datildata);
    m_cond.wakeOne();
}

void TempData::closefile()
{
    // 完成后保存文件
    m_workbook->dynamicCall("Save()");

    // 关闭工作簿
    m_workbook->dynamicCall("Close()");
    m_workbooks->dynamicCall("Close()");
    // 退出 Excel 应用程序
    m_excel->dynamicCall("Quit()");

    delete m_excel;  // 释放 Excel 对象
    m_excel=nullptr;
    m_workbooks=nullptr;
}

void TempData::dataClear()
{
    if(m_model ==nullptr){
        m_model = qobject_cast<TableModel*>(m_tableView->model());
    }
    //删除测试数据
    LOG_INFO("数据清理");
    int columnCount = m_model->columnCount();
    int row=m_model->rowCount();

    // 从指定列开始，删除后面的所有列
    for (int i=0;i<row;i++){
        for (int col = columnCount - 1; col >= 6; --col) {
            auto item=m_model->item(i,col);
            if(item == nullptr) continue;
            item->setText(QString(""));
            //m_model->removeColumn(col);  // 删除该列
        }
    }
    m_showcol=6;
    emit setLaybelText("OK");
}

void TempData::modslot()
{
    QRadioButton *button = qobject_cast<QRadioButton *>(sender());
    if(!m_tableView) return;
    if(button->isChecked()){
        m_tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        //修改数据
        //connect(m_model,&QStandardItemModel::dataChanged,this,&TempData::SaveData);
        connect(m_model,&QStandardItemModel::dataChanged,this,&TempData::SaveData);
    }else{
        m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        //修改数据
        disconnect(m_model,&QStandardItemModel::dataChanged,this,&TempData::SaveData);
    }
}

void TempData::getData()
{
    static int j=6;
    static int showrow=0;
    while(true){
        if(m_queue.isEmpty()){
            QThread::msleep(100);
        }
        QMutexLocker lock(&m_locker);
        m_cond.wait(&m_locker);
        LOG_INFO("数据取出队列");
        j=m_showcol;
        if(j>=m_model->columnCount()&&m_model->columnCount()>0){
            //QMessageBox::information(nullptr,"提示","显示列数已满");
            return;
        }
        if(m_model->columnCount()==0)continue;
        if (m_queue.empty())continue;
        RecvFile::STDetailData datildata = m_queue.dequeue();
        //lock.unlock();
        if (m_model==nullptr) {
            g_pLogger->writeLog(1 ,("模型为空"));
            if(m_tableView->model()!= nullptr){
                m_model = qobject_cast<TableModel*>(m_tableView->model());
            }else{
                m_model = new TableModel;
            }
        }
        //m_model->clear();
        double stand=0,measure=0,ups=0,downs=0;
        int i=0;
        // 遍历并修改数据
        int colCount=m_model->columnCount();
        /*
        for (int col = 0; col < colCount; ++col) {
            QStandardItem *item = m_model->item(2, col);
            if (item !=nullptr&&item->data().isNull()) {
                // 修改数据
                j=col;
            }
        }
        */
        QStringList headerlist;
        QSet<int> redvec;
        QSet<int> allvec;
        for(auto item=datildata.m_mMeasuredValue.begin();item!=datildata.m_mMeasuredValue.end();item++){
            QString name=item.key();
            headerlist<<name;
            //m_model->setItem(i,j,new QStandardItem(name));
            QString mingcheng=item.value().strName;//名称
            if(m_key.contains(name)){
                i=m_key[name];
                //continue;
            }
            measure=item.value().dActual;//实测值
            /*
            downs=item.value().dLowerLimit;//下偏差
            ups=item.value().dUpperLimit;//上偏差
            stand=item.value().dTheo;//理论值
            */
            QStandardItem *showitem=new QStandardItem(QString::number(measure));
            /*
            // 设置字体颜色为红色
            if(m_model->item(i,3)!=nullptr&&m_model->item(i,4)!=nullptr&&(m_model->item(i,5)==nullptr)){
                QColor rc=standFont(measure,m_model->item(i,3)->data().toFloat(),m_model->item(i,4)->data().toFloat(),m_model->item(i,5)->data().toFloat());
                showitem->setForeground(QBrush(rc));
                if(rc==Qt::red){
                    redvec.append(i);
                    //auto item=m_model->item(i,m_model->columnCount()-1);
                    //item->setForeground(QBrush(rc));
                }
            }*/
            //allvec.append(i);
            if(i>showrow)showrow=i;
            showitem->setTextAlignment(Qt::AlignCenter);
            m_model->setItem(i++,j,showitem);
        }
        //判定是否合格 遍历item 将model中所有的数据进行重新的颜色设置和结果判定列的更新和label的更新
        for(int i=6;i<m_model->columnCount()-1;i++){
            bool fn=false;
            for(int j=0;j<=showrow;j++){
                QStandardItem *showitem=m_model->item(j,i);
                if(showitem ==nullptr)continue;
                if(m_model->item(j,3)!=nullptr&&m_model->item(j,4)!=nullptr&&(m_model->item(j,5)!=nullptr)){
                    float measure=showitem->text().toFloat();//实测值
                    float downs=m_model->item(j,5)->text().toFloat();//下偏差
                    float ups=m_model->item(j,4)->text().toFloat();//上偏差
                    float stand=m_model->item(j,3)->text().toFloat();//理论值
                    QColor rc=standFont(showitem->text().toFloat(),m_model->item(j,3)->text().toFloat(),m_model->item(j,4)->text().toFloat(),m_model->item(j,5)->text().toFloat());
                    showitem->setForeground(QBrush(rc));
                    if(rc==Qt::red){
                        redvec.insert(j);
                        fn=true;
                        //auto item=m_model->item(i,m_model->columnCount()-1);
                        //item->setForeground(QBrush(rc));
                    }
                    allvec.insert(j);
                    m_model->setItem(j,i,showitem);
                }
            }
        }
        bool flabel=false;
        for(int j:allvec){
            auto showitem=m_model->item(j,m_model->columnCount()-1);
            if(redvec.contains(j)){
                showitem=m_model->item(j,m_model->columnCount()-1);
                if(showitem == nullptr){
                    showitem=new QStandardItem("NG");
                }else{
                    showitem->setText("NG");
                }
                // 设置字体颜色为红色
                showitem->setForeground(QBrush(Qt::red));
                flabel=true;
                m_model->setItem(j,m_model->columnCount()-1,showitem);
            }else{
                showitem=m_model->item(j,m_model->columnCount()-1);
                if(showitem == nullptr){
                    showitem=new QStandardItem("OK");
                }else{
                    showitem->setText("OK");
                }
                // 设置字体颜色为红色
                showitem->setForeground(QBrush(Qt::green));
                m_model->setItem(j,m_model->columnCount()-1,showitem);
            }
        }
        if (flabel){
            emit setLaybelText("NG");
        }else{
            emit setLaybelText("OK");
        }
        /*
        for(auto a : allvec){
            QStandardItem *showitem=m_model->item(a,m_model->columnCount()-1);
            if(redvec.contains(a)){
                if(showitem == nullptr){
                    showitem=new QStandardItem("NG");
                }
                // 设置字体颜色为红色
                showitem->setForeground(QBrush(Qt::red));
                m_model->setItem(a,m_model->columnCount()-1,showitem);
            }else{
                if(showitem == nullptr){
                    showitem=new QStandardItem("OK");
                }
                // 设置字体颜色为红色
                showitem->setForeground(QBrush(Qt::green));
                m_model->setItem(a,m_model->columnCount()-1,showitem);
            }
        }
        */
        /*
        for(int a=6;a<j;a++){
            bool fn=true;
            for(int b=0;b<i-1;b++){
                auto it=m_model->item(b,a);
                if(it==nullptr)continue;
                if(it->foreground().color().name()==Qt::red){

                    fn=false;
                    break;
                }
                if(fn){

                }
            }

        }*/
        //m_model->setItem(i-1,m_model->columnCount()-1,new QStandardItem(datildata.m_cQualified));
        j++;
        m_showcol=j;
        //m_model->setVerticalHeaderLabels(headerlist);
        // 设置代理
        //MyItemDelegate *delegate = new MyItemDelegate(m_tableView);
        //m_tableView->setItemDelegate(delegate);

        //m_tableView->setModel(m_model);  // 将模型绑定到视图

        // 显示表格
        m_tableView->show();
        m_tableView->update();
        //m_tableView->repaint();
        // 禁用所有编辑操作
        //m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void TempData::SaveData(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles)
{
    /*
    if (!m_sheet) return;
    QAxObject *cell = m_sheet->querySubObject("Cells(int, int)", topLeft.row()+14, topLeft.column()+9); // A1 单元格
    cell->setProperty("Value", m_model->data(topLeft));
    // 保存文件
    m_workbook->dynamicCall("Save()");
    */
    /*
    *对修改内容进行保存，
     */
    //先获取参数内容进行显示设置
    //再修改参数key
    if(topLeft.column()==m_model->columnCount()-1)return;
    QStandardItem *keyitem=m_model->item(topLeft.row(),1);
    if(keyitem == nullptr){
        return;
    }
    QString key = keyitem->text();
    float value = m_model->item(topLeft.row(),topLeft.column())->text().toFloat();
    int row=topLeft.row();
    if(m_model->columnCount() ==0 && m_model->rowCount()==0)return;
    if(m_model->item(row,3)==nullptr) return;
    if(m_model->item(row,4)==nullptr) return;
    if(m_model->item(row,5)==nullptr) return;
    QColor rc=standFont(value,m_model->item(row,3)->text().toFloat(),m_model->item(row,4)->text().toFloat(),m_model->item(row,5)->text().toFloat());
    //判断自身的颜色
    auto moditem=m_model->item(row,topLeft.column());
    if(moditem == nullptr) return;
    QColor oldcolor= moditem->foreground().color();
    if(oldcolor != rc)moditem->setForeground(QBrush(rc));
    m_model->setItem(topLeft.row(),topLeft.column(),moditem);
    if(rc == Qt::red){
        auto item=m_model->item(row,m_model->columnCount()-1);
        item->setForeground(QBrush(rc));
        m_model->setItem(row,m_model->columnCount()-1,item);
        emit setLaybelText("NG");
    }
    //遍历当前行
    bool fn=true;
    for(int i=6;i<m_model->columnCount()-1;i++){
        auto item=m_model->item(row,i);
        if (item == nullptr) continue;
        if(item->foreground().color()==Qt::red){
            //说明当前行的结果不用修改
            fn=false;
            auto item=m_model->item(row,m_model->columnCount()-1);
            if(item->text()!="NG") item->setText("NG");
            if(item->foreground().color()!=Qt::red)item->setForeground(QBrush(Qt::red));
            //m_model->setItem(row,m_model->columnCount()-1,item);
            emit setLaybelText("NG");
            break;
        }
    }
    if(fn){
        auto item=m_model->item(row,m_model->columnCount()-1);
        item->setText("OK");
        item->setForeground(QBrush(Qt::green));
        m_model->setItem(row,m_model->columnCount()-1,item);
    }
    //遍历结果列，没有红色 则设置label为绿色
    bool fs=false;
    for (int i=0;i<m_model->rowCount();i++){
        auto item=m_model->item(i,m_model->columnCount()-1);
        if (item == nullptr) continue;
        if(item->foreground().color()==Qt::red){
            fs=true;
            break;
        }
    }
    if (fs){
        emit setLaybelText("NG");
    }else{
        emit setLaybelText("OK");
    }
    emit dataChanged(topLeft.column()-6, key,value);
}

void TempData::Setyangbenshuliang(int col)
{
    //更新表头和列数
    int cols=m_model->columnCount();
    if (cols >= col+6 ) return;
    m_model->insertColumn(cols-2);
    m_model->insertColumns(cols-2,col-(cols-6));
}
