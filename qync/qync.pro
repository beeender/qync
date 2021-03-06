TEMPLATE = app

QT += qml quick widgets sql

#TODO:Remove this.
CONFIG += link_pkgconfig
CONFIG += c++11
PKGCONFIG += glib-2.0
PKGCONFIG += openssl
PKGCONFIG += gobject-2.0
PKGCONFIG += gmime-2.6
PKGCONFIG += libxml-2.0

SOURCES += \
    qync.cpp \
    core/QyncSipeCore.cpp \
    core/QyncDB.cpp \
    core/QyncBuddyListModel.cpp \
    core/QyncCategoryListModel.cpp \
    core/QyncBuddy.cpp \
    core/QyncGroup.cpp \
    core/QyncUtils.cpp

RESOURCES += \
    qml/qml.qrc

INCLUDEPATH += ../sipe-qync/inc core/
LIBS += ../sipe-qync/libsipe-qync.a

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    core/QyncSipeCore.h \
    core/QyncDB.h \
    core/QyncBuddyListModel.h \
    core/QyncCategoryListModel.h \
    core/QyncBuddy.h \
    core/QyncGroup.h \
    core/QyncUtils.h
