QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../XMYChatShare/xmy_tcpsocket.cpp \
    addfriend.cpp \
    chat.cpp \
    chatwindow.cpp \
    loginsession.cpp \
    main.cpp \
    loginwindow.cpp \
    settingdialog.cpp \
    user.cpp \
    xmyusersettings.cpp

HEADERS += \
    ../XMYChatShare/xmy_basic.h \
    ../XMYChatShare/xmy_tcpsocket.h \
    addfriend.h \
    chat.h \
    chatwindow.h \
    loginsession.h \
    loginwindow.h \
    settingdialog.h \
    user.h \
    xmyusersettings.h

FORMS += \
    addfriend.ui \
    chat.ui \
    chatwindow.ui \
    loginwindow.ui \
    settingdialog.ui \
    user.ui

TRANSLATIONS += \
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \

RESOURCES += \
    images.qrc \
