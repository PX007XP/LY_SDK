#include "loadingdialog.h"

LoadingDialog::LoadingDialog(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    // 创建一个QLabel用于显示GIF动画
    label = new QLabel(this);

    // 创建一个QMovie对象并加载GIF文件
    movie = new QMovie(":/Resources/loading.gif", QByteArray(), this);

    if (!movie->isValid()) {
        qWarning() << "Error loading movie resource.";
    }

    // 设置QLabel的Movie对象并开始播放动画
    label->setMovie(movie);
    movie->start();

    // 设置布局并将QLabel添加到布局中
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label, 0, Qt::AlignCenter);

    // 定义一个定时器用于动画结束后发送结束信号
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &LoadingDialog::stopAnimation);
}

LoadingDialog::~LoadingDialog()
{
    if(label)
    {
        delete label;
    }
    if(movie)
    {
        delete movie;
    }
    if(timer)
    {
        delete timer;
    }
}

void LoadingDialog::startAnimation()
{
    // 重新开始动画，并显示窗口
    movie->start();
    show();
}

void LoadingDialog::stopAnimation()
{
    movie->stop();
    hide();
    timer->stop();

}

void LoadingDialog::setDuration(int milliseconds)
{
    // 设置动画持续时间，如果为0，则表示无限期显示动画
    if (milliseconds > 0) {
        timer->setInterval(milliseconds);
        timer->start();
    } else {
        timer->stop();
    }
}

void LoadingDialog::resizeEvent(QResizeEvent *event)
{
    // 重写调整窗口大小事件，确保GIF始终显示在窗口中央
    QWidget::resizeEvent(event);
    if (label) {
        label->move((width() - label->width()) / 2, (height() - label->height()) / 2);
    }
}
