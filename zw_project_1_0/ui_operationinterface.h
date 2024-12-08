/********************************************************************************
** Form generated from reading UI file 'operationinterface.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPERATIONINTERFACE_H
#define UI_OPERATIONINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include "zdatetimeedit.h"

QT_BEGIN_NAMESPACE

class Ui_OperationInterface
{
public:
    QGridLayout *gridLayout_3;
    QLabel *label_9;
    QSplitter *splitter;
    QLabel *label_17;
    QLineEdit *UserEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLineEdit *zhidongganzhi_lineEdit;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_8;
    QLineEdit *saveFilePathEdit;
    QSplitter *splitter_3;
    QPushButton *LoginPushButton;
    QPushButton *SavePasswordPushButton;
    QLabel *label_4;
    QLabel *label_15;
    QLineEdit *MobanlujinEdit;
    QComboBox *TypecomboBox;
    QFrame *line_2;
    ZDateTimeEdit *dateTimeEditEnd;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QSplitter *splitter_2;
    QLabel *label_18;
    QLineEdit *PasswordEdit;
    QGridLayout *gridLayout_2;
    QPushButton *ShowDataButton;
    QPushButton *ComCheckButton;
    QPushButton *WriteFilepushButton;
    QPushButton *ClearDataButton;
    QRadioButton *radioButton;
    QLabel *label_21;
    QTableView *ShowtableView;
    QComboBox *PathcomboBox;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QComboBox *jianceleibie_comboBox;
    QFrame *line_3;
    QLineEdit *lineEdit;
    QLabel *label_14;
    QLabel *label_16;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *caijiTypecomboBox;
    QLabel *label_7;
    QComboBox *sehbeicomboBox;
    QComboBox *FilecomboBox;
    QLabel *label_3;
    QFrame *line;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_11;
    QLineEdit *IpEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_13;
    QLineEdit *PortEdit;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *connectButton;
    QPushButton *GetDataButton;
    QGridLayout *gridLayout;
    QLabel *label_jiancexiangmu;
    QLabel *label_47;
    QLabel *label_30;
    QLabel *label_shenqingdanhao;
    QLabel *label_36;
    QLabel *label_jitai;
    QLabel *label_muxuehao;
    QLabel *label_29;
    QLabel *label_25;
    QLabel *label_20;
    QLabel *label_yangpingshuliang;
    QLineEdit *NumberEdit;
    QLabel *label_32;
    QPushButton *GetInfoButton;
    QLabel *label_shoujianshijian;
    QLabel *label_38;
    QLabel *label_44;
    QLabel *label_gongxu;
    QLabel *label_jianyanleibie;
    QLabel *lable_shenqingrenyuan;
    QLabel *label_23;
    QLabel *label_beizhu;
    QLabel *label_shenqingshijian;
    QLabel *label_songjiandanwei;
    QFrame *line_5;
    QLabel *label_shifoupohuai;
    QLabel *label_jianceyaoqiu;
    QLabel *label_48;
    QLabel *label_xiangmmumingchen;
    QLabel *label_42;
    QLabel *label_26;
    QLabel *label_41;
    QLabel *label_jiajubianhao;
    QLabel *label_35;
    QLabel *label_19;
    ZDateTimeEdit *dateTimeEditStart;

    void setupUi(QWidget *OperationInterface)
    {
        if (OperationInterface->objectName().isEmpty())
            OperationInterface->setObjectName(QString::fromUtf8("OperationInterface"));
        OperationInterface->resize(1108, 720);
        gridLayout_3 = new QGridLayout(OperationInterface);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_9 = new QLabel(OperationInterface);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_3->addWidget(label_9, 8, 6, 1, 1);

        splitter = new QSplitter(OperationInterface);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        label_17 = new QLabel(splitter);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        splitter->addWidget(label_17);
        UserEdit = new QLineEdit(splitter);
        UserEdit->setObjectName(QString::fromUtf8("UserEdit"));
        splitter->addWidget(UserEdit);

        gridLayout_3->addWidget(splitter, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_6 = new QLabel(OperationInterface);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_6->addWidget(label_6);

        zhidongganzhi_lineEdit = new QLineEdit(OperationInterface);
        zhidongganzhi_lineEdit->setObjectName(QString::fromUtf8("zhidongganzhi_lineEdit"));

        horizontalLayout_6->addWidget(zhidongganzhi_lineEdit);


        gridLayout_3->addLayout(horizontalLayout_6, 12, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_8 = new QLabel(OperationInterface);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_7->addWidget(label_8);

        saveFilePathEdit = new QLineEdit(OperationInterface);
        saveFilePathEdit->setObjectName(QString::fromUtf8("saveFilePathEdit"));

        horizontalLayout_7->addWidget(saveFilePathEdit);


        gridLayout_3->addLayout(horizontalLayout_7, 13, 0, 1, 1);

        splitter_3 = new QSplitter(OperationInterface);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        LoginPushButton = new QPushButton(splitter_3);
        LoginPushButton->setObjectName(QString::fromUtf8("LoginPushButton"));
        splitter_3->addWidget(LoginPushButton);
        SavePasswordPushButton = new QPushButton(splitter_3);
        SavePasswordPushButton->setObjectName(QString::fromUtf8("SavePasswordPushButton"));
        splitter_3->addWidget(SavePasswordPushButton);

        gridLayout_3->addWidget(splitter_3, 0, 2, 1, 1);

        label_4 = new QLabel(OperationInterface);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 0, 4, 1, 1);

        label_15 = new QLabel(OperationInterface);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_3->addWidget(label_15, 6, 4, 1, 1);

        MobanlujinEdit = new QLineEdit(OperationInterface);
        MobanlujinEdit->setObjectName(QString::fromUtf8("MobanlujinEdit"));

        gridLayout_3->addWidget(MobanlujinEdit, 0, 5, 1, 1);

        TypecomboBox = new QComboBox(OperationInterface);
        TypecomboBox->setObjectName(QString::fromUtf8("TypecomboBox"));

        gridLayout_3->addWidget(TypecomboBox, 2, 5, 1, 1);

        line_2 = new QFrame(OperationInterface);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_2, 0, 3, 9, 1);

        dateTimeEditEnd = new ZDateTimeEdit(OperationInterface);
        dateTimeEditEnd->setObjectName(QString::fromUtf8("dateTimeEditEnd"));
        dateTimeEditEnd->setCalendarPopup(false);

        gridLayout_3->addWidget(dateTimeEditEnd, 5, 5, 1, 1);

        lineEdit_2 = new QLineEdit(OperationInterface);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout_3->addWidget(lineEdit_2, 7, 5, 1, 1);

        label = new QLabel(OperationInterface);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 1, 4, 1, 1);

        splitter_2 = new QSplitter(OperationInterface);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        label_18 = new QLabel(splitter_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        splitter_2->addWidget(label_18);
        PasswordEdit = new QLineEdit(splitter_2);
        PasswordEdit->setObjectName(QString::fromUtf8("PasswordEdit"));
        PasswordEdit->setEnabled(true);
        PasswordEdit->setEchoMode(QLineEdit::Normal);
        splitter_2->addWidget(PasswordEdit);

        gridLayout_3->addWidget(splitter_2, 0, 1, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        ShowDataButton = new QPushButton(OperationInterface);
        ShowDataButton->setObjectName(QString::fromUtf8("ShowDataButton"));

        gridLayout_2->addWidget(ShowDataButton, 2, 0, 1, 1);

        ComCheckButton = new QPushButton(OperationInterface);
        ComCheckButton->setObjectName(QString::fromUtf8("ComCheckButton"));

        gridLayout_2->addWidget(ComCheckButton, 2, 2, 1, 1);

        WriteFilepushButton = new QPushButton(OperationInterface);
        WriteFilepushButton->setObjectName(QString::fromUtf8("WriteFilepushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(WriteFilepushButton->sizePolicy().hasHeightForWidth());
        WriteFilepushButton->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(WriteFilepushButton, 2, 1, 1, 1);

        ClearDataButton = new QPushButton(OperationInterface);
        ClearDataButton->setObjectName(QString::fromUtf8("ClearDataButton"));

        gridLayout_2->addWidget(ClearDataButton, 0, 2, 1, 1);

        radioButton = new QRadioButton(OperationInterface);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        gridLayout_2->addWidget(radioButton, 0, 0, 1, 1);

        label_21 = new QLabel(OperationInterface);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setAcceptDrops(false);
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_21, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 11, 2, 2, 1);

        ShowtableView = new QTableView(OperationInterface);
        ShowtableView->setObjectName(QString::fromUtf8("ShowtableView"));

        gridLayout_3->addWidget(ShowtableView, 15, 0, 1, 7);

        PathcomboBox = new QComboBox(OperationInterface);
        PathcomboBox->setObjectName(QString::fromUtf8("PathcomboBox"));
        sizePolicy1.setHeightForWidth(PathcomboBox->sizePolicy().hasHeightForWidth());
        PathcomboBox->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(PathcomboBox, 1, 5, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_10 = new QLabel(OperationInterface);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_8->addWidget(label_10);

        jianceleibie_comboBox = new QComboBox(OperationInterface);
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->addItem(QString());
        jianceleibie_comboBox->setObjectName(QString::fromUtf8("jianceleibie_comboBox"));

        horizontalLayout_8->addWidget(jianceleibie_comboBox);


        gridLayout_3->addLayout(horizontalLayout_8, 13, 1, 1, 1);

        line_3 = new QFrame(OperationInterface);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line_3, 9, 0, 1, 4);

        lineEdit = new QLineEdit(OperationInterface);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout_3->addWidget(lineEdit, 6, 5, 1, 1);

        label_14 = new QLabel(OperationInterface);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_3->addWidget(label_14, 5, 4, 1, 1);

        label_16 = new QLabel(OperationInterface);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_3->addWidget(label_16, 7, 4, 1, 1);

        label_2 = new QLabel(OperationInterface);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 2, 4, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_5 = new QLabel(OperationInterface);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_5->addWidget(label_5);

        caijiTypecomboBox = new QComboBox(OperationInterface);
        caijiTypecomboBox->addItem(QString());
        caijiTypecomboBox->addItem(QString());
        caijiTypecomboBox->setObjectName(QString::fromUtf8("caijiTypecomboBox"));

        horizontalLayout_5->addWidget(caijiTypecomboBox);

        label_7 = new QLabel(OperationInterface);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        sehbeicomboBox = new QComboBox(OperationInterface);
        sehbeicomboBox->addItem(QString());
        sehbeicomboBox->addItem(QString());
        sehbeicomboBox->setObjectName(QString::fromUtf8("sehbeicomboBox"));

        horizontalLayout_5->addWidget(sehbeicomboBox);


        gridLayout_3->addLayout(horizontalLayout_5, 11, 0, 1, 1);

        FilecomboBox = new QComboBox(OperationInterface);
        FilecomboBox->setObjectName(QString::fromUtf8("FilecomboBox"));

        gridLayout_3->addWidget(FilecomboBox, 3, 5, 1, 1);

        label_3 = new QLabel(OperationInterface);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 3, 4, 1, 1);

        line = new QFrame(OperationInterface);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_3->addWidget(line, 14, 0, 1, 7);

        label_12 = new QLabel(OperationInterface);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_3->addWidget(label_12, 4, 4, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_11 = new QLabel(OperationInterface);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout->addWidget(label_11);

        IpEdit = new QLineEdit(OperationInterface);
        IpEdit->setObjectName(QString::fromUtf8("IpEdit"));

        horizontalLayout->addWidget(IpEdit);


        horizontalLayout_4->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_13 = new QLabel(OperationInterface);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_2->addWidget(label_13);

        PortEdit = new QLineEdit(OperationInterface);
        PortEdit->setObjectName(QString::fromUtf8("PortEdit"));

        horizontalLayout_2->addWidget(PortEdit);


        horizontalLayout_4->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        connectButton = new QPushButton(OperationInterface);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout_3->addWidget(connectButton);

        GetDataButton = new QPushButton(OperationInterface);
        GetDataButton->setObjectName(QString::fromUtf8("GetDataButton"));

        horizontalLayout_3->addWidget(GetDataButton);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        gridLayout_3->addLayout(horizontalLayout_4, 10, 0, 1, 2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_jiancexiangmu = new QLabel(OperationInterface);
        label_jiancexiangmu->setObjectName(QString::fromUtf8("label_jiancexiangmu"));

        gridLayout->addWidget(label_jiancexiangmu, 5, 7, 1, 1);

        label_47 = new QLabel(OperationInterface);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout->addWidget(label_47, 6, 6, 1, 1);

        label_30 = new QLabel(OperationInterface);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout->addWidget(label_30, 3, 0, 1, 1);

        label_shenqingdanhao = new QLabel(OperationInterface);
        label_shenqingdanhao->setObjectName(QString::fromUtf8("label_shenqingdanhao"));

        gridLayout->addWidget(label_shenqingdanhao, 2, 1, 1, 2);

        label_36 = new QLabel(OperationInterface);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout->addWidget(label_36, 4, 0, 1, 1);

        label_jitai = new QLabel(OperationInterface);
        label_jitai->setObjectName(QString::fromUtf8("label_jitai"));

        gridLayout->addWidget(label_jitai, 3, 4, 1, 2);

        label_muxuehao = new QLabel(OperationInterface);
        label_muxuehao->setObjectName(QString::fromUtf8("label_muxuehao"));

        gridLayout->addWidget(label_muxuehao, 6, 7, 1, 1);

        label_29 = new QLabel(OperationInterface);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout->addWidget(label_29, 3, 6, 1, 1);

        label_25 = new QLabel(OperationInterface);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout->addWidget(label_25, 2, 6, 1, 1);

        label_20 = new QLabel(OperationInterface);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout->addWidget(label_20, 2, 0, 1, 1);

        label_yangpingshuliang = new QLabel(OperationInterface);
        label_yangpingshuliang->setObjectName(QString::fromUtf8("label_yangpingshuliang"));

        gridLayout->addWidget(label_yangpingshuliang, 4, 4, 1, 2);

        NumberEdit = new QLineEdit(OperationInterface);
        NumberEdit->setObjectName(QString::fromUtf8("NumberEdit"));

        gridLayout->addWidget(NumberEdit, 1, 1, 1, 2);

        label_32 = new QLabel(OperationInterface);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout->addWidget(label_32, 4, 3, 1, 1);

        GetInfoButton = new QPushButton(OperationInterface);
        GetInfoButton->setObjectName(QString::fromUtf8("GetInfoButton"));

        gridLayout->addWidget(GetInfoButton, 1, 3, 1, 1);

        label_shoujianshijian = new QLabel(OperationInterface);
        label_shoujianshijian->setObjectName(QString::fromUtf8("label_shoujianshijian"));

        gridLayout->addWidget(label_shoujianshijian, 4, 7, 1, 1);

        label_38 = new QLabel(OperationInterface);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        gridLayout->addWidget(label_38, 5, 3, 1, 1);

        label_44 = new QLabel(OperationInterface);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout->addWidget(label_44, 6, 3, 1, 1);

        label_gongxu = new QLabel(OperationInterface);
        label_gongxu->setObjectName(QString::fromUtf8("label_gongxu"));

        gridLayout->addWidget(label_gongxu, 6, 1, 1, 2);

        label_jianyanleibie = new QLabel(OperationInterface);
        label_jianyanleibie->setObjectName(QString::fromUtf8("label_jianyanleibie"));

        gridLayout->addWidget(label_jianyanleibie, 5, 1, 1, 2);

        lable_shenqingrenyuan = new QLabel(OperationInterface);
        lable_shenqingrenyuan->setObjectName(QString::fromUtf8("lable_shenqingrenyuan"));

        gridLayout->addWidget(lable_shenqingrenyuan, 2, 4, 1, 2);

        label_23 = new QLabel(OperationInterface);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout->addWidget(label_23, 2, 3, 1, 1);

        label_beizhu = new QLabel(OperationInterface);
        label_beizhu->setObjectName(QString::fromUtf8("label_beizhu"));

        gridLayout->addWidget(label_beizhu, 7, 0, 1, 1);

        label_shenqingshijian = new QLabel(OperationInterface);
        label_shenqingshijian->setObjectName(QString::fromUtf8("label_shenqingshijian"));

        gridLayout->addWidget(label_shenqingshijian, 3, 7, 1, 1);

        label_songjiandanwei = new QLabel(OperationInterface);
        label_songjiandanwei->setObjectName(QString::fromUtf8("label_songjiandanwei"));

        gridLayout->addWidget(label_songjiandanwei, 2, 7, 1, 1);

        line_5 = new QFrame(OperationInterface);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_5, 0, 0, 1, 8);

        label_shifoupohuai = new QLabel(OperationInterface);
        label_shifoupohuai->setObjectName(QString::fromUtf8("label_shifoupohuai"));

        gridLayout->addWidget(label_shifoupohuai, 5, 4, 1, 2);

        label_jianceyaoqiu = new QLabel(OperationInterface);
        label_jianceyaoqiu->setObjectName(QString::fromUtf8("label_jianceyaoqiu"));

        gridLayout->addWidget(label_jianceyaoqiu, 4, 1, 1, 2);

        label_48 = new QLabel(OperationInterface);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout->addWidget(label_48, 6, 0, 1, 1);

        label_xiangmmumingchen = new QLabel(OperationInterface);
        label_xiangmmumingchen->setObjectName(QString::fromUtf8("label_xiangmmumingchen"));

        gridLayout->addWidget(label_xiangmmumingchen, 3, 1, 1, 2);

        label_42 = new QLabel(OperationInterface);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout->addWidget(label_42, 5, 0, 1, 1);

        label_26 = new QLabel(OperationInterface);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout->addWidget(label_26, 3, 3, 1, 1);

        label_41 = new QLabel(OperationInterface);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout->addWidget(label_41, 5, 6, 1, 1);

        label_jiajubianhao = new QLabel(OperationInterface);
        label_jiajubianhao->setObjectName(QString::fromUtf8("label_jiajubianhao"));

        gridLayout->addWidget(label_jiajubianhao, 6, 4, 1, 2);

        label_35 = new QLabel(OperationInterface);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout->addWidget(label_35, 4, 6, 1, 1);

        label_19 = new QLabel(OperationInterface);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout->addWidget(label_19, 1, 0, 1, 1);


        gridLayout_3->addLayout(gridLayout, 2, 0, 6, 3);

        dateTimeEditStart = new ZDateTimeEdit(OperationInterface);
        dateTimeEditStart->setObjectName(QString::fromUtf8("dateTimeEditStart"));
        dateTimeEditStart->setWrapping(false);
        dateTimeEditStart->setAccelerated(false);
        dateTimeEditStart->setKeyboardTracking(true);
        dateTimeEditStart->setMaximumDateTime(QDateTime(QDate(9999, 12, 31), QTime(23, 59, 59)));
        dateTimeEditStart->setCalendarPopup(false);
        dateTimeEditStart->setCurrentSectionIndex(0);

        gridLayout_3->addWidget(dateTimeEditStart, 4, 5, 1, 1);


        retranslateUi(OperationInterface);

        TypecomboBox->setCurrentIndex(-1);
        PathcomboBox->setCurrentIndex(-1);
        jianceleibie_comboBox->setCurrentIndex(0);
        caijiTypecomboBox->setCurrentIndex(0);
        sehbeicomboBox->setCurrentIndex(0);
        FilecomboBox->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(OperationInterface);
    } // setupUi

    void retranslateUi(QWidget *OperationInterface)
    {
        OperationInterface->setWindowTitle(QCoreApplication::translate("OperationInterface", "OperationInterface", nullptr));
        label_9->setText(QString());
        label_17->setText(QCoreApplication::translate("OperationInterface", "\345\267\245\345\217\267\357\274\232", nullptr));
        UserEdit->setText(QCoreApplication::translate("OperationInterface", "10030534", nullptr));
        label_6->setText(QCoreApplication::translate("OperationInterface", "\350\207\252\345\212\250\346\204\237\347\237\245\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("OperationInterface", "\346\226\207\344\273\266\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", nullptr));
        LoginPushButton->setText(QCoreApplication::translate("OperationInterface", "\347\231\273\345\275\225", nullptr));
        SavePasswordPushButton->setText(QCoreApplication::translate("OperationInterface", "\350\256\276\347\275\256", nullptr));
        label_4->setText(QCoreApplication::translate("OperationInterface", "\351\241\271\347\233\256\350\267\257\345\276\204:", nullptr));
        label_15->setText(QCoreApplication::translate("OperationInterface", "\346\265\213\351\207\217\344\272\272\345\221\230", nullptr));
        MobanlujinEdit->setText(QCoreApplication::translate("OperationInterface", "D:\\", nullptr));
        dateTimeEditEnd->setDisplayFormat(QCoreApplication::translate("OperationInterface", "yyyy-M-d H:mm", nullptr));
        label->setText(QCoreApplication::translate("OperationInterface", "\351\241\271\347\233\256\345\220\215\347\247\260:", nullptr));
        label_18->setText(QCoreApplication::translate("OperationInterface", "\345\257\206\347\240\201\357\274\232", nullptr));
        PasswordEdit->setText(QCoreApplication::translate("OperationInterface", "Qwer.12345", nullptr));
        ShowDataButton->setText(QCoreApplication::translate("OperationInterface", "\344\277\241\346\201\257\346\230\276\347\244\272", nullptr));
        ComCheckButton->setText(QCoreApplication::translate("OperationInterface", "\345\256\214\346\210\220\346\243\200\346\265\213", nullptr));
        WriteFilepushButton->setText(QCoreApplication::translate("OperationInterface", "\344\270\212\344\274\240\346\225\260\346\215\256", nullptr));
        ClearDataButton->setText(QCoreApplication::translate("OperationInterface", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
        radioButton->setText(QCoreApplication::translate("OperationInterface", "\344\277\256\346\224\271\346\225\260\346\215\256", nullptr));
        label_21->setText(QCoreApplication::translate("OperationInterface", "OK", nullptr));
        label_10->setText(QCoreApplication::translate("OperationInterface", "\346\243\200\346\237\245\347\261\273\345\210\253\357\274\232", nullptr));
        jianceleibie_comboBox->setItemText(0, QCoreApplication::translate("OperationInterface", "FAI", nullptr));
        jianceleibie_comboBox->setItemText(1, QCoreApplication::translate("OperationInterface", "CIK", nullptr));
        jianceleibie_comboBox->setItemText(2, QCoreApplication::translate("OperationInterface", "\351\246\226\344\273\266", nullptr));
        jianceleibie_comboBox->setItemText(3, QCoreApplication::translate("OperationInterface", "\345\267\241\344\273\2661", nullptr));
        jianceleibie_comboBox->setItemText(4, QCoreApplication::translate("OperationInterface", "\345\267\241\344\273\2662", nullptr));
        jianceleibie_comboBox->setItemText(5, QCoreApplication::translate("OperationInterface", "\345\267\241\344\273\2663", nullptr));
        jianceleibie_comboBox->setItemText(6, QCoreApplication::translate("OperationInterface", "\345\260\276\344\273\266", nullptr));
        jianceleibie_comboBox->setItemText(7, QCoreApplication::translate("OperationInterface", "\346\235\245\346\226\231", nullptr));
        jianceleibie_comboBox->setItemText(8, QCoreApplication::translate("OperationInterface", "CR&R", nullptr));
        jianceleibie_comboBox->setItemText(9, QCoreApplication::translate("OperationInterface", "\345\207\272\350\264\247", nullptr));
        jianceleibie_comboBox->setItemText(10, QCoreApplication::translate("OperationInterface", "\350\260\203\346\234\272", nullptr));
        jianceleibie_comboBox->setItemText(11, QCoreApplication::translate("OperationInterface", "\346\214\207\345\256\232\345\260\272\345\257\270", nullptr));
        jianceleibie_comboBox->setItemText(12, QCoreApplication::translate("OperationInterface", "\350\260\203\346\234\272\345\244\215\346\265\213", nullptr));
        jianceleibie_comboBox->setItemText(13, QCoreApplication::translate("OperationInterface", "\346\236\266\346\234\272\351\246\226\344\273\266", nullptr));
        jianceleibie_comboBox->setItemText(14, QCoreApplication::translate("OperationInterface", "\346\215\242\345\210\200\351\246\226\344\273\266", nullptr));
        jianceleibie_comboBox->setItemText(15, QCoreApplication::translate("OperationInterface", "FAI+CPK", nullptr));
        jianceleibie_comboBox->setItemText(16, QCoreApplication::translate("OperationInterface", "\345\210\200\345\205\267\345\260\272\345\257\270", nullptr));

        label_14->setText(QCoreApplication::translate("OperationInterface", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        label_16->setText(QCoreApplication::translate("OperationInterface", "\345\256\241\346\240\270\344\272\272\345\221\230", nullptr));
        label_2->setText(QCoreApplication::translate("OperationInterface", "\346\235\220\346\226\231\345\220\215\347\247\260\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("OperationInterface", "\351\207\207\351\233\206\346\226\271\345\274\217\357\274\232", nullptr));
        caijiTypecomboBox->setItemText(0, QCoreApplication::translate("OperationInterface", "\346\225\260\346\215\256\345\257\271\346\216\245", nullptr));
        caijiTypecomboBox->setItemText(1, QCoreApplication::translate("OperationInterface", "\350\207\252\345\212\250\346\204\237\347\237\245", nullptr));

        label_7->setText(QCoreApplication::translate("OperationInterface", "\350\256\276\345\244\207\345\223\201\347\211\214\357\274\232", nullptr));
        sehbeicomboBox->setItemText(0, QCoreApplication::translate("OperationInterface", "\345\205\206\344\270\2601", nullptr));
        sehbeicomboBox->setItemText(1, QCoreApplication::translate("OperationInterface", "\345\205\206\344\270\2602", nullptr));

        label_3->setText(QCoreApplication::translate("OperationInterface", "\346\212\245\345\221\212\351\200\211\346\213\251:", nullptr));
        label_12->setText(QCoreApplication::translate("OperationInterface", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label_11->setText(QCoreApplication::translate("OperationInterface", "iP\357\274\232", nullptr));
        IpEdit->setText(QCoreApplication::translate("OperationInterface", "192.168.31.145", nullptr));
        label_13->setText(QCoreApplication::translate("OperationInterface", "\347\253\257\345\217\243\357\274\232", nullptr));
        PortEdit->setText(QCoreApplication::translate("OperationInterface", "8889", nullptr));
        connectButton->setText(QCoreApplication::translate("OperationInterface", "\345\273\272\347\253\213\351\223\276\346\216\245", nullptr));
        GetDataButton->setText(QCoreApplication::translate("OperationInterface", "\350\216\267\345\217\226\346\225\260\346\215\256", nullptr));
        label_jiancexiangmu->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_47->setText(QCoreApplication::translate("OperationInterface", "\346\250\241\347\251\264\345\217\267:", nullptr));
        label_30->setText(QCoreApplication::translate("OperationInterface", "\351\241\271\347\233\256\345\220\215\347\247\260\357\274\232", nullptr));
        label_shenqingdanhao->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_36->setText(QCoreApplication::translate("OperationInterface", "\346\243\200\346\265\213\350\246\201\346\261\202\357\274\232", nullptr));
        label_jitai->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_muxuehao->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_29->setText(QCoreApplication::translate("OperationInterface", "\347\224\263\350\257\267\346\227\266\351\227\264:", nullptr));
        label_25->setText(QCoreApplication::translate("OperationInterface", "\351\200\201\346\243\200\345\215\225\344\275\215:", nullptr));
        label_20->setText(QCoreApplication::translate("OperationInterface", "\347\224\263\350\257\267\345\215\225\345\217\267\357\274\232", nullptr));
        label_yangpingshuliang->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        NumberEdit->setText(QCoreApplication::translate("OperationInterface", "mmsdCY12410231B2", nullptr));
        label_32->setText(QCoreApplication::translate("OperationInterface", "\346\240\267\345\223\201\346\225\260\351\207\217\357\274\232", nullptr));
        GetInfoButton->setText(QCoreApplication::translate("OperationInterface", "\346\237\245\350\257\242", nullptr));
        label_shoujianshijian->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_38->setText(QCoreApplication::translate("OperationInterface", "\346\230\257\345\220\246\347\240\264\345\235\217\357\274\232", nullptr));
        label_44->setText(QCoreApplication::translate("OperationInterface", "\345\244\271\345\205\267\347\274\226\345\217\267\357\274\232", nullptr));
        label_gongxu->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_jianyanleibie->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        lable_shenqingrenyuan->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_23->setText(QCoreApplication::translate("OperationInterface", "\347\224\263\350\257\267\344\272\272\345\221\230\357\274\232", nullptr));
        label_beizhu->setText(QCoreApplication::translate("OperationInterface", "\345\244\207\346\263\250\357\274\232", nullptr));
        label_shenqingshijian->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_songjiandanwei->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_shifoupohuai->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_jianceyaoqiu->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_48->setText(QCoreApplication::translate("OperationInterface", "\345\267\245\345\272\217\357\274\232", nullptr));
        label_xiangmmumingchen->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_42->setText(QCoreApplication::translate("OperationInterface", "\346\243\200\351\252\214\347\261\273\345\210\253\357\274\232", nullptr));
        label_26->setText(QCoreApplication::translate("OperationInterface", "\346\234\272\345\217\260\357\274\232", nullptr));
        label_41->setText(QCoreApplication::translate("OperationInterface", "\346\243\200\346\265\213\351\241\271\347\233\256:", nullptr));
        label_jiajubianhao->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_35->setText(QCoreApplication::translate("OperationInterface", "\346\224\266\344\273\266\346\227\266\351\227\264:", nullptr));
        label_19->setText(QCoreApplication::translate("OperationInterface", "mm\345\255\220\345\215\225\345\217\267\357\274\232", nullptr));
        dateTimeEditStart->setDisplayFormat(QCoreApplication::translate("OperationInterface", "yyyy-M-d H:mm", nullptr));
    } // retranslateUi

};

namespace Ui {
    class OperationInterface: public Ui_OperationInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATIONINTERFACE_H
