QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../XMYChatShare/xmy_tcpsocket.cpp \
    ../XMYChatShare/xmy_utilities.cpp \
    main.cpp \
    startwindow.cpp \
    xmy_database.cpp \
    xmy_tcpserver.cpp

HEADERS += \
    ../XMYChatShare/xmy_basic.h \
    ../XMYChatShare/xmy_tcpsocket.h \
    ../XMYChatShare/xmy_utilities.h \
    startwindow.h \
    xmy_database.h \
    xmy_tcpserver.h

FORMS += \
    startwindow.ui

TRANSLATIONS += \
    XMYChatServer_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
