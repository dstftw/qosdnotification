TARGET = qosdnotification
TEMPLATE = lib
win32: DESTDIR = ./
DEFINES += QOSDNOTIFICATION_LIBRARY
include($$PWD/../src/osdnotification.pri)
