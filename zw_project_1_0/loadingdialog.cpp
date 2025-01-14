#include "loadingdialog.h"
#include <QDialog>
#include <QFrame>
#include <QLabel>
#include <QMovie>
#include <QGridLayout>
#include <QTimer>
#include <QResizeEvent>
#include <QFile>
#include <QDebug>
#include "logger.h"

LoadingDialog::LoadingDialog(QWidget *parent) : QDialog(parent)
{
    m_pParent = parent;
    //如果需要显示任务栏对话框则删除Qt::Tool
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    init();
}

LoadingDialog::~LoadingDialog()
{
    delete m_lable;
    delete m_movie;
    delete m_centerFrame;
    deleteLater();
}

void LoadingDialog::init()
{
    this->setFixedSize(600, 600);
    this->setAttribute(Qt::WA_TranslucentBackground);// 设置背景透明
    this->setWindowFlags(Qt::FramelessWindowHint); // 设置无边框窗口

    m_centerFrame = new QFrame(this);
    m_centerFrame->setGeometry(10, 10 ,this->width()-10, this->height()-10);
   // m_centerFrame->setAttribute(Qt::WA_TranslucentBackground);// 设置背景透明


    //加载Loading动画
    m_lable = new QLabel(this);
    //m_lable->setAttribute(Qt::WA_TranslucentBackground);
    m_movie = new QMovie(":/Resources/loading.gif");

    if (m_movie->isValid())
    {
        m_movie->setScaledSize(this->size());
        m_lable->setScaledContents(true);
        m_lable->setMovie(m_movie);
        m_movie->start();
    } else
    {
        LOG_INFO("动画加载失败");
        return;
    }


    QGridLayout *gridLayout = new QGridLayout();
    gridLayout->setSpacing(0);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->addWidget(m_lable);
    m_centerFrame->setLayout(gridLayout);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, &QTimer::timeout, this, &LoadingDialog::onTimerTimeout, Qt::UniqueConnection);
    m_pTimer->start(10);
    LOG_INFO("LoadingDialog 初始化完成");



}

void LoadingDialog::move_to_center(QWidget *pParent)
{
    m_pParent = pParent;
    if(pParent != nullptr && pParent != NULL)
    {
        int nParentWidth = pParent->width();
        int nParentHeigth = pParent->height();

        int nWidth = this->width();
        int nHeight = this->height();

        int nParentX = pParent->x();
        int nParentY = pParent->y();

        int x = (nParentX + (nParentWidth - nWidth) / 2);
        int y = (nParentY + (nParentHeigth - nHeight) / 2);

        this->move(x, y);
    }
}

void LoadingDialog::onTimerTimeout()
{
    move_to_center(m_pParent);
}



