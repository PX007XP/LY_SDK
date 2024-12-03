#ifndef ZDATETIMEEDIT_H
#define ZDATETIMEEDIT_H

#include <QWidget>
#include <QDateTimeEdit>
#include <QPushButton>
#include <QLabel>

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





class DayLabel;
class CalendarWidget;

class ZDateTimeEdit : public QDateTimeEdit
{
    Q_OBJECT
public:
    explicit ZDateTimeEdit(QWidget *parent = 0);
    ~ZDateTimeEdit();


    void setDisplayFormat(const QString &format);


private:
    QPushButton *m_popupButton=nullptr;
    CalendarWidget* m_pCldrWgt;
    QDateTime m_dateTime;
    QString m_strFormat;

public slots:
    void showCalendarWidget();

protected slots:
    void slotDayClicked(const QDateTime & dt);
};






#endif // ZDATETIMEEDIT_H
