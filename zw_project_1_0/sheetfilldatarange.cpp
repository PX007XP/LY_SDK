#include "sheetfilldatarange.h"



CSheetFillDataRange::CSheetFillDataRange()
{

}

int CSheetFillDataRange::InitData()
{
    // 每个表初始化不同

    m_iMinRow = 15;
    m_iMaxRow = 47;
    m_iMinColumn = 10;
    m_iMaxColumn = 162;
    m_iNowColumn = m_iMinColumn;
    return 0;
}

int CSheetFillDataRange::GetMinRow()
{
    return m_iMinRow;
}

int CSheetFillDataRange::GetMaxRow()
{
    return m_iMaxRow;
}

int CSheetFillDataRange::GetMinColumn()
{
    return m_iMinColumn;
}

int CSheetFillDataRange::GetMaxColumn()
{
    return m_iMaxColumn;
}

int CSheetFillDataRange::GetNowColumn()
{
    return m_iNowColumn;
}

void CSheetFillDataRange::AddNowColun()
{
    if(m_iNowColumn < m_iMinColumn)
    {
        m_iNowColumn++;
    }
}
