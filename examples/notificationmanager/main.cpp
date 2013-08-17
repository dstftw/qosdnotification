#include <QApplication>

#include "notificationmanager.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    NotificationManager manager;
    manager.show();

    return app.exec();
}
