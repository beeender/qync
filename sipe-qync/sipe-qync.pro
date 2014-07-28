#-------------------------------------------------
#
# Project created by QtCreator 2014-07-28T16:38:52
#
#-------------------------------------------------

QT       += qml network sql

QT       -= gui

TARGET = sipe-qync
TEMPLATE = lib
CONFIG += staticlib

DEFINES += SIPEQYNC_LIBRARY

# enable the PKGCONFIG feature
CONFIG += link_pkgconfig
PKGCONFIG += glib-2.0
PKGCONFIG += gmime-2.6
PKGCONFIG += libxml-2.0

DEFINES += PACKAGE_VERSION=\\\"$$system(cat ./siplcs/VERSION)\\\"
DEFINES += PACKAGE_URL=\\\"http://sipe.sourceforge.net/\\\"
DEFINES += PACKAGE_BUGREPORT=\\\"https://sourceforge.net/p/sipe/bugs/\\\"
DEFINES += SIPE_TRANSLATIONS_URL=\\\"https://www.transifex.com/projects/p/pidgin-sipe/r/mob/\\\"

SOURCES += \
    siplcs/src/core/md4.c \
    siplcs/src/core/sip-csta.c \
    siplcs/src/core/sip-sec-basic.c \
    siplcs/src/core/sip-sec-digest.c \
    siplcs/src/core/sip-sec-gssapi.c \
    siplcs/src/core/sip-sec-negotiate.c \
    siplcs/src/core/sip-sec-ntlm.c \
    siplcs/src/core/sip-sec-tls-dsk.c \
    siplcs/src/core/sip-sec.c \
    siplcs/src/core/sip-soap.c \
    siplcs/src/core/sip-transport.c \
    siplcs/src/core/sipe-buddy.c \
    siplcs/src/core/sipe-cal.c \
    siplcs/src/core/sipe-cert-crypto-openssl.c \
    siplcs/src/core/sipe-certificate.c \
    siplcs/src/core/sipe-chat.c \
    siplcs/src/core/sipe-conf.c \
    siplcs/src/core/sipe-core.c \
    siplcs/src/core/sipe-crypt-openssl.c \
    siplcs/src/core/sipe-dialog.c \
    siplcs/src/core/sipe-digest-openssl.c \
    siplcs/src/core/sipe-domino.c \
    siplcs/src/core/sipe-ews-autodiscover.c \
    siplcs/src/core/sipe-ews.c \
    siplcs/src/core/sipe-ft-tftp.c \
    siplcs/src/core/sipe-ft.c \
    siplcs/src/core/sipe-group.c \
    siplcs/src/core/sipe-groupchat.c \
    siplcs/src/core/sipe-http-request.c \
    siplcs/src/core/sipe-http-transport.c \
    siplcs/src/core/sipe-http.c \
    siplcs/src/core/sipe-im.c \
    siplcs/src/core/sipe-incoming.c \
    siplcs/src/core/sipe-mime.c \
    siplcs/src/core/sipe-notify.c \
    siplcs/src/core/sipe-ocs2005.c \
    siplcs/src/core/sipe-ocs2007.c \
    siplcs/src/core/sipe-schedule.c \
    siplcs/src/core/sipe-session.c \
    siplcs/src/core/sipe-sign.c \
    siplcs/src/core/sipe-status.c \
    siplcs/src/core/sipe-subscriptions.c \
    siplcs/src/core/sipe-svc.c \
    siplcs/src/core/sipe-tls.c \
    siplcs/src/core/sipe-ucs.c \
    siplcs/src/core/sipe-user.c \
    siplcs/src/core/sipe-utils.c \
    siplcs/src/core/sipe-webticket.c \
    siplcs/src/core/sipe-xml.c \
    siplcs/src/core/sipmsg.c \
    siplcs/src/core/uuid.c \
    src/QyncBackend.cpp \
    src/QyncBuddyListModel.cpp \
    src/QyncBuddyObject.cpp \
    src/QyncDB.cpp \
    src/QyncGroupObject.cpp \
    src/QyncSipe.cpp \
    src/QyncSipeBuddy.cpp \
    src/QyncSipeChat.cpp \
    src/QyncSipeConnection.cpp \
    src/QyncSipeDebug.cpp \
    src/QyncSipeDnsQuery.cpp \
    src/QyncSipeFt.cpp \
    src/QyncSipeGroupChat.cpp \
    src/QyncSipeIm.cpp \
    src/QyncSipeMain.cpp \
    src/QyncSipeMarkup.cpp \
    src/QyncSipeNetwork.cpp \
    src/QyncSipeNotify.cpp \
    src/QyncSipeSchedule.cpp \
    src/QyncSipeSearch.cpp \
    src/QyncSipeSetting.cpp \
    src/QyncSipeStatus.cpp \
    src/QyncSipeTransport.cpp \
    src/QyncSipeUser.cpp \
    src/QyncSipeUtils.cpp

INCLUDEPATH += inc/ siplcs/src/api/

HEADERS +=\
        sipe-qync_global.h \
    inc/QyncBackend.h \
    inc/QyncBuddyListModel.h \
    inc/QyncBuddyObject.h \
    inc/QyncDB.h \
    inc/QyncGroupObject.h \
    inc/QyncSipe.h \
    src/QyncSipeUtils.h \
    siplcs/src/api/sipe-backend.h \
    siplcs/src/api/sipe-common.h \
    siplcs/src/api/sipe-core.h \
    siplcs/src/api/sipe-mime.h \
    siplcs/src/api/sipe-nls.h \
    sipe-qync_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
