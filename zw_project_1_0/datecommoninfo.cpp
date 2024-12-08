#include "dateCommonInfo.h"

#include <QDebug>
#include <QInputDialog>
#include <QPainter>
#include <QStyleOption>
#include <QDateTime>
#include <QPushButton>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QDate>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QDebug>
#include <QFont>
#include <QMenu>
#include <QComboBox>
#include <QListView>
#include <QStyledItemDelegate>

#define T_D_YAER   1924 //  天干地支开始计算年月
#define Has_Lunar 0 //农历的宏开关


//每年春节对应的公历日期
static const int springFestival[] = {
    130,217,206,                                // 1968,1969,1970
    127,215,203,123,211,131,218,207,128,216,    // 1971--1980
    205,125,213,202,220,209,219,217,206,127,    // 1981---1990
    215,204,123,210,131,219,207,128,216,205,    // 1991--2000
    124,212,201,122,209,129,218,207,126,214,    // 2001--2010
    203,123,210,131,219,208,128,216,205,125,    // 2011--2020                                       //2011--2020
    212,201,122,210,129,217,206,126,213,203,    // 2021--2030
    123,211,131,219,208,128,215,204,124,212     // 2031--2040
};

//16--18位表示闰几月，0--12位表示农历每月的数据，高位表示1月，低位表示12月（农历闰月就会多一个月）
static const int  nLunarData[] = {
    461653,1386,2413,                                            // 1968,1969,1970
    330077,1197,2637,268877,3365,531109,2900,2922,398042,2395,   // 1971--1980
    1179,267415,2635,661067,1701,1748,398772,2742,2391,330031,   // 1981---1990
    1175,1611,200010,3749,527717,1452,2742,332397,2350,3222,     // 1991--2000
    268949,3402,3493,133973,1386,464219,605,2349,334123,2709,    // 2001--2010
    2890,267946,2773,592565,1210,2651,395863,1323,2707,265877,   // 2011--2020
    1706,2773,133557,1206,398510,2638,3366,335142,3411,1450,     // 2021 -- 2030
    200042,2413,723293,1197,2637,399947,3365,3410,334676,2906    // 2031 -- 2040
};

static const int chineseTwentyFourData[] = {
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 1970
    0x96,0xB4,0x96,0xA6,0x97,0x97,0x78,0x79,0x79,0x69,0x78,0x77,     // 1971
    0x96,0xA4,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 1972
    0xA5,0xB5,0x96,0xA5,0xA6,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 1973
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 1974
    0x96,0xB4,0x96,0xA6,0x97,0x97,0x78,0x79,0x78,0x69,0x78,0x77,     // 1975
    0x96,0xA4,0xA5,0xB5,0xA6,0xA6,0x88,0x89,0x88,0x78,0x87,0x87,     // 1976
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 1977
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x78,0x87,     // 1978
    0x96,0xB4,0x96,0xA6,0x96,0x97,0x78,0x79,0x78,0x69,0x78,0x77,     // 1979
    0x96,0xA4,0xA5,0xB5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 1980
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x77,0x87,     // 1981
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x77,0x87,     // 1982
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x78,0x79,0x78,0x69,0x78,0x77,     // 1983
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x87,     // 1984
    0xA5,0xB4,0xA6,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 1985
    0xA5,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x77,0x87,     // 1986
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x79,0x78,0x69,0x78,0x87,     // 1987
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 1988
    0xA5,0xB4,0xA5,0xA5,0xA6,0x96,0x88,0x88,0x88,0x78,0x87,0x87,     // 1989
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x79,0x77,0x87,     // 1990
    0x95,0xB4,0x96,0xA5,0x86,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 1991
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 1992
    0xA5,0xB3,0xA5,0xA5,0xA6,0x96,0x88,0x88,0x88,0x78,0x87,0x87,     // 1993
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 1994
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x76,0x78,0x69,0x78,0x87,     // 1995
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 1996
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 1997
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 1998
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 1999
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2000
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2001
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 2002
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 2003
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2004
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2005
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2006
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x69,0x78,0x87,     // 2007
    0x96,0xB4,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     // 2008
    0xA5,0xB3,0xA5,0xB5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2009
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2010
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x78,0x87,     // 2011
    0x96,0xB4,0xA5,0xB5,0xA5,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     // 2012
    0xA5,0xB3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x87,     // 2013
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2014
    0x95,0xB4,0x96,0xA5,0x96,0x97,0x88,0x78,0x78,0x79,0x77,0x87,     // 2015
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x87,0x88,0x87,0x78,0x87,0x86,     // 2016
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x87,     // 2017
    0xA5,0xB4,0xA6,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2018
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x79,0x77,0x87,     // 2019
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x86,     // 2020
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2021
    0xA5,0xB4,0xA5,0xA5,0xA6,0x96,0x88,0x88,0x88,0x78,0x87,0x87,     // 2022
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x79,0x77,0x87,     // 2023
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     // 2024
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2025
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2026
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 2027
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     // 2028
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2029
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87,     // 2030
    0xA5,0xB4,0x96,0xA5,0x96,0x96,0x88,0x78,0x78,0x78,0x87,0x87,     // 2031
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     // 2032
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x86,     // 2033
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x78,0x88,0x78,0x87,0x87,     // 2034
    0xA5,0xB4,0x96,0xA5,0xA6,0x96,0x88,0x88,0x78,0x78,0x87,0x87,     // 2035
    0x95,0xB4,0xA5,0xB4,0xA5,0xA6,0x97,0x87,0x87,0x78,0x87,0x96,     // 2036
    0xA5,0xC3,0xA5,0xB5,0xA6,0xA6,0x87,0x88,0x88,0x78,0x87,0x86,     // 2037
    0xA5,0xB3,0xA5,0xA5,0xA6,0xA6,0x88,0x88,0x88,0x78,0x87,0x87      // 2038
};

static const QString dayName[] =  {
    LC_STR("*"),
    LC_STR("初一"), LC_STR("初二"), LC_STR("初三"), LC_STR("初四"), LC_STR("初五"),
    LC_STR("初六"), LC_STR("初七"), LC_STR("初八"), LC_STR("初九"), LC_STR("初十"),
    LC_STR("十一"), LC_STR("十二"), LC_STR("十三"), LC_STR("十四"), LC_STR("十五"),
    LC_STR("十六"), LC_STR("十七"), LC_STR("十八"), LC_STR("十九"), LC_STR("二十"),
    LC_STR("廿一"), LC_STR("廿二"), LC_STR("廿三"), LC_STR("廿四"), LC_STR("廿五"),
    LC_STR("廿六"), LC_STR("廿七"), LC_STR("廿八"), LC_STR("廿九"), LC_STR("三十")
};

/*农历月份名*/
static const QString monName[] = {
    LC_STR("*"),
    LC_STR("正月"), LC_STR("二月"), LC_STR("三月"), LC_STR("四月"),
    LC_STR("五月"), LC_STR("六月"), LC_STR("七月"), LC_STR("八月"),
    LC_STR("九月"), LC_STR("十月"), LC_STR("冬月"), LC_STR("腊月")
};

// 24节气
static const QString solarTerm[] = {
    LC_STR("小寒"), LC_STR("大寒"), LC_STR("立春"), LC_STR("雨水"), LC_STR("惊蛰"), LC_STR("春分"), LC_STR("清明"), LC_STR("谷雨"),
    LC_STR("立夏"), LC_STR("小满"), LC_STR("芒种"), LC_STR("夏至"), LC_STR("小暑"), LC_STR("大暑"), LC_STR("立秋"), LC_STR("处暑"),
    LC_STR("白露"), LC_STR("秋分"), LC_STR("寒露"), LC_STR("霜降"), LC_STR("立冬"), LC_STR("小雪"), LC_STR("大雪"), LC_STR("冬至")
};


// 天干算法
static const QString strTiangan[] = {
    LC_STR("甲"), LC_STR("乙"), LC_STR("丙"), LC_STR("丁"), LC_STR("戊"),
    LC_STR("己"), LC_STR("庚"), LC_STR("辛"), LC_STR("壬"), LC_STR("癸"),
};

// 动物属性
static const QString strAnimal[] = {
    LC_STR("鼠"), LC_STR("牛"), LC_STR("虎"), LC_STR("兔"), LC_STR("龙"), LC_STR("蛇"),
    LC_STR("马"), LC_STR("羊"), LC_STR("猴"), LC_STR("鸡"), LC_STR("狗"), LC_STR("猪"),
};

// 地址算法
static const QString strDizhi[] = {
    LC_STR("子"), LC_STR("丑"), LC_STR("寅"), LC_STR("卯"), LC_STR("辰"), LC_STR("巳"),
    LC_STR("午"), LC_STR("未"), LC_STR("申"), LC_STR("酉"), LC_STR("戌"), LC_STR("亥"),
};

/*公历每月前面的天数*/
int monthAdd[] = {
    0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334
};


DateCommonInfo::DateCommonInfo(QObject *parent) : QObject(parent)
{

}

/**
 * @brief Date::getSpringFestivalMonth 获取当年春节是几月几日
 * @param year
 * @return
 */
quint16 DateCommonInfo::getSpringFestivalDate(int year)
{
    int nTemp = year - 1968;
    int springFestivalMonth = springFestival[nTemp] / 100;
    int springFestivalDay = springFestival[nTemp] % 100;
    qDebug() << springFestivalMonth << springFestivalDay;

    return (springFestivalMonth << 8) | springFestivalDay;
}

int DateCommonInfo::getFirstDayOfWeek(int year, int month)
{
    int week = 0;
    // 获取当年1月1日是星期几
    week = (year + (year- 1) / 4 -(year - 1) / 100 + (year - 1) / 400) % 7;
    week += getTotalMonthDays(year, month);
    return week % 7;
}

int DateCommonInfo::getTotalMonthDays(int year, int month)
{
    int nDays = 0;
    int nLoopDay = isLoopYaer(year) ? 1 : 0;
    switch (month) {
    case  1: nDays =   0;            break;
    case  2: nDays =  31;            break;
    case  3: nDays =  59 + nLoopDay; break;
    case  4: nDays =  90 + nLoopDay; break;
    case  5: nDays = 120 + nLoopDay; break;
    case  6: nDays = 151 + nLoopDay; break;
    case  7: nDays = 181 + nLoopDay; break;
    case  8: nDays = 212 + nLoopDay; break;
    case  9: nDays = 243 + nLoopDay; break;
    case 10: nDays = 273 + nLoopDay; break;
    case 11: nDays = 304 + nLoopDay; break;
    case 12: nDays = 334 + nLoopDay; break;
    default: nDays = 0; break;
    }
    return nDays;
}

int DateCommonInfo::getMonthDays(int year, int month)
{
    int nDays = 0;
    int nLoopDay = isLoopYaer(year) ? 1 : 0;
    switch (month) {
    case  1: nDays = 31;            break;
    case  2: nDays = 28 + nLoopDay; break;
    case  3: nDays = 31;            break;
    case  4: nDays = 30;            break;
    case  5: nDays = 31;            break;
    case  6: nDays = 30;            break;
    case  7: nDays = 31;            break;
    case  8: nDays = 31;            break;
    case  9: nDays = 30;            break;
    case 10: nDays = 31;            break;
    case 11: nDays = 30;            break;
    case 12: nDays = 31;            break;
    default: nDays = 30;            break;
    }

    return nDays;
}

bool DateCommonInfo::isLoopYaer(int year)
{
    return (((0 == (year % 4)) && (0 != (year % 100))) || (0 == (year % 400)));
}

/**
 * @brief Date::getLunarDate 计算农历
 * @param year  年
 * @param month 月
 * @param day 日
 * @return
 */
QString DateCommonInfo::getLunarDate (int year, int month, int day){
    int nTheDate,nIsEnd,nMonTemp,k,n,nBit;
    // 先获取公历节日
    QString strDate = holiday(month, day);
    // 计算24节气
    QString strSolarTerms = solarTerms(year, month, day);

    /*现在计算农历：获得当年春节的公历日期（比如：2015年春节日期为（2月19日）），
            以此为分界点，2.19前面的农历是2014年农历（用2014年农历数据来计算），
            2.19以及之后的日期，农历为2015年农历（用2015年农历数据来计算）。*/
    nMonTemp = year - 1968;
    int springFestivalMonth = springFestival[nMonTemp] / 100;
    int springFestivalDaty = springFestival[nMonTemp] % 100;

    if(month < springFestivalMonth )
    {
        nMonTemp--;
        nTheDate = 365 * 1 + day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

        if((!(year % 4)) && (month > 2))
            nTheDate = nTheDate + 1;

        if((!((year - 1) % 4)))
            nTheDate = nTheDate + 1;
    }
    else if (month == springFestivalMonth)
    {
        if (day < springFestivalDaty) {
            nMonTemp--;
            nTheDate = 365 * 1 + day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

            if((!(year % 4)) && (month > 2))
                nTheDate = nTheDate + 1;

            if((!((year-1) % 4)))
                nTheDate = nTheDate + 1;
        }
        else {
            nTheDate = day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

            if((!(year % 4)) && (month > 2))
                nTheDate = nTheDate + 1;
        }
    }else{
        nTheDate = day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;
        if((!(year % 4)) && (month > 2))
            nTheDate = nTheDate + 1;
    }
    /*--计算农历天干、地支、月、日---*/
    nIsEnd = 0;

    while(nIsEnd != 1)  {
        if(nLunarData[nMonTemp] < 4095)
            k = 11;
        else
            k = 12;
        n = k;
        while(n >= 0)   {
            // 获取wNongliData(m)的第n个二进制位的值
            nBit = nLunarData[nMonTemp];

            nBit = nBit >> n;
            nBit = nBit % 2;
            if (nTheDate <= (29 + nBit))    {
                nIsEnd = 1;
                break;
            }

            nTheDate = nTheDate - 29 - nBit;
            n = n - 1;
        }

        if(nIsEnd)
            break;

        nMonTemp = nMonTemp + 1;
    }

    // 农历的年月日
    year = 1969 + nMonTemp -1;
    month = k - n + 1;
    day = nTheDate;

    if (k == 12)  {
        if (month == (nLunarData[nMonTemp] / 65536) + 1)
            month = 1 - month;
        else if (month > (nLunarData[nMonTemp] / 65536) + 1)
            month = month - 1;
    }

    // 显示装换的农历
    // only day == 1 ,return month name
    if (1 == day) {
        if(month < 1){
            strDate = "闰" + monName[month * -1];
            return strDate;
        }

        // 公历节日
        if ("" != strDate) return strDate;

        // 计算农历节日
        strDate = lunarFestival(month, day);

        // 如果有节日，直接显示
        if ("" == strDate) {
            // 如果当天不是24节气，显示农历日子
            strDate = strSolarTerms;
            if ("" == strDate) {
                strDate = monName[month];
            }
        }

    } else {
        // 公历节日
        if ("" != strDate) return strDate;

        // 计算农历节日
        strDate = lunarFestival(month, day);
        // 如果有节日，直接显示
        if ("" == strDate) {
            // 如果当天不是24节气，显示农历日子
            strDate = strSolarTerms;
            if ("" == strDate) {
                strDate = dayName[day];
            }
        }
    }

    return strDate;
}

/**
 * @brief Date::getLunarMonAndDay 响应点击时的农历显示
 * @param year
 * @param month
 * @param day
 * @return
 */
QString DateCommonInfo::getLunarMonAndDay(int year, int month, int day)
{
    int nTheDate, nIsEnd, nMonTemp, k, n, nBit;
    QString strDate = "";
    /*现在计算农历：获得当年春节的公历日期（比如：2015年春节日期为（2月19日）），
            以此为分界点，2.19前面的农历是2014年农历（用2014年农历数据来计算），
            2.19以及之后的日期，农历为2015年农历（用2015年农历数据来计算）。*/
    nMonTemp = year - 1968;
    int springFestivalMonth = springFestival[nMonTemp] / 100;
    int springFestivalDaty = springFestival[nMonTemp] % 100;

    if(month < springFestivalMonth )
    {
        nMonTemp--;
        nTheDate = 365 * 1 + day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

        if((!(year % 4)) && (month > 2))
            nTheDate = nTheDate + 1;

        if((!((year - 1) % 4)))
            nTheDate = nTheDate + 1;
    }
    else if (month == springFestivalMonth)
    {
        if (day < springFestivalDaty) {
            nMonTemp--;
            nTheDate = 365 * 1 + day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

            if((!(year % 4)) && (month > 2))
                nTheDate = nTheDate + 1;

            if((!((year-1) % 4)))
                nTheDate = nTheDate + 1;
        }
        else {
            nTheDate = day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;

            if((!(year % 4)) && (month > 2))
                nTheDate = nTheDate + 1;
        }
    }else{
        nTheDate = day + monthAdd[month - 1] - 31 * ((springFestival[nMonTemp] / 100) - 1) - springFestival[nMonTemp] % 100 + 1;
        if((!(year % 4)) && (month > 2))
            nTheDate = nTheDate + 1;
    }
    /*--计算农历天干、地支、月、日---*/
    nIsEnd = 0;

    while(nIsEnd != 1)  {
        if(nLunarData[nMonTemp] < 4095)
            k = 11;
        else
            k = 12;
        n = k;
        while(n >= 0)   {
            // 获取wNongliData(m)的第n个二进制位的值
            nBit = nLunarData[nMonTemp];

            nBit = nBit >> n;
            nBit = nBit % 2;
            if (nTheDate <= (29 + nBit))    {
                nIsEnd = 1;
                break;
            }

            nTheDate = nTheDate - 29 - nBit;
            n = n - 1;
        }

        if(nIsEnd)
            break;

        nMonTemp = nMonTemp + 1;
    }

    // 农历的年月日
    year = 1969 + nMonTemp -1;
    month = k - n + 1;
    day = nTheDate;

    if (k == 12)  {
        if (month == (nLunarData[nMonTemp] / 65536) + 1)
            month = 1 - month;
        else if (month > (nLunarData[nMonTemp] / 65536) + 1)
            month = month - 1;
    }

    // 显示装换的农历
    // only day == 1 ,return month name
    if (1 == day) {
        if (month < 1){
            strDate = LC_STR("闰") + monName[month * -1];
            return strDate;
        }

        strDate = monName[month];

    } else {
        strDate = monName[month]+ dayName[day];
    }

    return strDate;
}

/**
 * @brief Date::getLunarTime  计算今年是什么年如 ：甲子年
 * @param year
 * @return
 */
QString DateCommonInfo::getLunarTime(int year)
{
    int ntemp = 0;
    // 农历时辰
    QString strTime = "";
    if (year > T_D_YAER) {
        ntemp = year - T_D_YAER;
        strTime.append(strTiangan[ntemp % 10]);
        strTime.append(strDizhi[ntemp % 12]);
        strTime.append(strAnimal[ntemp % 12]);
        strTime.append(LC_STR("年"));
    }

    return strTime;
}


/**
 * @brief Date::holiday 公历假日
 * @param month
 * @param day
 * @return
 */
QString DateCommonInfo::holiday(int month, int day)
{
    int temp = (month << 8) | day;
    QString strHoliday = "";
    switch (temp) {
    case 0x0101: strHoliday = LC_STR("元旦");  break;
    case 0x020E: strHoliday = LC_STR("情人节"); break;
    case 0x0308: strHoliday = LC_STR("妇女节"); break;
    case 0x0401: strHoliday = LC_STR("愚人节"); break;
    case 0x0501: strHoliday = LC_STR("劳动节"); break;
    case 0x0504: strHoliday = LC_STR("青年节"); break;
    case 0x0601: strHoliday = LC_STR("儿童节"); break;
    case 0x0701: strHoliday = LC_STR("建党节"); break;
    case 0x0801: strHoliday = LC_STR("建军节"); break;
    case 0x090A: strHoliday = LC_STR("教师节"); break;
    case 0x0A01: strHoliday = LC_STR("国庆节"); break;
    case 0x0C18: strHoliday = LC_STR("圣诞节"); break;
    default: break;
    }

    return strHoliday;
}

/**
 * @brief Date::chineseTwentyFourDay 计算24节气
 * @param year
 * @param month
 * @param day
 * @return
 */
QString DateCommonInfo::solarTerms(int year, int month, int day){
    int dayTemp = 0;
    int index = (year - 1970) * 12 + month - 1;

    if (day < 15) {
        dayTemp = 15 - day;
        if((chineseTwentyFourData[index] >> 4) == dayTemp)
            return solarTerm[2 * (month - 1)];
        else
            return "";

    } else if (day > 15) {
        dayTemp = day - 15;
        if((chineseTwentyFourData[index] & 0x0f) == dayTemp)
            return solarTerm[2 * (month - 1) + 1];
    }

    return "";
}

/**
 * @brief Date::lunarFestival 农历春节节日
 * @param month
 * @param day
 * @return 节日
 */
QString DateCommonInfo::lunarFestival(int month, int day) {
    int temp = (month << 8) | day;
    QString strFestival = "";
    switch (temp) {
    case 0x0101: strFestival = LC_STR("春节");  break;
    case 0x010F: strFestival = LC_STR("元宵节"); break;
    case 0x0202: strFestival = LC_STR("龙抬头"); break;
    case 0x0505: strFestival = LC_STR("端午节"); break;
    case 0x0707: strFestival = LC_STR("七夕节"); break;
    case 0x080F: strFestival = LC_STR("中秋节"); break;
    case 0x0909: strFestival = LC_STR("重阳节"); break;
    case 0x0C08: strFestival = LC_STR("腊八节"); break;
    default: break;
    }

    return strFestival;
}


static const QString s_strWeek[] = {
    LC_STR("周日"), LC_STR("周一"), LC_STR("周二"),
    LC_STR("周三"), LC_STR("周四"), LC_STR("周五"),
    LC_STR("周六"),
};

CalendarWidget::CalendarWidget(QString fromat ,QWidget *parent, Qt::WindowFlags f)
    : QWidget(parent, f)
{
    m_fromat = fromat;
    // 获取当前年月日
    m_nYear  = QDate::currentDate().year();
    m_nMonth = QDate::currentDate().month();
    m_nDay = QDate::currentDate().day();
    m_pCrtSelect = NULL;

    //  设置默认日期范围
    m_minDt = QDateTime(QDate(1900,1,1));
    m_maxDt = QDateTime(QDate(2099,12,31), QTime(23, 59, 59));

    initWidget();
    initDate();
    initStyleSheet();
    UpdateYear();
}

CalendarWidget::~CalendarWidget()
{

}

void CalendarWidget::initStyleSheet()
{

    setAutoFillBackground(false);
    setAttribute(Qt::WA_TranslucentBackground, true);
}

void CalendarWidget::UpdateYear()
{
    comboBox_Year->clear();
    QDate d1 = m_minDt.date();
    QDate d2 = m_maxDt.date();
    for (int i = d1.year(); i<= d2.year(); i++)
    {
        comboBox_Year->addItem(QString::number(i));
    }
}

DayLabel *CalendarWidget::getDayLabel(int y, int m, int d)
{
    int nWeek  = DateCommonInfo::getFirstDayOfWeek(y, m);
    nWeek = (0 == nWeek ? 7 : nWeek);
    // 显示当前天数
    return labelDay[d + nWeek - 1];
}

void CalendarWidget::changeCurrentSelectDay()
{
    DayLabel *pLabel = getDayLabel(m_nYear, m_nMonth, m_nDay);

    if(m_pCrtSelect)
        m_pCrtSelect->setSelected(false);
    m_pCrtSelect = pLabel;
    if(m_pCrtSelect)
        m_pCrtSelect->setSelected(true);
}

//void CalendarWidget::paintEvent(QPaintEvent *e)
//{
//    QPainter p(this);
//    p.drawPixmap(0, 0, QPixmap(":/Resources/bk.png").scaled(size()));
//
//    QWidget::paintEvent(e);
//}

int CalendarWidget::year() const
{
    return m_nYear;
}

void CalendarWidget::setYear(int nYear)
{
    m_nYear = nYear;
    disconnect(comboBox_Year, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxDateChange(int)));
    comboBox_Year->setCurrentIndex(comboBox_Year->findText(QString::number(nYear)));
    connect(comboBox_Year, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxDateChange(int)));
}

int CalendarWidget::month() const
{
    return m_nMonth;
}

void CalendarWidget::setMonth(int nMonth)
{
    m_nMonth = nMonth;
    disconnect(comboBox_Month, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxDateChange(int)));
    comboBox_Month->setCurrentIndex(nMonth - 1);
    connect(comboBox_Month, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxDateChange(int)));
}

int CalendarWidget::day() const
{
    return m_nDay;
}

void CalendarWidget::setDay(int nDay)
{
    m_nDay = nDay;
}

int CalendarWidget::hour() const
{
    return m_nHour;
}

void CalendarWidget::setHour(int h)
{
    m_nHour = h;
    disconnect(comboBox_Hour, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxTimeChange(int)));
    comboBox_Hour->setCurrentIndex(h);
    connect(comboBox_Hour, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxTimeChange(int)));
}

int CalendarWidget::minute()
{
    return m_nMin;
}

void CalendarWidget::setMinute(int m)
{
    m_nMin = m;
    disconnect(comboBox_min, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxTimeChange(int)));
    comboBox_min->setCurrentIndex(m);
    connect(comboBox_min, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxTimeChange(int)));
}


int CalendarWidget::second()
{
    return m_nSec;
}

void CalendarWidget::setSecond(int s)
{
    m_nSec = s;
    disconnect(comboBox_sec, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxTimeChange(int)));
    comboBox_sec->setCurrentIndex(s);
    connect(comboBox_sec, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxTimeChange(int)));
}

void CalendarWidget::jumpToDateTime(const QDateTime& dt)
{
    setYear(dt.date().year());
    setMonth(dt.date().month());
    setDay(dt.date().day());
    setHour(dt.time().hour());
    setMinute(dt.time().minute());
    setSecond(dt.time().second());

    initDate();

    changeCurrentSelectDay();
}

void CalendarWidget::setDateTimeRange(const QDateTime &min, const QDateTime &max)
{
    if(max <= min)
        return;

    m_minDt = min; m_maxDt = max;
}

void CalendarWidget::dateTimeRange(QDateTime &min, QDateTime &max)
{
    min = m_minDt; max = m_maxDt;
}

/**
 * @brief CalendarWidget::initWidget 初始化界面
 */
void CalendarWidget::initWidget()
{
    this->setMinimumSize(400, 300);
    this->setObjectName("widgetCalendar");

    QGridLayout * qgridlayout = new QGridLayout(this);
    qgridlayout->setContentsMargins(0, 0, 0, 0);


    m_base = new QWidget(this);
    m_base->setObjectName("baseWidget");
    //m_base->setMinimumSize(size());

    qgridlayout->addWidget(m_base);

    verLayoutCalendar = new QVBoxLayout(m_base);
    verLayoutCalendar->setContentsMargins(0, 10, 0, 0);
    //    verLayoutCalendar->setSpacing(6);

    //! [1] 标题行
    widgetTitle = new QWidget(this);
    widgetTitle->setObjectName("widgetTitle");
    widgetTitle->setMinimumHeight(32);

    comboBox_Year = new QComboBox(this);
    comboBox_Month = new QComboBox(this);
    comboBox_Hour = new QComboBox(this);
    label_splite = new QLabel(this);
    comboBox_min = new QComboBox(this);
    label_splite2 = new QLabel(this);
    comboBox_sec = new QComboBox(this);


    QStringList monthList;
    monthList<<LC_STR("一月")<<LC_STR("二月")<<LC_STR("三月")<<LC_STR("四月")<<LC_STR("五月")<<LC_STR("六月")<<LC_STR("七月")<<LC_STR("八月")<<LC_STR("九月")<<LC_STR("十月")<<LC_STR("十一月")<<LC_STR("十二月");
    comboBox_Month->addItems(monthList);

    label_splite->setText(LC_STR(":"));
    label_splite->setMinimumWidth(4);
    label_splite2->setText(LC_STR(":"));
    label_splite2->setMinimumWidth(4);
    comboBox_Hour->clear();
    for (int i = 0; i < 24; ++i)
        comboBox_Hour->addItem(QString::asprintf("%02d", i));
    comboBox_min->clear();
    for (int i = 0; i < 60; ++i)
        comboBox_min->addItem(QString::asprintf("%02d", i));
    comboBox_sec->clear();
    for (int i = 0; i < 60; ++i)
        comboBox_sec->addItem(QString::asprintf("%02d", i));

    QHBoxLayout *HTopLayout = new QHBoxLayout(widgetTitle);
    HTopLayout->setContentsMargins(14, 0, 14, 0);
    HTopLayout->setSpacing(0);
    HTopLayout->addWidget(comboBox_Year);
    HTopLayout->addStretch(1);
    HTopLayout->addWidget(comboBox_Month);
    HTopLayout->addStretch(1);
    HTopLayout->addWidget(comboBox_Hour);
    HTopLayout->addWidget(label_splite);
    HTopLayout->addWidget(comboBox_min);
    HTopLayout->addWidget(label_splite2);
    HTopLayout->addWidget(comboBox_sec);
    HTopLayout->addStretch(1);

    verLayoutCalendar->addWidget(widgetTitle);

    comboBox_Year->setObjectName("comboBox_Year");
    comboBox_Month->setObjectName("comboBox_Month");
    comboBox_Hour->setObjectName("comboBox_Hour");
    comboBox_min->setObjectName("comboBox_Min");
    comboBox_sec->setObjectName("comboBox_Sec");
    label_splite->setObjectName("label_splite");

    comboBox_Year->setItemDelegate(new QStyledItemDelegate());
    comboBox_Month->setItemDelegate(new QStyledItemDelegate());
    comboBox_Hour->setItemDelegate(new QStyledItemDelegate());
    comboBox_min->setItemDelegate(new QStyledItemDelegate());
    comboBox_sec->setItemDelegate(new QStyledItemDelegate());

    connect(comboBox_Year, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxDateChange(int)));
    connect(comboBox_Month, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxDateChange(int)));
    connect(comboBox_Hour, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxTimeChange(int)));
    connect(comboBox_min, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxTimeChange(int)));
    connect(comboBox_sec, SIGNAL(currentIndexChanged(int)), this, SLOT(sltComboBoxTimeChange(int)));
    //! [1]

    //! [2] 星期行
    widgetWeek = new QWidget(this);
    widgetWeek->setObjectName("widgetWeek");

    horLayoutWeek = new QHBoxLayout(widgetWeek);
    horLayoutWeek->setContentsMargins(0, 0, 0, 0);
    horLayoutWeek->setSpacing(0);

    for (int i = 0; i < Week; i++) {
        labelWeek[i] = new QLabel(widgetWeek);
        labelWeek[i]->setText(s_strWeek[i]);
        labelWeek[i]->setObjectName("labelWeek");
        labelWeek[i]->setMinimumHeight(30);
        labelWeek[i]->setAlignment(Qt::AlignCenter);
        if ((0 == (i % 7)) || (6 == (i% 7))) {
            labelWeek[i]->setProperty("weekend", true);
            labelWeek[i]->setObjectName("labelWeekend");
        }
        horLayoutWeek->addWidget(labelWeek[i]);
    }

    verLayoutCalendar->addWidget(widgetWeek);
    //! [2]

    //! [3] 主体日期
    widgetBody = new QWidget(this);
    verLayoutCalendar->addWidget(widgetBody, 1);
    gridLayoutBody = new QGridLayout(widgetBody);
    gridLayoutBody->setHorizontalSpacing(0);
    gridLayoutBody->setVerticalSpacing(0);
    gridLayoutBody->setContentsMargins(0, 0, 0, 0);

    for (int i = 0; i < 42; i++) {
        labelDay[i] = new DayLabel(widgetBody);
        labelDay[i]->setObjectName("labelDay");
        labelDay[i]->setAlignment(Qt::AlignCenter);
        labelDay[i]->setText(QString::number(i));
        if ((0 == (i % 7)) || (6 == (i% 7))) {
            labelDay[i]->setProperty("weekend", true);
        }
        gridLayoutBody->addWidget(labelDay[i], i / 7, i % 7);
        connect(labelDay[i], SIGNAL(signalClicked(int,int)), this, SLOT(sltDayClicked(int,int)));
    }
    //! [3]

    //! [4] 底栏行
    widget_bottom = new QWidget(this);
    pushBtn_Rtn = new QPushButton(this);
    pushBtn_Now = new QPushButton(this);
    pushBtn_Ok = new QPushButton(this);
    pushBtn_Rtn->setFixedSize(67, 23);
    pushBtn_Now->setFixedSize(67, 23);
    pushBtn_Ok->setFixedSize(67, 23);

    pushBtn_Rtn->setText(LC_STR("返回今天"));
    pushBtn_Now->setText(LC_STR("此刻"));
    pushBtn_Ok->setText(LC_STR("确定"));

    QHBoxLayout* hBottomLay = new QHBoxLayout(widget_bottom);
    hBottomLay->setContentsMargins(25, 0, 25, 13);
    hBottomLay->addWidget(pushBtn_Rtn);
    hBottomLay->addStretch(1);
    hBottomLay->addWidget(pushBtn_Now);
    hBottomLay->addStretch(1);
    hBottomLay->addWidget(pushBtn_Ok);
    verLayoutCalendar->addWidget(widget_bottom);

    connect(pushBtn_Rtn, SIGNAL(clicked()), this, SLOT(slotPushBtnRtn()));
    connect(pushBtn_Now, SIGNAL(clicked()), this, SLOT(slotPushBtnNow()));
    connect(pushBtn_Ok, SIGNAL(clicked()), this, SLOT(slotPushBtnOk()));

    initSize();

    //! [4]
}

void CalendarWidget::setDisplayFormat(const QString &format)
{
    m_fromat = format;
    initSize();
}

void CalendarWidget::initSize()
{
    int height = 300;
    int width = 350;

    //m_fromat = "yM ";
    bool year_flag =m_fromat.contains("y");
    bool mon_flag =m_fromat.contains("M");
    bool day_flag =m_fromat.contains("d");
    bool hour_flag =m_fromat.contains("h") || m_fromat.contains("H");
    bool min_flag = m_fromat.contains("m");
    bool sec_flag = m_fromat.contains("s");


    comboBox_Year->show();
    comboBox_Month->show();
    widgetBody->show();
    comboBox_Hour->show();
    label_splite->show();
    comboBox_min->show();
    label_splite2->show();
    comboBox_sec->show();
    pushBtn_Rtn->show();
    pushBtn_Now->show();

    if(!year_flag)
    {
        comboBox_Year->hide();
    }
    if(!mon_flag)
    {
        comboBox_Month->hide();
    }
    if(!day_flag)
    {
        widgetBody->hide();
        widgetWeek->hide();
        height -= 220;
    }
    if(!hour_flag)
    {
        comboBox_Hour->hide();
        label_splite->hide();
    }
    if(!min_flag)
    {
        comboBox_min->hide();

    }
    if(!sec_flag)
    {
        label_splite2->hide();
        comboBox_sec->hide();
    }
    if((!year_flag) && (!mon_flag) && (!day_flag))
    {
        pushBtn_Rtn->hide();
        width -=160;
    }
    else if((!hour_flag) && (!min_flag) && (!sec_flag))
    {
        pushBtn_Now->hide();
        if(!day_flag)
        {
            width -=160;
        }
    }


    this->setMinimumSize(width, height);
    //m_base->setMinimumSize(width, height);
}

/**
 * @brief CalendarWidget::initDate 初始化日期
 */
void CalendarWidget::initDate()
{
    // 首先判断当前月的第一天是星期几
    int nWeek  = DateCommonInfo::getFirstDayOfWeek(m_nYear, m_nMonth);
    int nMonthDays = DateCommonInfo::getMonthDays(m_nYear, m_nMonth);
    // 上月天数
    int nPreMonDays = DateCommonInfo::getMonthDays(1 == m_nMonth ? m_nYear - 1 : m_nYear, 1 == m_nMonth ? 12 : m_nMonth - 1);

    // 显示上月剩余天数
    if (0 == nWeek) {
        // 显示上月天数
        for (int i = 0; i < 7; i++) {
            if(m_nMonth==1)
            {
                labelDay[i]->showDay((nPreMonDays - 7 + i + 1), DateCommonInfo::getLunarDate(m_nYear-1, 12, nPreMonDays - 7 + i + 1));
            }
            else
            {
                labelDay[i]->showDay((nPreMonDays - 7 + i + 1), DateCommonInfo::getLunarDate(m_nYear, m_nMonth-1, nPreMonDays - 7 + i + 1));
            }

            labelDay[i]->setColor(PREV_MONTH_DAY);
        }
        // 显示下月天数
        for (int i = 0; i < (42 - nMonthDays - 7); i++) {
            if(m_nMonth==12)
            {
                labelDay[nMonthDays + 7 + i]->showDay((i + 1), DateCommonInfo::getLunarDate(m_nYear+1, 1, i + 1));
            }
            else
            {
                labelDay[nMonthDays + 7 + i]->showDay((i + 1), DateCommonInfo::getLunarDate(m_nYear, m_nMonth+1, i + 1));
            }
            labelDay[nMonthDays + 7 + i]->setColor(NEXT_MONTH_DAY);
        }
    }
    else {
        for (int i = 0; i < nWeek; i++) {
            if(m_nMonth==1)
            {
                labelDay[i]->showDay((nPreMonDays - nWeek + i + 1), DateCommonInfo::getLunarDate(m_nYear-1, 12, (nPreMonDays - nWeek + i + 1)));
            }
            else
            {
                labelDay[i]->showDay((nPreMonDays - nWeek + i + 1), DateCommonInfo::getLunarDate(m_nYear, m_nMonth-1, (nPreMonDays - nWeek + i + 1)));
            }

            labelDay[i]->setColor(PREV_MONTH_DAY);
        }

        // 显示下月天数
        for (int i = (nWeek + nMonthDays); i < 42; i++) {
            if(m_nMonth==12)
            {
                labelDay[i]->showDay((i - (nWeek + nMonthDays) + 1), DateCommonInfo::getLunarDate(m_nYear+1, 1, (i - (nWeek + nMonthDays) + 1)));
            }
            else
            {
                labelDay[i]->showDay((i - (nWeek + nMonthDays) + 1), DateCommonInfo::getLunarDate(m_nYear, m_nMonth+1, (i - (nWeek + nMonthDays) + 1)));
            }

            labelDay[i]->setColor(NEXT_MONTH_DAY);
        }
    }

    // 显示当前月
    int nProperty = 1;
    int index = 0;
    for (int i = nWeek; i < (nMonthDays + nWeek); i++) {
        index = (0 == nWeek ? (i + 7) : i);
        labelDay[index]->showDay(i - nWeek + 1, DateCommonInfo::getLunarDate(m_nYear, m_nMonth, i - nWeek + 1));
        nProperty = (((0 == (i % 7)) || (6 == (i% 7))) ? WEEKEND_DAY : CURR_MONTH_DAY);
        labelDay[index]->setColor(nProperty);
    }

    //  如果现在显示的是当前月，则设置当前的日期
    QDate d = QDate::currentDate();
    if(d == QDate(m_nYear, m_nMonth, d.day()))
    {
        getDayLabel(m_nYear, m_nMonth, d.day())->setColor(CURRENT_DAY);
    }
}

/**
 * @brief CalendarWidget::sltDayClicked 点击响应
 * @param type  类型 0 表示上月 1表示下月
 * @param day  当前点击的天数
 */
void CalendarWidget::sltDayClicked(int type, int day)
{
    // 上月
    if (PREV_MONTH_DAY == type) {
        sltShowPrevMonth();
    }
    // 下月
    else if (NEXT_MONTH_DAY == type) {
        sltShowNextMonth();
    }
    // 当天/周末/当月天数都显示在右边，并转换成农历
    else if ((CURR_MONTH_DAY == type)
             || (WEEKEND_DAY == type)
             || (CURRENT_DAY == type)) {
        // 选中当天
        m_nDay = day;
        emit dayClicked(QDateTime(QDate(m_nYear, m_nMonth, m_nDay), QTime(m_nHour, m_nMin,m_nSec)));
    }

    //  更改当前选中项
    changeCurrentSelectDay();
}

/**
 * @brief CalendarWidget::sltShowPrevMonth 显示上月日期
 */
void CalendarWidget::sltShowPrevMonth()
{
    m_nMonth--;
    if (m_nMonth < 1) {
        m_nMonth = 12;
        m_nYear--;
    }

    setYear(m_nYear);
    setMonth(m_nMonth);
    initDate();
    // 发送更新信号
    emit dayClicked(QDateTime(QDate(m_nYear, m_nMonth, m_nDay), QTime(m_nHour, m_nMin, m_nSec)));
}

/**
 * @brief CalendarWidget::sltShowNextMonth 显示下月日期
 */
void CalendarWidget::sltShowNextMonth()
{
    m_nMonth++;
    if (m_nMonth > 12) {
        m_nMonth = 1;
        m_nYear++;
    }
    setYear(m_nYear);
    setMonth(m_nMonth);
    initDate();
    // 发送更新信号
    emit dayClicked(QDateTime(QDate(m_nYear, m_nMonth, m_nDay), QTime(m_nHour, m_nMin, m_nSec)));
}

void CalendarWidget::sltComboBoxDateChange(int)
{
    if(comboBox_Year->isVisible() || comboBox_Month->isVisible())
    {
        m_nYear = comboBox_Year->currentText().toInt();
        m_nMonth = comboBox_Month->currentIndex() + 1;

        int days = DateCommonInfo::getMonthDays(m_nYear, m_nMonth);
        if(m_nDay > days)
            m_nDay = days;

        initDate();

        //  更新当前选中项
        changeCurrentSelectDay();

        // 发送更新信号
        emit dayClicked(QDateTime(QDate(m_nYear, m_nMonth, m_nDay), QTime(m_nHour, m_nMin, m_nSec)));
    }
}

void CalendarWidget::sltComboBoxTimeChange(int)
{
    if (comboBox_Hour->isVisible() || comboBox_min->isVisible() || comboBox_sec->isVisible())
    {
        m_nHour = comboBox_Hour->currentIndex();
        m_nMin = comboBox_min->currentIndex();
        m_nSec = comboBox_sec->currentIndex();

        emit dayClicked(QDateTime(QDate(m_nYear, m_nMonth, m_nDay), QTime(m_nHour, m_nMin, m_nSec)));
    }
}

void CalendarWidget::slotPushBtnRtn()
{
    jumpToDateTime(QDateTime::currentDateTime());
    emit dayClicked(QDateTime(QDate(m_nYear, m_nMonth, m_nDay), QTime(m_nHour, m_nMin, m_nSec)));
}

void CalendarWidget::slotPushBtnNow()
{
    slotPushBtnRtn();
    close();
}

void CalendarWidget::slotPushBtnOk()
{
    close();
}

//////////////////////////////////////
/// \brief DayLabel::DayLabel
/// \param parent
////////////////////////////////

#include <QMouseEvent>
#include <QEvent>
#include <QPixmap>

DayLabel::DayLabel(QWidget *parent):
    QLabel(parent)
{
    m_bSelect = false;
    m_nDay = 0;
    m_bHover = false;
}

bool DayLabel::getBSelect() const
{
    return m_bSelect;
}

void DayLabel::setSelected(bool value)
{
    m_bSelect = value;
    update();
}

void DayLabel::setColor(int type)
{
    // 设置控件属性类型
    this->setProperty("type", type);

    update();
}

/**
 * @brief DayLabel::showDay
 * @param nDay
 * @param strLunar
 * @param type
 */
void DayLabel::showDay(int nDay, QString strLunar)
{
    m_strText = QString::number(nDay);
    m_nDay = nDay;

#if Has_Lunar    //  显示农历
    if ("" != strLunar) {
        m_strText.append("\n");
        m_strText.append(strLunar);
    }
#endif
}

void DayLabel::enterEvent(QEvent *e)
{
    int nProperty = this->property("type").toInt();
    if (PREV_MONTH_DAY == nProperty || NEXT_MONTH_DAY == nProperty) return;

    m_bHover = true;
    update();

    QLabel::enterEvent(e);
}

void DayLabel::leaveEvent(QEvent *e)
{
    int nProperty = this->property("type").toInt();
    if (PREV_MONTH_DAY == nProperty || NEXT_MONTH_DAY == nProperty) return;

    m_bHover = false;
    update();

    QLabel::leaveEvent(e);
}

void DayLabel::mousePressEvent(QMouseEvent *e)
{
    emit signalClicked(this->property("type").toInt(), m_nDay);

    QLabel::mousePressEvent(e);
}

void DayLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    //    int nProperty = this->property("type").toInt();
    //    if (PREV_MONTH_DAY == nProperty || NEXT_MONTH_DAY == nProperty) return;

    QLabel::mouseDoubleClickEvent(e);
}

void DayLabel::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    //  不是悬停
    if(!m_bHover)
    {
        //  选中
        if(m_bSelect)
        {
            p.setBrush(QBrush(QColor("#117dd9")));
            p.setPen(QPen(QColor("#117dd9"), 1));
#if Has_Lunar    //  显示农历
            p.drawRect(rect());
#else
            p.drawEllipse(rect().center(), 12, 12);
#endif
            p.setPen(QPen(QColor("#ffffff"), 1));
            p.drawText(rect(), Qt::AlignCenter, m_strText);
        }
        else
        {
            int type = this->property("type").toInt();
            //  当前日
            if(CURRENT_DAY == type)
            {
                p.setPen(QPen(QColor("#117dd9"), 1));
#if Has_Lunar    //  显示农历
                p.drawRect(rect());
#else
                p.drawEllipse(rect().center(), 12, 12);
#endif
                p.setPen(QPen(QColor("#cadfff"), 1));
                p.drawText(rect(), Qt::AlignCenter, m_strText);
            }
            // 其他月
            else if ((PREV_MONTH_DAY == type) || (NEXT_MONTH_DAY == type)) {
                p.setPen(QPen(QColor("#2360bc"), 1));
                p.drawText(rect(), Qt::AlignCenter, m_strText);
            }
            // 当前月
            else if (CURR_MONTH_DAY == type) {
                p.setPen(QPen(QColor("#cadfff"), 1));
                p.drawText(rect(), Qt::AlignCenter, m_strText);
            }
            // 周末
            else if (WEEKEND_DAY == type) {
                p.setPen(QPen(QColor("#00caff"), 1));
                p.drawText(rect(), Qt::AlignCenter, m_strText);
            }
        }
    }
    //  悬停的效果
    else
    {
        p.setBrush(QBrush(QColor("#117dd9")));
        p.setPen(QPen(QColor("#117dd9"), 1));
#if Has_Lunar    //  显示农历
        p.drawRect(rect());
#else
        p.drawEllipse(rect().center(), 12, 12);
#endif
        p.setPen(QPen(QColor("#ffffff"), 1));
        p.drawText(rect(), Qt::AlignCenter, m_strText);
    }


    //    QLabel::paintEvent(e);
}
