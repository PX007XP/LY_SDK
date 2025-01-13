QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets network axcontainer xml

CONFIG += c++17

TARGET = LIMS
TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
 #-*- coding: utf-8 -*-

 QMAKE_CXXFLAGS += /FS

SOURCES += \
    configobject.cpp \
    datecommoninfo.cpp \
    excellprecess.cpp \
    globle.cpp \
    httpnetobject.cpp \
    loadingdialog.cpp \
    logger.cpp \
    main.cpp \
    recvfile.cpp \
    sheetfilldatarange.cpp\
    operationinterface.cpp\
    tempdata.cpp\
    readpoint.cpp\
    tablemodel.cpp \
    zdatetimeedit.cpp

HEADERS += \
    configobject.h \
    datecommoninfo.h \
    excellprecess.h \
    globle.h \
    httpnetobject.h \
    loadingdialog.h \
    logger.h \
    recvfile.h \
    sheetfilldatarange.h\
    operationinterface.h \
    ui_operationinterface.h \
    tempdata.h\
    readpoint.h\
    tablemodel.h \
    zdatetimeedit.h

FORMS += \
    operationinterface.ui

msvc{
    QMAKE_CFLAGS += /utf-8
    QMAKE_CXXFLAGS += /utf-8
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    css.qrc
