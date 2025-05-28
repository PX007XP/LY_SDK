#include "zdatetimeedit.h"
#include "QWidgetAction"
#include "dateCommonInfo.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFile>
#include <QMenu>



ZDateTimeEdit::ZDateTimeEdit(QWidget *parent):QDateTimeEdit(parent)
{


    m_popupButton = new QPushButton();
    m_popupButton->setObjectName("popupButton");
    //m_popupButton->setText("+");
    //m_popupButton->setCursor(Qt::ArrowCursor);
    QHBoxLayout *layout = new QHBoxLayout();
    m_popupButton->setCursor(QCursor(Qt::PointingHandCursor));
    m_popupButton->setFont(QFont("Microsoft YaHei"));
    layout->addStretch();
    layout->addWidget(m_popupButton);
    layout->setContentsMargins(0,0,20,0);
    this->setLayout(layout);



    m_pCldrWgt = new CalendarWidget(displayFormat(),this, QMenu().windowFlags() | Qt::FramelessWindowHint);
    m_dateTime = QDateTime::currentDateTime();
    setDateTime(m_dateTime);
    connect(m_popupButton, &QAbstractButton::clicked, this, &ZDateTimeEdit::showCalendarWidget);
    connect(m_pCldrWgt, &CalendarWidget::dayClicked, this, &ZDateTimeEdit::slotDayClicked);
    QFile file(":/zDateTimeEdit.qss");
    if (file.open(QFile::ReadOnly))
    {
        QString qss = file.readAll();
        setStyleSheet(qss);
        file.close();
    }
    QString tmp = displayFormat();
}

ZDateTimeEdit::~ZDateTimeEdit()
{
    if(m_pCldrWgt)
    {
        delete m_pCldrWgt;
    }
}

void ZDateTimeEdit::showCalendarWidget()
{
    QPoint pt(0, height()+5);
    pt = mapToGlobal(pt);

    m_pCldrWgt->jumpToDateTime(m_dateTime);
    m_pCldrWgt->move(pt);
    m_pCldrWgt->show();
}

void ZDateTimeEdit::slotDayClicked(const QDateTime &dt)
{
    m_dateTime = dt;
    setDateTime(dt);
}

void ZDateTimeEdit::setDisplayFormat(const QString &format)
{
    m_pCldrWgt->setDisplayFormat(format);
    QDateTimeEdit::setDisplayFormat(format);
}


