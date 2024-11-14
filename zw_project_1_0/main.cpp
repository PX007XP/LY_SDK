#include "operationinterface.h"

#include <QApplication>
//#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // 设置编码为“UTF-8”
  //  QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    OperationInterface w;
    w.show();
    return a.exec();
}
