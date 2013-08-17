#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QListWidget;
class QToolButton;
class QAction;
QT_END_NAMESPACE

class QOSDNotificationManager;
class QAbstractOSDNotification;
class QOSDNotification;

class IconWidget;
class ColorWidget;

class NotificationManagerSettingsWidget;
class NotificationSettingsWidget;

struct OSDNotificationData
{
    OSDNotificationData() :
        title(QObject::tr("Notification's title")),
        titleColor(Qt::white),
        bodyText(QObject::tr("Notification's body text")),
        bodyTextColor(QColor("#eaeaea")),
        iconAutoScale(true),
        backgroundColor(QColor("#131313")),
        backgroundHoverColor(backgroundColor),
        borderColor(backgroundColor.darker(150)),
        borderHoverColor(borderColor),
        borderWidth(2.0),
        borderRadius(10),
        duration(5000),
        opacity(0.8),
        hoverOpacity(0.9),
        closeButtonVisible(true) {
    }

    QString title;
    QColor titleColor;
    QString bodyText;
    QColor bodyTextColor;
    QPixmap icon;
    bool iconAutoScale;
    QColor backgroundColor;
    QColor backgroundHoverColor;
    QColor borderColor;
    QColor borderHoverColor;
    qreal borderWidth;
    qreal borderRadius;
    int duration;
    qreal opacity;
    qreal hoverOpacity;
    bool closeButtonVisible;
};

class NotificationManager : public QWidget
{
    Q_OBJECT

public:
    NotificationManager(QWidget *parent = 0);

    int notificationCount() const;

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void horizontalMarginChanged(int value);
    void verticalMarginChanged(int value);
    void spacingChanged(int value);
    void minimumNotificationWidthChanged(int value);
    void minimumNotificationHeightChanged(int value);
    void maximumNotificationWidthChanged(int value);
    void maximumNotificationHeightChanged(int value);
    void maxCountChanged(int value);
    void positionChanged(int value);
    void defaultSpacingChanged(int value);

    void titleChanged(const QString &value);
    void titleColorChanged(const QColor &value);
    void bodyTextChanged(const QString &value);
    void bodyTextColorChanged(const QColor &value);
    void iconChanged(const QPixmap &value);
    void iconAutoScaleChanged(bool value);
    void backgroundColorChanged(const QColor &value);
    void backgroundHoverColorChanged(const QColor &value);
    void borderColorChanged(const QColor &value);
    void borderHoverColorChanged(const QColor &value);
    void borderWidthChanged(qreal value);
    void borderRadiusChanged(qreal value);
    void durationChanged(int value);
    void opacityChanged(qreal value);
    void hoverOpacityChanged(qreal value);
    void closeButtonVisibleChanged(bool value);

    void currentNotificationChanged(int index);
    void addNotification();
    void removeNotification();
    void clearNotifications();
    void notificationRemoved(QAbstractOSDNotification* notification);

private:
    void loadSettingsForCurrentNotification();

    QAction *addNotificationAction;
    QAction *removeNotificationAction;
    QAction *clearNotificationsAction;

    QOSDNotificationManager *manager;
    QOSDNotification *currentNotification;
    OSDNotificationData newNotificationData;
    OSDNotificationData *currentNotificationData;

    QList<OSDNotificationData *> notificationDatas;
    QList<QOSDNotification *> notifications;

    NotificationManagerSettingsWidget *notificationManagerSettingsWidget;
    NotificationSettingsWidget *notificationSettingsWidget;
    QListWidget *notificationsListWidget;

    QToolButton *addNotificationButton;
    QToolButton *removeNotificationButton;
    QToolButton *clearNotificationsButton;
};

#endif // NOTIFICATIONMANAGER_H
