#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QVBoxLayout>
#include <QTimer>
#include <QResizeEvent>

class LoadingDialog : public QWidget
{
    Q_OBJECT
public:
    explicit LoadingDialog(QWidget *parent = nullptr);
    ~LoadingDialog();


    void startAnimation();

    void stopAnimation();

    void setDuration(int milliseconds);

    void resizeEvent(QResizeEvent *event) override;
signals:

private:
    QLabel *label;
    QMovie *movie;
    QTimer *timer;
};

#endif // LOADINGDIALOG_H
