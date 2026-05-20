#include "readpoint.h"
#include <QFile>
#include <QDomDocument>
#include <QDebug>

ReadPoint::ReadPoint() {}

std::vector<std::vector<int>> ReadPoint::readXml(const QString &fileName,const QString &rootname) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "Error opening file:" << file.errorString();
        return std::vector<std::vector<int>>();
    }

    // 读取文件内容
    QByteArray fileData = file.readAll();
    file.close();

    // 解析XML
    QDomDocument doc;
    if (!doc.setContent(fileData)) {
        qDebug() << "Failed to parse XML.";
        return   std::vector<std::vector<int>>();
    }

    // 获取根元素
    QDomElement root = doc.documentElement();

    // 获取 <coordinates> 元素
    std::vector<std::vector<int>> res;
    QDomNodeList coordinateNodes = root.elementsByTagName(rootname);
    for (int i = 0; i < coordinateNodes.count(); ++i) {
        QDomNode coordinateNode = coordinateNodes.at(i);

        // 获取 <point> 元素
        QDomNodeList pointNodes = coordinateNode.toElement().elementsByTagName("point");
        for (int j = 0; j < pointNodes.count(); ++j) {
            QDomNode pointNode = pointNodes.at(j);
            QDomElement pointElement = pointNode.toElement();

            // 获取 <x> 和 <y> 的值
            int x = pointElement.firstChildElement("x").text().toInt();
            int y = pointElement.firstChildElement("y").text().toInt();

            // 输出坐标
            qDebug() << "x:" << x << ", y:" << y;
            res.push_back(std::vector<int>{x,y});
        }
    }
    return res;
}
