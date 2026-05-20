#ifndef READPOINT_H
#define READPOINT_H
#include <QString>
#include <vector>

class ReadPoint
{
public:
    ReadPoint();
    std::vector<std::vector<int>> readXml(const QString &fileName,const QString &rootname);
};

#endif // READPOINT_H
