#ifndef QABSTRACTOSDNOTIFICATION_P_H
#define QABSTRACTOSDNOTIFICATION_P_H

#include <QTimer>

#include "qabstractosdnotification.h"

class QAbstractOSDNotificationPrivate
{
    Q_DECLARE_PUBLIC(QAbstractOSDNotification)
public:
    QAbstractOSDNotificationPrivate();
    virtual ~QAbstractOSDNotificationPrivate();

    void init(QAbstractOSDNotification *q);

    void restartDurationTimer();

    void _q_durationTimeout();

    QAbstractOSDNotification *q_ptr;

    bool deleteLater;
    int duration;
    QTimer durationTimer;
    QTimer fadeOutTimer;
    bool hovered;
};

#endif // QABSTRACTOSDNOTIFICATION_P_H
