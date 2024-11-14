#ifndef SHEETFILLDATARANGE_H
#define SHEETFILLDATARANGE_H

class CSheetFillDataRange
{
public:
    CSheetFillDataRange();

    int InitData();

    int GetMinRow();
    int GetMaxRow();
    int GetMinColumn();
    int GetMaxColumn();
    int GetNowColumn();
    void AddNowColun();

private:
    int m_iMinRow; // 开始写的行
    int m_iMaxRow; // 结束写的行
    int m_iMinColumn; //开始列
    int m_iMaxColumn; //开始列

    int m_iNowColumn;// 当前可写行
};

#endif // SHEETFILLDATARANGE_H
