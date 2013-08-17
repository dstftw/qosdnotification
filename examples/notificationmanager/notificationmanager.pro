QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS = notificationmanager.h \
    colorwidget.h \
    notificationsettingswidget.h \
    icondroparea.h \
    iconwidget.h \
    notificationmanagersettingswidget.h
SOURCES = notificationmanager.cpp \
    main.cpp \
    colorwidget.cpp \
    notificationsettingswidget.cpp \
    icondroparea.cpp \
    iconwidget.cpp \
    notificationmanagersettingswidget.cpp

include(../examplebase.pri)
