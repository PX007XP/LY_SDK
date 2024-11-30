#include "operationinterface.h"

#include <QApplication>
#include <QFile>
//#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置统一的样式表
    QFile file(":/style.css");  // 样式表文件路径
    if (!file.open(QFile::ReadOnly)) {
        qWarning("Unable to open the style file!");
        return -1;
    }
    QString styleSheet = QLatin1String(file.readAll());
    a.setStyleSheet(styleSheet);  // 应用样式表
    // 设置编码为“UTF-8”
  //  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    OperationInterface w;

    w.show();
    return a.exec();
}
