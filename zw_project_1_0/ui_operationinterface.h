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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "zdatetimeedit.h"

QT_BEGIN_NAMESPACE

class Ui_OperationInterface
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_4;
    QSplitter *splitter;
    QLabel *label_17;
    QLineEdit *UserEdit;
    QSplitter *splitter_2;
    QLabel *label_18;
    QLineEdit *PasswordEdit;
    QSplitter *splitter_3;
    QPushButton *LoginPushButton;
    QHBoxLayout *horizontalLayout_5;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QPushButton *GetInfoButton;
    QLabel *label_jitai;
    QLabel *label_beizhu;
    QLabel *label_38;
    QLabel *label_jianyanleibie;
    QLabel *label_25;
    QLabel *label_gongxu;
    QLabel *label_23;
    QLabel *label_songjiandanwei;
    QLabel *label_41;
    QLabel *label_shifoupohuai;
    QLabel *label_jiajubianhao;
    QLabel *label_44;
    QLabel *label_42;
    QLabel *label_muxuehao;
    QLabel *label_jiancexiangmu;
    QLabel *label_xiangmmumingchen;
    QLabel *label_29;
    QLabel *label_32;
    QLabel *label_shoujianshijian;
    QLabel *label_20;
    QLabel *label_35;
    QLabel *label_47;
    QLabel *label_shenqingshijian;
    QLabel *label_yangpingshuliang;
    QLabel *label_30;
    QLabel *label_jianceyaoqiu;
    QLineEdit *NumberEdit;
    QLabel *label_36;
    QLabel *label_48;
    QLabel *lable_shenqingrenyuan;
    QLabel *label_26;
    QLabel *label_shenqingdanhao;
    QLabel *label_19;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *connectButton;
    QPushButton *GetDataButton;
    QRadioButton *radioButton;
    QLabel *label_6;
    QLabel *label_5;
    QComboBox *sehbeicomboBox;
    QComboBox *caijiTypecomboBox;
    QLabel *label_8;
    QPushButton *WriteFilepushButton;
    QPushButton *ShowDataButton;
    QLabel *label_21;
    QHBoxLayout *horizontalLayout;
    QLabel *label_11;
    QLineEdit *IpEdit;
    QPushButton *ComCheckButton;
    QLabel *label_7;
    QLineEdit *lineEdit_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_13;
    QLineEdit *PortEdit;
    QPushButton *ClearDataButton;
    QLineEdit *saveFilePathEdit;
    QPushButton *DownLoadFileButton;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_2;
    QLabel *label_16;
    QLineEdit *shenherenyuan_lineEdit;
    QComboBox *FilecomboBox;
    QLabel *label_12;
    QComboBox *PathcomboBox;
    QLabel *label_14;
    ZDateTimeEdit *dateTimeEditEnd;
    QLabel *label_15;
    QLineEdit *MobanlujinEdit;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_3;
    QComboBox *TypecomboBox;
    ZDateTimeEdit *dateTimeEditStart;
    QLineEdit *celiangrenyuan_lineEdit;
    QLabel *label_10;
    QComboBox *jianceleibie_comboBox;
    QTableView *ShowtableView;

    void setupUi(QWidget *OperationInterface)
    {
        if (OperationInterface->objectName().isEmpty())
            OperationInterface->setObjectName(QString::fromUtf8("OperationInterface"));
        OperationInterface->resize(1399, 720);
        layoutWidget = new QWidget(OperationInterface);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(12, -17, 1236, 584));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_3 = new QGroupBox(layoutWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_3);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        splitter = new QSplitter(groupBox_3);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        label_17 = new QLabel(splitter);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        splitter->addWidget(label_17);
        UserEdit = new QLineEdit(splitter);
        UserEdit->setObjectName(QString::fromUtf8("UserEdit"));
        splitter->addWidget(UserEdit);

        horizontalLayout_4->addWidget(splitter);

        splitter_2 = new QSplitter(groupBox_3);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        label_18 = new QLabel(splitter_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        splitter_2->addWidget(label_18);
        PasswordEdit = new QLineEdit(splitter_2);
        PasswordEdit->setObjectName(QString::fromUtf8("PasswordEdit"));
        PasswordEdit->setEnabled(true);
        PasswordEdit->setEchoMode(QLineEdit::Password);
        splitter_2->addWidget(PasswordEdit);

        horizontalLayout_4->addWidget(splitter_2);

        splitter_3 = new QSplitter(groupBox_3);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        splitter_3->setOrientation(Qt::Horizontal);
        LoginPushButton = new QPushButton(splitter_3);
        LoginPushButton->setObjectName(QString::fromUtf8("LoginPushButton"));
        splitter_3->addWidget(LoginPushButton);

        horizontalLayout_4->addWidget(splitter_3);


        verticalLayout->addWidget(groupBox_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        GetInfoButton = new QPushButton(groupBox);
        GetInfoButton->setObjectName(QString::fromUtf8("GetInfoButton"));

        gridLayout_5->addWidget(GetInfoButton, 0, 2, 1, 1);

        label_jitai = new QLabel(groupBox);
        label_jitai->setObjectName(QString::fromUtf8("label_jitai"));

        gridLayout_5->addWidget(label_jitai, 2, 3, 1, 1);

        label_beizhu = new QLabel(groupBox);
        label_beizhu->setObjectName(QString::fromUtf8("label_beizhu"));

        gridLayout_5->addWidget(label_beizhu, 6, 0, 1, 1);

        label_38 = new QLabel(groupBox);
        label_38->setObjectName(QString::fromUtf8("label_38"));

        gridLayout_5->addWidget(label_38, 4, 2, 1, 1);

        label_jianyanleibie = new QLabel(groupBox);
        label_jianyanleibie->setObjectName(QString::fromUtf8("label_jianyanleibie"));

        gridLayout_5->addWidget(label_jianyanleibie, 4, 1, 1, 1);

        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        gridLayout_5->addWidget(label_25, 1, 5, 1, 1);

        label_gongxu = new QLabel(groupBox);
        label_gongxu->setObjectName(QString::fromUtf8("label_gongxu"));

        gridLayout_5->addWidget(label_gongxu, 5, 1, 1, 1);

        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_5->addWidget(label_23, 1, 2, 1, 1);

        label_songjiandanwei = new QLabel(groupBox);
        label_songjiandanwei->setObjectName(QString::fromUtf8("label_songjiandanwei"));

        gridLayout_5->addWidget(label_songjiandanwei, 1, 6, 1, 1);

        label_41 = new QLabel(groupBox);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout_5->addWidget(label_41, 4, 5, 1, 1);

        label_shifoupohuai = new QLabel(groupBox);
        label_shifoupohuai->setObjectName(QString::fromUtf8("label_shifoupohuai"));

        gridLayout_5->addWidget(label_shifoupohuai, 4, 3, 1, 1);

        label_jiajubianhao = new QLabel(groupBox);
        label_jiajubianhao->setObjectName(QString::fromUtf8("label_jiajubianhao"));

        gridLayout_5->addWidget(label_jiajubianhao, 5, 3, 1, 1);

        label_44 = new QLabel(groupBox);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout_5->addWidget(label_44, 5, 2, 1, 1);

        label_42 = new QLabel(groupBox);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout_5->addWidget(label_42, 4, 0, 1, 1);

        label_muxuehao = new QLabel(groupBox);
        label_muxuehao->setObjectName(QString::fromUtf8("label_muxuehao"));

        gridLayout_5->addWidget(label_muxuehao, 5, 6, 1, 1);

        label_jiancexiangmu = new QLabel(groupBox);
        label_jiancexiangmu->setObjectName(QString::fromUtf8("label_jiancexiangmu"));

        gridLayout_5->addWidget(label_jiancexiangmu, 4, 6, 1, 1);

        label_xiangmmumingchen = new QLabel(groupBox);
        label_xiangmmumingchen->setObjectName(QString::fromUtf8("label_xiangmmumingchen"));

        gridLayout_5->addWidget(label_xiangmmumingchen, 2, 1, 1, 1);

        label_29 = new QLabel(groupBox);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout_5->addWidget(label_29, 2, 5, 1, 1);

        label_32 = new QLabel(groupBox);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout_5->addWidget(label_32, 3, 2, 1, 1);

        label_shoujianshijian = new QLabel(groupBox);
        label_shoujianshijian->setObjectName(QString::fromUtf8("label_shoujianshijian"));

        gridLayout_5->addWidget(label_shoujianshijian, 3, 6, 1, 1);

        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));

        gridLayout_5->addWidget(label_20, 1, 0, 1, 1);

        label_35 = new QLabel(groupBox);
        label_35->setObjectName(QString::fromUtf8("label_35"));

        gridLayout_5->addWidget(label_35, 3, 5, 1, 1);

        label_47 = new QLabel(groupBox);
        label_47->setObjectName(QString::fromUtf8("label_47"));

        gridLayout_5->addWidget(label_47, 5, 5, 1, 1);

        label_shenqingshijian = new QLabel(groupBox);
        label_shenqingshijian->setObjectName(QString::fromUtf8("label_shenqingshijian"));

        gridLayout_5->addWidget(label_shenqingshijian, 2, 6, 1, 1);

        label_yangpingshuliang = new QLabel(groupBox);
        label_yangpingshuliang->setObjectName(QString::fromUtf8("label_yangpingshuliang"));

        gridLayout_5->addWidget(label_yangpingshuliang, 3, 3, 1, 1);

        label_30 = new QLabel(groupBox);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_5->addWidget(label_30, 2, 0, 1, 1);

        label_jianceyaoqiu = new QLabel(groupBox);
        label_jianceyaoqiu->setObjectName(QString::fromUtf8("label_jianceyaoqiu"));

        gridLayout_5->addWidget(label_jianceyaoqiu, 3, 1, 1, 1);

        NumberEdit = new QLineEdit(groupBox);
        NumberEdit->setObjectName(QString::fromUtf8("NumberEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NumberEdit->sizePolicy().hasHeightForWidth());
        NumberEdit->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(NumberEdit, 0, 1, 1, 1);

        label_36 = new QLabel(groupBox);
        label_36->setObjectName(QString::fromUtf8("label_36"));

        gridLayout_5->addWidget(label_36, 3, 0, 1, 1);

        label_48 = new QLabel(groupBox);
        label_48->setObjectName(QString::fromUtf8("label_48"));

        gridLayout_5->addWidget(label_48, 5, 0, 1, 1);

        lable_shenqingrenyuan = new QLabel(groupBox);
        lable_shenqingrenyuan->setObjectName(QString::fromUtf8("lable_shenqingrenyuan"));

        gridLayout_5->addWidget(lable_shenqingrenyuan, 1, 3, 1, 1);

        label_26 = new QLabel(groupBox);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        gridLayout_5->addWidget(label_26, 2, 2, 1, 1);

        label_shenqingdanhao = new QLabel(groupBox);
        label_shenqingdanhao->setObjectName(QString::fromUtf8("label_shenqingdanhao"));

        gridLayout_5->addWidget(label_shenqingdanhao, 1, 1, 1, 1);

        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        gridLayout_5->addWidget(label_19, 0, 0, 1, 1);


        horizontalLayout_5->addWidget(groupBox);


        verticalLayout->addLayout(horizontalLayout_5);

        groupBox_4 = new QGroupBox(layoutWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout = new QGridLayout(groupBox_4);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        connectButton = new QPushButton(groupBox_4);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        horizontalLayout_3->addWidget(connectButton);

        GetDataButton = new QPushButton(groupBox_4);
        GetDataButton->setObjectName(QString::fromUtf8("GetDataButton"));

        horizontalLayout_3->addWidget(GetDataButton);


        gridLayout->addLayout(horizontalLayout_3, 0, 8, 1, 1);

        radioButton = new QRadioButton(groupBox_4);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        gridLayout->addWidget(radioButton, 1, 9, 1, 1);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        sehbeicomboBox = new QComboBox(groupBox_4);
        sehbeicomboBox->addItem(QString());
        sehbeicomboBox->addItem(QString());
        sehbeicomboBox->addItem(QString());
        sehbeicomboBox->setObjectName(QString::fromUtf8("sehbeicomboBox"));

        gridLayout->addWidget(sehbeicomboBox, 1, 6, 1, 2);

        caijiTypecomboBox = new QComboBox(groupBox_4);
        caijiTypecomboBox->addItem(QString());
        caijiTypecomboBox->addItem(QString());
        caijiTypecomboBox->setObjectName(QString::fromUtf8("caijiTypecomboBox"));

        gridLayout->addWidget(caijiTypecomboBox, 1, 1, 1, 3);

        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 2, 0, 1, 1);

        WriteFilepushButton = new QPushButton(groupBox_4);
        WriteFilepushButton->setObjectName(QString::fromUtf8("WriteFilepushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(WriteFilepushButton->sizePolicy().hasHeightForWidth());
        WriteFilepushButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(WriteFilepushButton, 2, 10, 1, 1);

        ShowDataButton = new QPushButton(groupBox_4);
        ShowDataButton->setObjectName(QString::fromUtf8("ShowDataButton"));

        gridLayout->addWidget(ShowDataButton, 2, 9, 1, 1);

        label_21 = new QLabel(groupBox_4);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        QFont font;
        font.setPointSize(17);
        label_21->setFont(font);
        label_21->setAcceptDrops(false);
        label_21->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_21, 2, 8, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout->addWidget(label_11);

        IpEdit = new QLineEdit(groupBox_4);
        IpEdit->setObjectName(QString::fromUtf8("IpEdit"));

        horizontalLayout->addWidget(IpEdit);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 5);

        ComCheckButton = new QPushButton(groupBox_4);
        ComCheckButton->setObjectName(QString::fromUtf8("ComCheckButton"));

        gridLayout->addWidget(ComCheckButton, 2, 11, 1, 1);

        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 1, 4, 1, 2);

        lineEdit_3 = new QLineEdit(groupBox_4);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 3, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_13 = new QLabel(groupBox_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_2->addWidget(label_13);

        PortEdit = new QLineEdit(groupBox_4);
        PortEdit->setObjectName(QString::fromUtf8("PortEdit"));

        horizontalLayout_2->addWidget(PortEdit);


        gridLayout->addLayout(horizontalLayout_2, 0, 5, 1, 3);

        ClearDataButton = new QPushButton(groupBox_4);
        ClearDataButton->setObjectName(QString::fromUtf8("ClearDataButton"));

        gridLayout->addWidget(ClearDataButton, 1, 11, 1, 1);

        saveFilePathEdit = new QLineEdit(groupBox_4);
        saveFilePathEdit->setObjectName(QString::fromUtf8("saveFilePathEdit"));

        gridLayout->addWidget(saveFilePathEdit, 2, 2, 1, 6);

        DownLoadFileButton = new QPushButton(groupBox_4);
        DownLoadFileButton->setObjectName(QString::fromUtf8("DownLoadFileButton"));
        DownLoadFileButton->setStyleSheet(QString::fromUtf8("background-color: green;"));

        gridLayout->addWidget(DownLoadFileButton, 1, 10, 1, 1);


        verticalLayout->addWidget(groupBox_4);


        horizontalLayout_6->addLayout(verticalLayout);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        label_16 = new QLabel(groupBox_2);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 7, 0, 1, 1);

        shenherenyuan_lineEdit = new QLineEdit(groupBox_2);
        shenherenyuan_lineEdit->setObjectName(QString::fromUtf8("shenherenyuan_lineEdit"));

        gridLayout_2->addWidget(shenherenyuan_lineEdit, 7, 1, 1, 1);

        FilecomboBox = new QComboBox(groupBox_2);
        FilecomboBox->setObjectName(QString::fromUtf8("FilecomboBox"));

        gridLayout_2->addWidget(FilecomboBox, 3, 1, 1, 1);

        label_12 = new QLabel(groupBox_2);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 4, 0, 1, 1);

        PathcomboBox = new QComboBox(groupBox_2);
        PathcomboBox->setObjectName(QString::fromUtf8("PathcomboBox"));
        sizePolicy1.setHeightForWidth(PathcomboBox->sizePolicy().hasHeightForWidth());
        PathcomboBox->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(PathcomboBox, 1, 1, 1, 1);

        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 5, 0, 1, 1);

        dateTimeEditEnd = new ZDateTimeEdit(groupBox_2);
        dateTimeEditEnd->setObjectName(QString::fromUtf8("dateTimeEditEnd"));
        dateTimeEditEnd->setCalendarPopup(false);

        gridLayout_2->addWidget(dateTimeEditEnd, 5, 1, 1, 1);

        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 6, 0, 1, 1);

        MobanlujinEdit = new QLineEdit(groupBox_2);
        MobanlujinEdit->setObjectName(QString::fromUtf8("MobanlujinEdit"));

        gridLayout_2->addWidget(MobanlujinEdit, 0, 1, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 3, 0, 1, 1);

        TypecomboBox = new QComboBox(groupBox_2);
        TypecomboBox->setObjectName(QString::fromUtf8("TypecomboBox"));

        gridLayout_2->addWidget(TypecomboBox, 2, 1, 1, 1);

        dateTimeEditStart = new ZDateTimeEdit(groupBox_2);
        dateTimeEditStart->setObjectName(QString::fromUtf8("dateTimeEditStart"));
        dateTimeEditStart->setWrapping(false);
        dateTimeEditStart->setAccelerated(false);
        dateTimeEditStart->setKeyboardTracking(true);
        dateTimeEditStart->setMaximumDateTime(QDateTime(QDate(9999, 12, 31), QTime(23, 59, 59)));
        dateTimeEditStart->setCalendarPopup(false);
        dateTimeEditStart->setCurrentSectionIndex(0);

        gridLayout_2->addWidget(dateTimeEditStart, 4, 1, 1, 1);

        celiangrenyuan_lineEdit = new QLineEdit(groupBox_2);
        celiangrenyuan_lineEdit->setObjectName(QString::fromUtf8("celiangrenyuan_lineEdit"));

        gridLayout_2->addWidget(celiangrenyuan_lineEdit, 6, 1, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 8, 0, 1, 1);

        jianceleibie_comboBox = new QComboBox(groupBox_2);
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

        gridLayout_2->addWidget(jianceleibie_comboBox, 8, 1, 1, 1);


        horizontalLayout_6->addWidget(groupBox_2);


        verticalLayout_2->addLayout(horizontalLayout_6);

        ShowtableView = new QTableView(layoutWidget);
        ShowtableView->setObjectName(QString::fromUtf8("ShowtableView"));

        verticalLayout_2->addWidget(ShowtableView);


        retranslateUi(OperationInterface);

        sehbeicomboBox->setCurrentIndex(0);
        caijiTypecomboBox->setCurrentIndex(0);
        FilecomboBox->setCurrentIndex(-1);
        PathcomboBox->setCurrentIndex(-1);
        TypecomboBox->setCurrentIndex(-1);
        jianceleibie_comboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(OperationInterface);
    } // setupUi

    void retranslateUi(QWidget *OperationInterface)
    {
        OperationInterface->setWindowTitle(QCoreApplication::translate("OperationInterface", "OperationInterface", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("OperationInterface", "\347\224\250\346\210\267", nullptr));
        label_17->setText(QCoreApplication::translate("OperationInterface", "\345\267\245\345\217\267\357\274\232", nullptr));
        UserEdit->setText(QCoreApplication::translate("OperationInterface", "10030534", nullptr));
        label_18->setText(QCoreApplication::translate("OperationInterface", "\345\257\206\347\240\201\357\274\232", nullptr));
        PasswordEdit->setText(QCoreApplication::translate("OperationInterface", "Qwer.12345", nullptr));
        LoginPushButton->setText(QCoreApplication::translate("OperationInterface", "\347\231\273\345\275\225", nullptr));
        groupBox->setTitle(QCoreApplication::translate("OperationInterface", "\345\217\202\346\225\260", nullptr));
        GetInfoButton->setText(QCoreApplication::translate("OperationInterface", "\346\237\245\350\257\242", nullptr));
        label_jitai->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_beizhu->setText(QCoreApplication::translate("OperationInterface", "\345\244\207\346\263\250\357\274\232", nullptr));
        label_38->setText(QCoreApplication::translate("OperationInterface", "\346\230\257\345\220\246\347\240\264\345\235\217\357\274\232", nullptr));
        label_jianyanleibie->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_25->setText(QCoreApplication::translate("OperationInterface", "\351\200\201\346\243\200\345\215\225\344\275\215:", nullptr));
        label_gongxu->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_23->setText(QCoreApplication::translate("OperationInterface", "\347\224\263\350\257\267\344\272\272\345\221\230\357\274\232", nullptr));
        label_songjiandanwei->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_41->setText(QCoreApplication::translate("OperationInterface", "\346\243\200\346\265\213\351\241\271\347\233\256:", nullptr));
        label_shifoupohuai->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_jiajubianhao->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_44->setText(QCoreApplication::translate("OperationInterface", "\345\244\271\345\205\267\347\274\226\345\217\267\357\274\232", nullptr));
        label_42->setText(QCoreApplication::translate("OperationInterface", "\346\243\200\351\252\214\347\261\273\345\210\253\357\274\232", nullptr));
        label_muxuehao->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_jiancexiangmu->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_xiangmmumingchen->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_29->setText(QCoreApplication::translate("OperationInterface", "\347\224\263\350\257\267\346\227\266\351\227\264:", nullptr));
        label_32->setText(QCoreApplication::translate("OperationInterface", "\346\240\267\345\223\201\346\225\260\351\207\217\357\274\232", nullptr));
        label_shoujianshijian->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_20->setText(QCoreApplication::translate("OperationInterface", "\347\224\263\350\257\267\345\215\225\345\217\267\357\274\232", nullptr));
        label_35->setText(QCoreApplication::translate("OperationInterface", "\346\224\266\344\273\266\346\227\266\351\227\264:", nullptr));
        label_47->setText(QCoreApplication::translate("OperationInterface", "\346\250\241\347\251\264\345\217\267:", nullptr));
        label_shenqingshijian->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_yangpingshuliang->setText(QCoreApplication::translate("OperationInterface", "5", nullptr));
        label_30->setText(QCoreApplication::translate("OperationInterface", "\351\241\271\347\233\256\345\220\215\347\247\260\357\274\232", nullptr));
        label_jianceyaoqiu->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        NumberEdit->setText(QCoreApplication::translate("OperationInterface", "mmsdCY12412160C6", nullptr));
        label_36->setText(QCoreApplication::translate("OperationInterface", "\346\243\200\346\265\213\350\246\201\346\261\202\357\274\232", nullptr));
        label_48->setText(QCoreApplication::translate("OperationInterface", "\345\267\245\345\272\217\357\274\232", nullptr));
        lable_shenqingrenyuan->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_26->setText(QCoreApplication::translate("OperationInterface", "\346\234\272\345\217\260\357\274\232", nullptr));
        label_shenqingdanhao->setText(QCoreApplication::translate("OperationInterface", "\350\257\267\345\205\210\350\276\223\345\205\245mms\345\255\220\345\215\225\345\217\267", nullptr));
        label_19->setText(QCoreApplication::translate("OperationInterface", "mm\345\255\220\345\215\225\345\217\267\357\274\232", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("OperationInterface", "\347\275\221\347\273\234", nullptr));
        connectButton->setText(QCoreApplication::translate("OperationInterface", "\345\273\272\347\253\213\351\223\276\346\216\245", nullptr));
        GetDataButton->setText(QCoreApplication::translate("OperationInterface", "\350\216\267\345\217\226\346\225\260\346\215\256", nullptr));
        radioButton->setText(QCoreApplication::translate("OperationInterface", "\344\277\256\346\224\271\346\225\260\346\215\256", nullptr));
        label_6->setText(QCoreApplication::translate("OperationInterface", "\350\207\252\345\212\250\346\204\237\347\237\245\346\226\207\344\273\266\350\267\257\345\276\204\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("OperationInterface", "\351\207\207\351\233\206\346\226\271\345\274\217\357\274\232", nullptr));
        sehbeicomboBox->setItemText(0, QCoreApplication::translate("OperationInterface", "\345\205\206\344\270\2601", nullptr));
        sehbeicomboBox->setItemText(1, QCoreApplication::translate("OperationInterface", "MIV", nullptr));
        sehbeicomboBox->setItemText(2, QCoreApplication::translate("OperationInterface", "\345\205\206\344\270\2602", nullptr));

        caijiTypecomboBox->setItemText(0, QCoreApplication::translate("OperationInterface", "\346\225\260\346\215\256\345\257\271\346\216\245", nullptr));
        caijiTypecomboBox->setItemText(1, QCoreApplication::translate("OperationInterface", "\350\207\252\345\212\250\346\204\237\347\237\245", nullptr));

        label_8->setText(QCoreApplication::translate("OperationInterface", "\346\226\207\344\273\266\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", nullptr));
        WriteFilepushButton->setText(QCoreApplication::translate("OperationInterface", "\344\270\212\344\274\240\346\225\260\346\215\256", nullptr));
        ShowDataButton->setText(QCoreApplication::translate("OperationInterface", "\344\277\241\346\201\257\346\230\276\347\244\272", nullptr));
        label_21->setText(QCoreApplication::translate("OperationInterface", "OK", nullptr));
        label_11->setText(QCoreApplication::translate("OperationInterface", "iP\357\274\232", nullptr));
        IpEdit->setText(QCoreApplication::translate("OperationInterface", "192.168.31.145", nullptr));
        ComCheckButton->setText(QCoreApplication::translate("OperationInterface", "\345\256\214\346\210\220\346\243\200\346\265\213", nullptr));
        label_7->setText(QCoreApplication::translate("OperationInterface", "\350\256\276\345\244\207\345\223\201\347\211\214\357\274\232", nullptr));
        label_13->setText(QCoreApplication::translate("OperationInterface", "\347\253\257\345\217\243\357\274\232", nullptr));
        PortEdit->setText(QCoreApplication::translate("OperationInterface", "8889", nullptr));
        ClearDataButton->setText(QCoreApplication::translate("OperationInterface", "\346\270\205\347\251\272\346\225\260\346\215\256", nullptr));
        DownLoadFileButton->setText(QCoreApplication::translate("OperationInterface", "\344\270\213\350\275\275\346\226\207\344\273\266", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("OperationInterface", "\346\226\207\344\273\266\351\200\211\346\213\251", nullptr));
        label_2->setText(QCoreApplication::translate("OperationInterface", "\346\235\220\346\226\231\345\220\215\347\247\260\357\274\232", nullptr));
        label_16->setText(QCoreApplication::translate("OperationInterface", "\345\256\241\346\240\270\344\272\272\345\221\230", nullptr));
        label_12->setText(QCoreApplication::translate("OperationInterface", "\345\274\200\345\247\213\346\227\266\351\227\264", nullptr));
        label_14->setText(QCoreApplication::translate("OperationInterface", "\347\273\223\346\235\237\346\227\266\351\227\264", nullptr));
        dateTimeEditEnd->setDisplayFormat(QCoreApplication::translate("OperationInterface", "yyyy-M-d H:mm", nullptr));
        label_15->setText(QCoreApplication::translate("OperationInterface", "\346\265\213\351\207\217\344\272\272\345\221\230", nullptr));
        MobanlujinEdit->setText(QCoreApplication::translate("OperationInterface", "D:\\", nullptr));
        label_4->setText(QCoreApplication::translate("OperationInterface", "\351\241\271\347\233\256\350\267\257\345\276\204:", nullptr));
        label->setText(QCoreApplication::translate("OperationInterface", "\351\241\271\347\233\256\345\220\215\347\247\260:", nullptr));
        label_3->setText(QCoreApplication::translate("OperationInterface", "\346\212\245\345\221\212\351\200\211\346\213\251:", nullptr));
        dateTimeEditStart->setDisplayFormat(QCoreApplication::translate("OperationInterface", "yyyy-M-d H:mm", nullptr));
        label_10->setText(QCoreApplication::translate("OperationInterface", "\346\243\200\346\237\245\347\261\273\345\210\253\357\274\232", nullptr));
        jianceleibie_comboBox->setItemText(0, QCoreApplication::translate("OperationInterface", "FAI", nullptr));
        jianceleibie_comboBox->setItemText(1, QCoreApplication::translate("OperationInterface", "CPK", nullptr));
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

    } // retranslateUi

};

namespace Ui {
    class OperationInterface: public Ui_OperationInterface {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPERATIONINTERFACE_H
