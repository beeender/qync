cmake_minimum_required(VERSION 2.8)

project(qync)

include(FindPkgConfig)
include(FindGLIB.cmake)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Core)

pkg_search_module (GLIB2 REQUIRED glib-2.0)
pkg_search_module (GMIME26 REQUIRED gmime-2.6)
pkg_search_module (XML2 REQUIRED libxml-2.0)
pkg_search_module (OPENSSL REQUIRED openssl)

include_directories(${GLIB2_INCLUDE_DIRS})
include_directories(${GMIME26_INCLUDE_DIRS})
include_directories(${OPENSSL_INCLUDE_DIRS})
include_directories(${XML2_INCLUDE_DIRS})

message(STATUS "link dir: -${SSL_INCLUDE_DIRS}")

file (STRINGS "siplcs/VERSION" package-version)
add_definitions(-DPACKAGE_VERSION="${package-version}")
add_definitions(-DPACKAGE_URL="http://sipe.sourceforge.net/")
add_definitions(-DPACKAGE_BUGREPORT="https://sourceforge.net/p/sipe/bugs/")
add_definitions(-DSIPE_TRANSLATIONS_URL="https://www.transifex.com/projects/p/pidgin-sipe/r/mob/")

add_definitions(-g)

include_directories(${sipe-headers}siplcs/src/api/)

set(sipe-core-files
    siplcs/src/core/sipmsg.h
    siplcs/src/core/sipmsg.c
    siplcs/src/core/sip-csta.h
    siplcs/src/core/sip-csta.c
    siplcs/src/core/sip-sec.h
    siplcs/src/core/sip-sec.c
    siplcs/src/core/sip-sec-basic.h
    siplcs/src/core/sip-sec-basic.c
    siplcs/src/core/sip-sec-digest.h
    siplcs/src/core/sip-sec-digest.c
    siplcs/src/core/sip-sec-mech.h
    siplcs/src/core/sip-sec-tls-dsk.h
    siplcs/src/core/sip-sec-tls-dsk.c
    siplcs/src/core/sip-soap.h
    siplcs/src/core/sip-soap.c
    siplcs/src/core/sip-transport.h
    siplcs/src/core/sip-transport.c
    siplcs/src/core/sipe-buddy.h
    siplcs/src/core/sipe-buddy.c
    siplcs/src/core/sipe-cal.h
    siplcs/src/core/sipe-cal.c
    siplcs/src/core/sipe-certificate.h
    siplcs/src/core/sipe-certificate.c
    siplcs/src/core/sipe-cert-crypto.h
    siplcs/src/core/sipe-chat.h
    siplcs/src/core/sipe-chat.c
    siplcs/src/core/sipe-conf.h
    siplcs/src/core/sipe-conf.c
    siplcs/src/core/sipe-core-private.h
    siplcs/src/core/sipe-core.c
    siplcs/src/core/sipe-crypt.h
    siplcs/src/core/sipe-dialog.h
    siplcs/src/core/sipe-dialog.c
    siplcs/src/core/sipe-digest.h
    siplcs/src/core/sipe-ews.h
    siplcs/src/core/sipe-ews.c
    siplcs/src/core/sipe-ews-autodiscover.h
    siplcs/src/core/sipe-ews-autodiscover.c
    siplcs/src/core/sipe-ft.h
    siplcs/src/core/sipe-ft.c
    siplcs/src/core/sipe-ft-tftp.c
    siplcs/src/core/sipe-group.h
    siplcs/src/core/sipe-group.c
    siplcs/src/core/sipe-groupchat.h
    siplcs/src/core/sipe-groupchat.c
    siplcs/src/core/sipe-http.h
    siplcs/src/core/sipe-http.c
    siplcs/src/core/sipe-http-request.h
    siplcs/src/core/sipe-http-request.c
    siplcs/src/core/sipe-http-transport.h
    siplcs/src/core/sipe-http-transport.c
    siplcs/src/core/sipe-im.h
    siplcs/src/core/sipe-im.c
    siplcs/src/core/sipe-incoming.h
    siplcs/src/core/sipe-incoming.c
    siplcs/src/core/sipe-notify.h
    siplcs/src/core/sipe-notify.c
    siplcs/src/core/sipe-ocs2005.h
    siplcs/src/core/sipe-ocs2005.c
    siplcs/src/core/sipe-ocs2007.h
    siplcs/src/core/sipe-ocs2007.c
    siplcs/src/core/sipe-schedule.h
    siplcs/src/core/sipe-schedule.c
    siplcs/src/core/sipe-session.h
    siplcs/src/core/sipe-session.c siplcs/src/core/sipe-sign.h
    siplcs/src/core/sipe-sign.c
    siplcs/src/core/sipe-status.h
    siplcs/src/core/sipe-status.c
    siplcs/src/core/sipe-subscriptions.h
    siplcs/src/core/sipe-subscriptions.c
    siplcs/src/core/sipe-svc.h
    siplcs/src/core/sipe-svc.c
    siplcs/src/core/sipe-tls.h
    siplcs/src/core/sipe-tls.c
    siplcs/src/core/sipe-ucs.h
    siplcs/src/core/sipe-ucs.c
    siplcs/src/core/sipe-user.h
    siplcs/src/core/sipe-user.c
    siplcs/src/core/sipe-utils.h
    siplcs/src/core/sipe-utils.c
    siplcs/src/core/sipe-webticket.h
    siplcs/src/core/sipe-webticket.c
    siplcs/src/core/sipe-xml.h
    siplcs/src/core/uuid.h
    siplcs/src/core/uuid.c)

#TODO: Check GSSAPI only
set(sipe-core-files ${sipe-core-files}
    siplcs/src/core/md4.h
    siplcs/src/core/md4.c
    siplcs/src/core/sip-sec-ntlm.h
    siplcs/src/core/sip-sec-ntlm.c)

#TODO: Check OPENSSL
set(sipe-core-files ${sipe-core-files}
    siplcs/src/core/sipe-cert-crypto-openssl.c
    siplcs/src/core/sipe-crypt-openssl.c
    siplcs/src/core/sipe-digest-openssl.c)
#TODO:else
#set(sipe-core-files ${sipe-core-files}
#    siplcs/src/core/sipe-cert-crypto-nss.c
#    siplcs/src/core/sipe-crypt-nss.c
#    siplcs/src/core/sipe-digest-nss.c)

set(sipe-core-files ${sipe-core-files}
    siplcs/src/core/sipe-xml.c)

set(sipe-core-files ${sipe-core-files}
    siplcs/src/core/sipe-mime.c)
#Video & Voice call
#set(sipe-core-files ${sipe-core-files}
    #siplcs/src/core/sipe-media.h
    #siplcs/src/core/sipe-media.c
    #siplcs/src/core/sdpmsg.h
    #siplcs/src/core/sdpmsg.c)

aux_source_directory("sipe-qync/" sipe-backend-files)

add_library(sipe-qync STATIC ${sipe-core-files} ${sipe-backend-files})
qt5_use_modules(sipe-qync Network)

include_directories("core/")
aux_source_directory("core/" core-files)
add_executable(qync qync.cpp ${core-files})
add_dependencies(qync sipe-qync)
# Use the Widgets module from Qt 5.
qt5_use_modules(qync Widgets Network Qml Quick)
target_link_libraries(qync ${PROJECT_BINARY_DIR}/libsipe-qync.a
    ${GLIB_LIBRARIES} ${GMIME26_LIBRARIES} ${OPENSSL_LIBRARIES} ${XML2_LIBRARIES})

#install(TARGETS myapp DESTINATION bin)
