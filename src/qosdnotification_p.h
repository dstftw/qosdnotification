#ifndef QOSDNOTIFICATION_P_H
#define QOSDNOTIFICATION_P_H

#include "qosdnotification.h"
#include "qabstractosdnotification_p.h"

QT_BEGIN_NAMESPACE
class QLabel;
class QToolButton;
class QStackedLayout;
class QVBoxLayout;
QT_END_NAMESPACE

class QOSDNotificationCloseButton;

class QOSDNotificationPrivate : QAbstractOSDNotificationPrivate
{
    Q_DECLARE_PUBLIC(QOSDNotification)
public:
    QOSDNotificationPrivate();
    virtual ~QOSDNotificationPrivate();

    void init();

    void setTitle(const QString &title);
    void setBodyText(const QString &bodyText);
    void setBodyWidget(QWidget *bodyWidget);
    void setPixmap(const QPixmap &pixmap, bool autoScale);

    void maybeAddWidget(QWidget *widget);
    void maybeRemoveWidget(QWidget *widget);
    void maybeRemoveBodyWidget();

    void updateRect();
    void updateMask();
    void updateCloseButtonPosition();

    void _q_resized();
    void _q_setupCloseButtonPosition();
    void _q_closeButtonClicked();

    QRect rect;

    QLabel *titleLabel;
    QLabel *bodyTextLabel;
    QWidget *bodyWidget;
    QPixmap pixmap;
    QVBoxLayout *bodyLayout;
    QLabel *pixmapLabel;
    QOSDNotificationCloseButton *closeButton;
    QBrush backgroundBrush;
    QBrush backgroundHoverBrush;
    QColor backgroundColor;
    QColor backgroundHoverColor;
    QPen borderPen;
    QPen borderHoverPen;
    QColor borderColor;
    QColor borderHoverColor;
    QColor titleColor;
    QColor bodyTextColor;
    qreal borderWidth;
    qreal borderRadius;
    qreal opacity;
    qreal hoverOpacity;
    bool closeButtonVisible;
};

#endif // QOSDNOTIFICATION_P_H
