#ifndef QOSDNOTIFICATIONCLOSEBUTTON_P_H
#define QOSDNOTIFICATIONCLOSEBUTTON_P_H

#include "qosdnotificationclosebutton.h"

class QOSDNotificationCloseButtonPrivate
{
public:
    QOSDNotificationCloseButtonPrivate();
    virtual ~QOSDNotificationCloseButtonPrivate();

    QColor color;
    QColor hoverColor;
    qreal opacity;
    qreal hoverOpacity;
    bool hovered;
};

#endif // QOSDNOTIFICATIONCLOSEBUTTON_P_H
