#-------------------------------------------------
#
# Project created by QtCreator 2023-04-17T19:55:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ISP-03
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    global.cpp \
    user.cpp \
    logindialog.cpp \
    keymanage.cpp \
    modemanage.cpp \
    filemanage.cpp

HEADERS += \
        mainwindow.h \
    global.h \
    main.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qcertmgr.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qipworksopenpgp.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qipworksopenpgpkey.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qkeymgr.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qmime.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qopenpgp.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qpfilemailer.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qphtmlmailer.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qpimap.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qppop.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qpsmtp.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/qt/qsda.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/certmgr.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/ipworksopenpgp.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/keymgr.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/mime.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/openpgp.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/pfilemailer.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/phtmlmailer.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/pimap.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/ppop.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/psmtp.h \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/sda.h \
    logindialog.h \
    user.h \
    keymanage.h \
    modemanage.h \
    filemanage.h

FORMS += \
        mainwindow.ui \
    logindialog.ui

# INCLUDEPATH += D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\
INCLUDEPATH += D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\include\qt\

LIBS    += D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\lib\ipworksopenpgp22.dll
LIBS    += D:\preopengpg\IPWorks-OpenPGP-2022-C++-Edition-2\lib64\ipworksopenpgp22.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/ipworksopenpgp.key \
    ../../../preopengpg/IPWorks-OpenPGP-2022-C++-Edition-2/include/unicode/ipworksopenpgp.key

