#ifndef DATECOMMONINFO_H
#define DATECOMMONINFO_H

#include <QObject>
#include <QPushButton>
#include <QLabel>
#include <QDateTimeEdit>

QT_BEGIN_NAMESPACE
class QPushButton;
class QComboBox;
class QGroupBox;
class QLineEdit;
class QDate;
class QGridLayout;
class QHBoxLayout;
class QVBoxLayout;

class Event;
class DataBase;
QT_END_NAMESPACE

typedef enum {
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    Week
} E_WEEK;

typedef enum {
    PREV_MONTH_DAY,     // 上月剩余天数
    NEXT_MONTH_DAY,     // 下个月的天数
    CURR_MONTH_DAY,     // 当月天数
    WEEKEND_DAY,        // 周末
    SELECT_DAY,         // 选中的天
    CURRENT_DAY,        // 当天
} E_DAY;

#define LC_STR QStringLiteral
class DateCommonInfo : public QObject
{
    Q_OBJECT

public:
    explicit DateCommonInfo(QObject *parent = 0);

signals:

public slots:

public:
    static quint16 getSpringFestivalDate(int year);

    static int getFirstDayOfWeek(int year, int month);
    static int getTotalMonthDays(int year, int month);
    static int getMonthDays(int year, int month);
    static bool isLoopYaer(int year);
    static QString getLunarDate(int year, int month, int day);
    static QString getLunarMonAndDay(int year, int month, int day);
    // 计算今年是什么年如 ：甲子年
    static QString getLunarTime(int year);
private:
    static QString holiday(int month, int day);
    static QString solarTerms(int year, int month, int day);
    static QString lunarFestival(int month, int day);
};

class DayLabel : public QLabel {
    Q_OBJECT

public:
    explicit DayLabel(QWidget *parent = 0);

    bool getBSelect() const;
    void setSelected(bool value);
    void setColor(int type);
    void showDay(int nDay, QString strLunar);

signals:
    void signalClicked(int ntype, int day);

private:
    QLabel *labelIcon;
    int m_nDay;
    bool m_bHover;
    bool m_bSelect;
    QString m_strText;

protected:
    void enterEvent(QEvent *e);
    void leaveEvent(QEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent* e);
};

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QString fromat ,QWidget *parent = 0, Qt::WindowFlags f = Qt::WindowFlags());
    ~CalendarWidget();

    int year() const;
    void setYear(int year);

    int month() const;
    void setMonth(int month);

    int day() const;
    void setDay(int day);

    int hour() const;
    void setHour(int h);

    int minute();
    void setMinute(int m);

    int second();
    void setSecond(int s);

    void jumpToDateTime(const QDateTime& dt);

    void setDateTimeRange(const QDateTime &min, const QDateTime &max);
    void dateTimeRange(QDateTime &min, QDateTime &max);

    void setDisplayFormat(const QString &format);

signals:
    void dayClicked(const QDateTime&);
    void selectDayChanged(const QDateTime&);

private:
    QString m_fromat;

    QVBoxLayout *verLayoutCalendar;
    QWidget *m_base;
    QWidget *widgetTitle;
    QComboBox* comboBox_Year;
    QComboBox* comboBox_Month;

    QWidget *widgetWeek;
    QLabel *labelWeek[Week];
    QHBoxLayout *horLayoutWeek;

    QWidget *widgetBody;
    DayLabel *labelDay[42];
    QGridLayout *gridLayoutBody;

    QWidget *widgetRight;

    QLabel *labelShowToday;
    QLabel *labelShowWeek;
    QLabel *labelShowDay;
    QLabel *labelShowNYear;
    QLabel *labelShowLunarDate;
    QLabel *labelSpacer;
    QLabel *labelScheduleTitle;
    QLabel *labelSchedule;

    QWidget* widget_bottom;
    QComboBox* comboBox_Hour;
    QComboBox* comboBox_min;
    QComboBox* comboBox_sec;
    QLabel* label_splite;
    QLabel* label_splite2;
    QPushButton* pushBtn_Rtn;
    QPushButton* pushBtn_Now;
    QPushButton* pushBtn_Ok;

    QVBoxLayout *verlayoutWidgetRight;

    QHBoxLayout *horLayoutGlobal;

private:
    int m_nYear;
    int m_nMonth;
    int m_nDay;
    int m_nHour;
    int m_nMin;
    int m_nSec;
    QDateTime m_maxDt;
    QDateTime m_minDt;
    DayLabel* m_pCrtSelect;

private:
    void initWidget();
    void initSize();
    void initDate();
    void initStyleSheet();
    void UpdateYear();
    DayLabel* getDayLabel(int y, int m, int d);
    void changeCurrentSelectDay();

protected:
           //virtual void paintEvent(QPaintEvent* e);

private slots:
    void sltDayClicked(int type, int day);
    void sltShowPrevMonth();
    void sltShowNextMonth();
    void sltComboBoxDateChange(int);
    void sltComboBoxTimeChange(int);
    void slotPushBtnRtn();
    void slotPushBtnNow();
    void slotPushBtnOk();
};

#endif // DATE_H
