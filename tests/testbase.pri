QT *= testlib
CONFIG *= console testcase app_bundle
TEMPLATE = app
INCLUDEPATH += -I $$OUT_PWD -I $$PWD/../include/
LIBS += -L$$OUT_PWD/../../lib -lqosdnotification
macx {
    qosdnotification.path = Contents/MacOS
    qosdnotification.files = $$OUT_PWD/../../lib/libqosdnotification.1.dylib
    QMAKE_BUNDLE_DATA += qosdnotification
}
