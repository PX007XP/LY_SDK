#include "operationinterface.h"

#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QString>
#include <QMap>

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
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //加密解密
    // 打开文件
    QFile setfile(":/encrypt.txt");  // 替换为实际的文件路径

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
    int year =b.left(4).toInt();
    int mon = b.mid(4,2).toInt();
    int day = b.right(2).toInt();
    QDate dedate = QDate(year,mon,day);
    // 获取当前系统的日期
    QDate currentDate = QDateTime::currentDateTime().date();
    if(currentDate>dedate){
        return -1;
    }

    // 输出文件内容
    qDebug() << "文件内容：\n" << b;

    // 关闭文件
    setfile.close();

    // 设置统一的样式表
    QFile file(":/style.css");  // 样式表文件路径
    if (!file.open(QFile::ReadOnly)) {
        qWarning("Unable to open the style file!");
        return -1;
    }
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);  // 应用样式表
    // 设置编码为“UTF-8”
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    OperationInterface w;


    w.show();
    return a.exec();
}
