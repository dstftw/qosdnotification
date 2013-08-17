#include <QApplication>

#include <QOSDNotificationManager>
#include <QOSDNotification>

#include "customwidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QOSDNotificationManager manager;

    CustomWidget customWidget;
    QOSDNotification notification(QObject::tr("Enter some text"), &customWidget);
    QObject::connect(&customWidget, SIGNAL(done()), &notification, SLOT(close()));

    manager.add(&notification);

    return app.exec();
}
