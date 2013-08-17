#include <QApplication>
#include <QBrush>
#include <QPen>

#include <QOSDNotificationManager>
#include <QOSDNotification>

#include "customosdnotification.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QOSDNotificationManager manager;

    const QColor backgroundColor = QColor(102, 150, 227);
    const QColor borderColor = backgroundColor.darker(150);

    QOSDNotification notification1(QObject::tr("QOSDNotification"), QObject::tr("Text 1"));
    notification1.setBackgroundColor(backgroundColor);
    notification1.setBackgroundHoverColor(backgroundColor);
    notification1.setBorderColor(borderColor);
    notification1.setBorderHoverColor(borderColor);
    notification1.setTitleColor(Qt::black);
    notification1.setBodyTextColor(Qt::black);
    manager.add(&notification1);

    QPen pen(Qt::cyan);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    QPen hoverPen(pen);
    hoverPen.setStyle(Qt::DashLine);

    QOSDNotification notification2(QObject::tr("QOSDNotification"), QObject::tr("Text 2"));
    notification2.setBackgroundBrush(QBrush(Qt::black, Qt::SolidPattern));
    notification2.setBorderPen(pen);
    notification2.setBorderHoverPen(hoverPen);
    manager.add(&notification2);

    CustomOSDNotification notification3(QObject::tr("CustomOSDNotification"), QObject::tr("Text 3"));
    manager.add(&notification3);

    return app.exec();
}
