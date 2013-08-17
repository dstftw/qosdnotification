//#define QOSDNOTIFICATIONMANAGER_DEBUG

#ifdef QOSDNOTIFICATIONMANAGER_DEBUG
#include <QDebug>
#endif

#include <QApplication>
#include <QDesktopWidget>

#include "qosdnotificationmanager.h"
#include "qosdnotificationmanager_p.h"

#include "qabstractosdnotification.h"
#include "qosdnotification.h"

QOSDNotificationManager::QOSDNotificationManager(QObject *parent) :
    QObject(parent),
    d_ptr(new QOSDNotificationManagerPrivate(this))
{
}

QOSDNotificationManager::QOSDNotificationManager(const QWidget *widget, QObject *parent) :
    QObject(parent),
    d_ptr(new QOSDNotificationManagerPrivate(this))
{
    d_func()->mainWidget = widget;
}

QOSDNotificationManager::~QOSDNotificationManager()
{
    clear();
}

QOSDNotification *QOSDNotificationManager::add(const QString &title, const QString &bodyText, const QPixmap &pixmap, bool pixmapAutoScale)
{
    Q_D(QOSDNotificationManager);
    QOSDNotification *notification = new QOSDNotification(title, bodyText, pixmap, pixmapAutoScale);
    notification->setDuration(d->defaultDuration);
    notification->setDeleteLaterWhenFinished(true);
    add(notification);
    return notification;
}

QOSDNotification *QOSDNotificationManager::add(const QString &title, QWidget *bodyWidget, const QPixmap &pixmap, bool pixmapAutoScale)
{
    Q_D(QOSDNotificationManager);
    QOSDNotification *notification = new QOSDNotification(title, bodyWidget, pixmap, pixmapAutoScale);
    notification->setDuration(d->defaultDuration);
    notification->setDeleteLaterWhenFinished(true);
    add(notification);
    return notification;
}

void QOSDNotificationManager::add(QAbstractOSDNotification *notification)
{
    d_func()->addNotification(notification);
#ifdef QOSDNOTIFICATIONMANAGER_DEBUG
    qDebug() << "QOSDNotificationManager::add(), count =" << count();
#endif
}

void QOSDNotificationManager::remove(QAbstractOSDNotification *notification)
{
    d_func()->removeNotification(notification);
#ifdef QOSDNOTIFICATIONMANAGER_DEBUG
    qDebug() << "QOSDNotificationManager::remove(), count =" << count();
#endif
}

void QOSDNotificationManager::clear()
{
    Q_D(QOSDNotificationManager);
    foreach (QAbstractOSDNotification *notification, d->notifications) {
        if (notification->deleteLaterWhenFinished())
            notification->deleteLater();
    }
    d->notifications.clear();
}

int QOSDNotificationManager::count() const
{
    return d_func()->notifications.count();
}

int QOSDNotificationManager::maxCount() const
{
    return d_func()->maxCount;
}

void QOSDNotificationManager::setMaxCount(int maxCount)
{
    Q_D(QOSDNotificationManager);
    if (d->maxCount != maxCount) {
        d->maxCount = maxCount;
        if (maxCount > 0) {
            while (count() > maxCount)
                d->removeNotification(d->notifications.first());
        }
    }
}

Qt::Corner QOSDNotificationManager::position() const
{
    return d_func()->notificationPosition;
}

void QOSDNotificationManager::setPosition(Qt::Corner position)
{
    Q_D(QOSDNotificationManager);
    if (d->notificationPosition != position) {
        d->notificationPosition = position;
        d->updateNotificationPositions();
    }
}

int QOSDNotificationManager::horizontalMargin() const
{
    return d_func()->horizontalMargin;
}

void QOSDNotificationManager::setHorizontalMargin(int margin)
{
    Q_D(QOSDNotificationManager);
    if (d->horizontalMargin != margin) {
        d->horizontalMargin = margin;
        d->updateNotificationPositions();
    }
}

int QOSDNotificationManager::verticalMargin() const
{
    return d_func()->verticalMargin;
}

void QOSDNotificationManager::setVerticalMargin(int margin)
{
    Q_D(QOSDNotificationManager);
    if (d->verticalMargin != margin) {
        d->verticalMargin = margin;
        d->updateNotificationPositions();
    }
}

int QOSDNotificationManager::spacing() const
{
    return d_func()->spacing;
}

void QOSDNotificationManager::setSpacing(int spacing)
{
    Q_D(QOSDNotificationManager);
    if (d->spacing != spacing) {
        d->spacing = spacing;
        d->updateNotificationPositions();
    }
}

int QOSDNotificationManager::defaultDuration() const
{
    return d_func()->defaultDuration;
}

void QOSDNotificationManager::setDefaultDuration(int defaultDuration)
{
    Q_D(QOSDNotificationManager);
    if (d->defaultDuration != defaultDuration)
        d->defaultDuration = defaultDuration;
}

QSize QOSDNotificationManager::minimumNotificationSize() const
{
    Q_D(const QOSDNotificationManager);
    return QSize(d->minimumNotificationWidth, d->minimumNotificationHeight);
}

void QOSDNotificationManager::setMinimumNotificationSize(const QSize &size)
{
    Q_D(QOSDNotificationManager);
    int width = size.width();
    int height = size.height();
    if (d->minimumNotificationWidth != width)
        d->minimumNotificationWidth = width;
    if (d->minimumNotificationHeight != height)
        d->minimumNotificationHeight = height;
    if (d->minimumNotificationWidth != width || d->minimumNotificationHeight != height) {
        d->updateNotificationSizes();
    }
}

QSize QOSDNotificationManager::maximumNotificationSize() const
{
    Q_D(const QOSDNotificationManager);
    return QSize(d->maximumNotificationWidth, d->maximumNotificationHeight);
}

void QOSDNotificationManager::setMaximumNotificationSize(const QSize &size)
{
    Q_D(QOSDNotificationManager);
    int width = size.width();
    int height = size.height();
    if (d->maximumNotificationWidth != width)
        d->maximumNotificationWidth = width;
    if (d->maximumNotificationHeight != height)
        d->maximumNotificationHeight = height;
    if (d->maximumNotificationWidth != width || d->maximumNotificationHeight != height) {
        d->updateNotificationSizes();
    }
}

int QOSDNotificationManager::minimumNotificationWidth() const
{
    return d_func()->minimumNotificationWidth;
}

void QOSDNotificationManager::setMinimumNotificationWidth(int width)
{
    Q_D(QOSDNotificationManager);
    if (d->minimumNotificationWidth != width) {
        d->minimumNotificationWidth = width;
        d->updateNotificationSizes();
    }
}

int QOSDNotificationManager::minimumNotificationHeight() const
{
    return d_func()->minimumNotificationHeight;
}

void QOSDNotificationManager::setMinimumNotificationHeight(int height)
{
    Q_D(QOSDNotificationManager);
    if (d->minimumNotificationHeight != height) {
        d->minimumNotificationHeight = height;
        d->updateNotificationSizes();
    }
}

int QOSDNotificationManager::maximumNotificationWidth() const
{
    return d_func()->maximumNotificationWidth;
}

void QOSDNotificationManager::setMaximumNotificationWidth(int width)
{
    Q_D(QOSDNotificationManager);
    if (d->maximumNotificationWidth != width) {
        d->maximumNotificationWidth = width;
        d->updateNotificationSizes();
    }
}

int QOSDNotificationManager::maximumNotificationHeight() const
{
    return d_func()->maximumNotificationHeight;
}

void QOSDNotificationManager::setMaximumNotificationHeight(int height)
{
    Q_D(QOSDNotificationManager);
    if (d->maximumNotificationHeight != height) {
        d->maximumNotificationHeight = height;
        d->updateNotificationSizes();
    }
}

QOSDNotificationManagerPrivate::QOSDNotificationManagerPrivate(QOSDNotificationManager *qq)
    : q_ptr(qq),
      mainWidget(0),
      notificationPosition(Qt::BottomRightCorner),
      maxCount(5),
      horizontalMargin(5),
      verticalMargin(5),
      spacing(2),
      defaultDuration(5000),
      minimumNotificationWidth(290),
      minimumNotificationHeight(0),
      maximumNotificationWidth(QWIDGETSIZE_MAX),
      maximumNotificationHeight(QWIDGETSIZE_MAX)
{
}

QOSDNotificationManagerPrivate::~QOSDNotificationManagerPrivate()
{
}

bool QOSDNotificationManagerPrivate::isTop() const
{
    return notificationPosition == Qt::TopLeftCorner || notificationPosition == Qt::TopRightCorner;
}

bool QOSDNotificationManagerPrivate::isLeft() const
{
    return notificationPosition == Qt::TopLeftCorner || notificationPosition == Qt::BottomLeftCorner;
}

QRect QOSDNotificationManagerPrivate::availableGeometry() const
{
    QDesktopWidget *desktop = QApplication::desktop();
    return mainWidget ? desktop->availableGeometry(mainWidget) : desktop->availableGeometry();
}

int QOSDNotificationManagerPrivate::notificationsHeight() const
{
    int notificationsHeight = 0;
    if (notifications.size() > 0) {
        foreach (QAbstractOSDNotification *notification, notifications)
            notificationsHeight += notification->height();
        notificationsHeight += spacing * (notifications.size() - 1);
    }
    return notificationsHeight;
}

int QOSDNotificationManagerPrivate::verticalOffset() const
{
    int offset = verticalMargin + notificationsHeight();
    if (notifications.size() > 0)
        offset += spacing;
    return offset;
}

void QOSDNotificationManagerPrivate::updateNotificationSizes()
{
    foreach (QAbstractOSDNotification *notification, notifications) {
        notification->setMaximumSize(maximumNotificationWidth, maximumNotificationHeight);
        notification->setMinimumSize(minimumNotificationWidth, minimumNotificationHeight);
        notification->adjustSize();
    }
    //updateNotificationPositions();
}

void QOSDNotificationManagerPrivate::updateNotificationPositions()
{
#ifdef QOSDNOTIFICATIONMANAGER_DEBUG
    qDebug("QOSDNotificationManagerPrivate::updateNotificationPositions()");
#endif

    if (notifications.count() == 0)
        return;

    bool top = isTop();
    bool left = isLeft();

    QRect geometry = availableGeometry();

    int y = top ? geometry.top() + verticalMargin
                : geometry.bottom() - verticalMargin;

    foreach (QAbstractOSDNotification *notification, notifications) {
        int x = left ? geometry.left() + horizontalMargin
                     : geometry.right() - horizontalMargin - notification->width();
        if (!top)
            y -= notification->height();
        notification->move(x, y);
        if (top)
            y += spacing + notification->height();
        else
            y -= spacing;
    }
}

void QOSDNotificationManagerPrivate::setNotificationPosition(QAbstractOSDNotification *notification)
{
    bool top = isTop();
    bool left = isLeft();

    QRect geometry = availableGeometry();

    int x = left ? geometry.left() + horizontalMargin
                 : geometry.right() - horizontalMargin - notification->width();
    int y = top ? geometry.top() + verticalOffset()
                : geometry.bottom() - verticalOffset() - notification->height();

#ifdef QOSDNOTIFICATIONMANAGER_DEBUG
    qDebug("QOSDNotificationManagerPrivate::setNotificationPosition() move to (%d, %d)", x, y);
#endif

    notification->move(x, y);
}

void QOSDNotificationManagerPrivate::addNotification(QAbstractOSDNotification *notification)
{
    if (!notification)
        return;

    Q_Q(QOSDNotificationManager);

    if (notifications.contains(notification))
        return;

    // handle overflow
    if (maxCount > 0 && notifications.count() == maxCount)
        removeNotification(notifications.first());

    q->connect(notification, SIGNAL(resized()), q, SLOT(_q_notificationResized()));
    q->connect(notification, SIGNAL(finished()), q, SLOT(_q_notificationFinished()));

    if (!notification->isVisible())
        notification->show();

    notification->setMaximumSize(maximumNotificationWidth, maximumNotificationHeight);
    notification->setMinimumSize(minimumNotificationWidth, minimumNotificationHeight);

    setNotificationPosition(notification);

    notifications.append(notification);
}

void QOSDNotificationManagerPrivate::removeNotification(QAbstractOSDNotification *notification)
{
    if (!notification)
        return;

    Q_Q(QOSDNotificationManager);

    q->disconnect(notification, SIGNAL(resized()), q, SLOT(_q_notificationResized()));
    q->disconnect(notification, SIGNAL(finished()), q, SLOT(_q_notificationFinished()));

    if (notification->isVisible())
        notification->hide();

    int index = notifications.indexOf(notification);
    if (index == -1)
        return;

    int height = notification->height() + spacing;
    int dy = isTop() ? -height : height;

    notifications.removeAt(index);
    if (notification->deleteLaterWhenFinished())
        notification->deleteLater();

    for (int i = index; i < notifications.size(); ++i) {
        QAbstractOSDNotification *notification = notifications.at(i);
        int x = notification->x();
        int y = notification->y() + dy;
        notification->move(x, y);
    }

    emit q->removed(notification);
}

void QOSDNotificationManagerPrivate::_q_notificationResized()
{
#ifdef QOSDNOTIFICATIONMANAGER_DEBUG
    qDebug("QOSDNotificationManagerPrivate::_q_notificationResized()");
#endif
    updateNotificationPositions();
}

void QOSDNotificationManagerPrivate::_q_notificationFinished()
{
#ifdef QOSDNOTIFICATIONMANAGER_DEBUG
    qDebug("QOSDNotificationManagerPrivate::_q_notificationFinished()");
#endif
    Q_Q(QOSDNotificationManager);
    QAbstractOSDNotification *notification = qobject_cast<QAbstractOSDNotification *>(q->sender());
    emit q->finished(notification);
    q->remove(notification);
}

#include "moc_qosdnotificationmanager.cpp"
