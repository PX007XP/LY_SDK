#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>
#include <QTimer>
#include <QResizeEvent>


class LoadingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LoadingDialog(QWidget* parent = nullptr);
    ~LoadingDialog();

    void move_to_center(QWidget* pParent);


private:
    void init();

private slots:
    void onTimerTimeout();
    void onFrameChanged(int frame);

private:
    QLabel *m_lable;
    QMovie *m_movie;
    QFrame *m_centerFrame;
    QTimer *m_pTimer;
    QWidget *m_pParent;
};

#endif // LOADINGDIALOG_H
