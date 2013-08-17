#ifndef QOSDNOTIFICATIONMANAGER_P_H
#define QOSDNOTIFICATIONMANAGER_P_H

#include "qosdnotificationmanager.h"

class QOSDNotificationManagerPrivate
{
    Q_DECLARE_PUBLIC(QOSDNotificationManager)
public:
    QOSDNotificationManagerPrivate(QOSDNotificationManager *qq);
    virtual ~QOSDNotificationManagerPrivate();

    bool isTop() const;
    bool isLeft() const;
    QRect availableGeometry() const;
    int notificationsHeight() const;
    int verticalOffset() const;

    void updateNotificationSizes();
    void updateNotificationPositions();
    void setNotificationPosition(QAbstractOSDNotification *notification);

    void addNotification(QAbstractOSDNotification *notification);
    void removeNotification(QAbstractOSDNotification *notification);

    void _q_notificationResized();
    void _q_notificationFinished();

    QOSDNotificationManager *q_ptr;

    const QWidget *mainWidget;
    QList<QAbstractOSDNotification *> notifications;
    Qt::Corner notificationPosition;
    int maxCount;
    int horizontalMargin;
    int verticalMargin;
    int spacing;
    int defaultDuration;
    int minimumNotificationWidth;
    int minimumNotificationHeight;
    int maximumNotificationWidth;
    int maximumNotificationHeight;
};

#endif // QOSDNOTIFICATIONMANAGER_P_H
