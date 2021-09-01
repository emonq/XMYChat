QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../XMYChatShare/xmy_tcpsocket.cpp \
    ../XMYChatShare/xmy_utilities.cpp \
    clientdatabase.cpp \
    friendsearchdialog.cpp \
    loginsession.cpp \
    main.cpp \
    loginwindow.cpp \
    registerdialog.cpp \
    settingdialog.cpp \
    userinfodialog.cpp \
    usermainwindow.cpp \
    verificationdialog.cpp \
    xmyusersettings.cpp

HEADERS += \
    ../XMYChatShare/xmy_basic.h \
    ../XMYChatShare/xmy_tcpsocket.h \
    ../XMYChatShare/xmy_utilities.h \
    clientdatabase.h \
    friendsearchdialog.h \
    loginsession.h \
    loginwindow.h \
    registerdialog.h \
    settingdialog.h \
    userinfodialog.h \
    usermainwindow.h \
    verificationdialog.h \
    xmyusersettings.h

FORMS += \
    friendsearchdialog.ui \
    loginwindow.ui \
    registerdialog.ui \
    settingdialog.ui \
    userinfodialog.ui \
    usermainwindow.ui \
    verificationdialog.ui

UI_DIR = .

#TRANSLATIONS += \
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
