#include "operationinterface.h"

#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QString>
#include <QMap>
#include <QStyleFactory>
#include <QStandardPaths>
#include <QDir>

// 加密函数：数字 -> 字母
// 声明并初始化 QMap
QMap<QChar, QChar> numbermap={
    {'0','b'},{'1','c'},{'2','d'},{'3','e'},{'4','f'},
{'5','g'},{'6','h'},{'7','i'},{'8','j'},{'9','k'}
    };
QMap<QChar, QChar> charmap={
    {'b','0'},{'c','1'},{'d','2'},{'e','3'},{'f','4'},
    {'g','5'},{'h','6'},{'i','7'},{'j','8'},{'k','9'}
};
QString encrypt(QString number) {
    // 'a' 的 ASCII 值是 97，所以可以通过 number + 96 来得到对应字母的 ASCII 值
    QString letter;
    for(QChar ch : number){
        letter.append(numbermap[ch]);
    }

    return letter;
}
// 解密函数：字母 -> 数字
QString decrypt(QString &letter) {
    // 'a' 的 ASCII 值是 97，所以字母的 ASCII 值减去 96 得到对应的数字
    QString rec;
    for(QChar ch : letter){
        rec.append(charmap[ch]);
    }

    return rec;
}

bool CheckRegister()
{
    QDir homeDir = QDir::home();
    QString homePath = homeDir.absolutePath();

    qDebug() << "User Home Directory check: " << homeDir << "dkf :" << homePath;


    QString limisDirPath = homePath + "/LIMIS";
    QString filePath = limisDirPath + "/encrypt.txt";

    if (!QFile::exists(filePath)) 
    {
        qDebug() << "File encrypt.txt exists at: " << filePath;
        return false;
    } 

    // 验证文件内容
     // 3. 打开文件
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        qDebug() << "Failed to open file: " << filePath;
        return false;
    }

    // 4. 读取第一行内容
    QTextStream in(&file);
    QString firstLine = in.readLine();
    file.close();

    // 5. 输出第一行内容
    qDebug() << "First line content: " << firstLine;

    
    firstLine.remove('\n');
    QString b= decrypt(firstLine);
    qDebug() << b ;
    int year =b.left(4).toInt();
    int mon = b.mid(4,2).toInt();
    int day = b.right(2).toInt();
    QDate dedate = QDate(year,mon,day);
    
    // 获取当前系统的日期
    QDate currentDate = QDateTime::currentDateTime().date();
    if(currentDate > dedate)
    {
        return false;
    }

    return true;
}
// 注册程序
int RegisterExe()
{
    QDir homeDir = QDir::home();
    QString homePath = homeDir.absolutePath();

    qDebug() << "User Home Directory: " << homeDir << "dkf :" << homePath;

    // 2. 在主目录下创建文件夹 LIMIS
    QString limisDirPath = homePath + "/LIMIS";
    QString filePath = limisDirPath + "/encrypt.txt";

    // 检测文件是否存在 存在则不创建
    if (QFile::exists(filePath)) 
    {
        qDebug() << "File encrypt.txt exists at: " << filePath;
        return 1;
    } 

    QDir limisDir(limisDirPath);

    if (!limisDir.exists()) 
    {
        if (limisDir.mkpath(".")) 
        {
            qDebug() << "Folder LIMIS created successfully at: " << limisDirPath;
        } 
        else 
        {
            qDebug() << "Failed to create folder LIMIS.";
            return -1;
        }
    } 
    else 
    {
        qDebug() << "Folder LIMIS already exists at: " << limisDirPath;
    }

    // 3. 在 LIMIS 文件夹中创建文件 encrypt.txt
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) 
    {
        QTextStream out(&file);

        // 4. 向文件中写入 dbfhbhdb 八个字符20460620
        out << "dbfhbhdb";
        file.close();
        qDebug() << "File encrypt.txt created and written successfully at: " << filePath;
    } else 
    {
        qDebug() << "Failed to create or write to file encrypt.txt.";
    }
    return 0;
}
void printAllWidgetsFont(QWidget *parent) {
    if (!parent) {
        return;
    }

    // 打印当前控件的字体信息
    QFont font = parent->font();
    if(font.family() != "Microsoft YaHei")
    {
    qDebug() << "Widget:" << parent->metaObject()->className()
             << "| ObjectName:" << parent->objectName()
             << "| Font:" << font.family()
             << "| Size:" << font.pointSize()
             << "| Bold:" << font.bold()
             << "| Italic:" << font.italic();
    }

    // 递归遍历所有子控件
    for (QObject *child : parent->children()) {
        if (child->isWidgetType()) {
            printAllWidgetsFont(qobject_cast<QWidget*>(child));
        }
    }
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //加密解密
    // 打开文件
    QFile setfile(":/encrypt.txt");  // 替换为实际的文件路径  文件打包时打入到资源文件中了 要修改只能重新打包

    if (!setfile.open(QIODevice::ReadOnly)) {
        qDebug() << "无加密文件";
        return -1;
    }

    // 使用 QTextStream 读取文件内容
    QTextStream in(&setfile);
    QString content = in.readAll();  // 读取文件的所有内容
    content.remove('\n');
    //判断是否是英文字符
    // 定义正则表达式，匹配只包含小写字母的字符串
    /*
    QRegExp regex("^[b-k]+$");
    if (!regex.exactMatch(content)) {
        return -1;
    }
    if (content.size()!=8){
        return -1;
    }
    */
    //QString c= encrypt(content);
    QString b= decrypt(content);
    qDebug() << b ;
    int year =b.left(4).toInt();
    int mon = b.mid(4,2).toInt();
    int day = b.right(2).toInt();
    QDate dedate = QDate(year,mon,day);
    
    // 获取当前系统的日期
    QDate currentDate = QDateTime::currentDateTime().date();
    if(currentDate > dedate)
    {
        qDebug() << dedate << " , " << currentDate;
        if (CheckRegister())
        {
            qDebug() << "注册完成 , 可以打开";
        }
        else
        {
            QMessageBox::warning(nullptr, "Storage Error",QString("使用时间到期, 请联系开发人员"));
            return -1;
        }
    }

    // 第一次验证通过 在C盘固定目录下生成一个文件  C:\Program Files\LIMS\encrypt.txt
    RegisterExe();
    // 输出文件内容
    qDebug() << "文件内容：\n" << b;

    // 关闭文件
    setfile.close();


   // 设置全局字体（仅指定字体，不改变大小）
    QFont font("Microsoft YaHei");
    QApplication::setFont(font);
    // 设置统一的样式表
    QFile file(":/style.css");  // 样式表文件路径
    if (!file.open(QFile::ReadOnly)) {
        qWarning("Unable to open the style file!");
        return -1;
    }
    QString styleSheet = QLatin1String(file.readAll());
    int index = styleSheet.indexOf("QWidget");
    if (index != -1) {
        // 删除子字符串之前的所有字符
        styleSheet.remove(0, index);  // 从位置0开始，删除到子字符串出现位置的所有字符
        qDebug() << "Result: " << styleSheet;
    }
    a.setStyleSheet(styleSheet);  // 应用样式表
    // 设置编码为“UTF-8”
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    OperationInterface w;

    w.setWindowTitle("LIMS");
    w.setWindowIconText("LIMS");
    w.show();

    QFont appFont = QApplication::font();
    qDebug() << "Application font family:" << appFont.family();

     printAllWidgetsFont(&w); // 打印当前窗口所有控件的字体

    return a.exec();
}
