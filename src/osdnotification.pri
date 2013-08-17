QT *= core gui

greaterThan(QT_MAJOR_VERSION, 4): QT *= widgets

INCLUDEPATH += $$PWD

SOURCES += \
    $$PWD/qosdnotificationmanager.cpp \
    $$PWD/qabstractosdnotification.cpp \
    $$PWD/qosdnotification.cpp \
    $$PWD/qosdnotificationclosebutton.cpp

HEADERS += \
    $$PWD/qosdnotificationmanager.h \
    $$PWD/qosdnotificationmanager_p.h \
    $$PWD/qabstractosdnotification.h \
    $$PWD/qabstractosdnotification_p.h \
    $$PWD/qosdnotification.h \
    $$PWD/qosdnotification_p.h \
    $$PWD/qosdnotificationclosebutton.h \
    $$PWD/qosdnotificationclosebutton_p.h \
    $$PWD/qosdnotification_global.h

contains(DEFINES, OSDNOTIFICATION_DEBUG) {
    DEFINES += QOSDNOTIFICATIONMANAGER_DEBUG \
        QOSDNOTIFICATION_DEBUG
}
