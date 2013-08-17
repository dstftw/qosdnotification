#include <QMouseEvent>
#include <QTimer>

#include "qabstractosdnotification.h"
#include "qabstractosdnotification_p.h"

QAbstractOSDNotification::QAbstractOSDNotification(QWidget *parent) :
    QWidget(parent),
    d_ptr(new QAbstractOSDNotificationPrivate)
{
    d_func()->init(this);
}

QAbstractOSDNotification::QAbstractOSDNotification(QAbstractOSDNotificationPrivate &dd, QWidget *parent, Qt::WindowFlags f) :
    QWidget(parent, f),
    d_ptr(&dd)
{
    d_func()->init(this);
}

QAbstractOSDNotification::~QAbstractOSDNotification()
{
}

bool QAbstractOSDNotification::deleteLaterWhenFinished() const
{
    return d_func()->deleteLater;
}

void QAbstractOSDNotification::setDeleteLaterWhenFinished(bool deleteLater)
{
    Q_D(QAbstractOSDNotification);
    if (d->deleteLater != deleteLater)
        d->deleteLater = deleteLater;
}

int QAbstractOSDNotification::duration() const
{
    return d_func()->duration;
}

void QAbstractOSDNotification::setDuration(int duration)
{
    Q_D(QAbstractOSDNotification);
    if (d->duration != duration) {
        d->duration = duration;
        if (d->durationTimer.isActive())
            d->restartDurationTimer();
    }
}

bool QAbstractOSDNotification::isHovered() const
{
    return d_func()->hovered;
}

void QAbstractOSDNotification::show()
{
    emit aboutToShow();
    QWidget::show();
    emit shown();
    d_func()->restartDurationTimer();
}

void QAbstractOSDNotification::hide()
{
    emit aboutToHide();
    QWidget::hide();
    emit hidden();
    d_func()->durationTimer.stop();
}

void QAbstractOSDNotification::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    Q_D(QAbstractOSDNotification);
    d->durationTimer.stop();
    d->hovered = true;
    emit hovered();
}

void QAbstractOSDNotification::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    Q_D(QAbstractOSDNotification);
    d->restartDurationTimer();
    d->hovered = false;
    emit unhovered();
}

void QAbstractOSDNotification::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        emit activated();
}

void QAbstractOSDNotification::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    emit resized();
}

QAbstractOSDNotificationPrivate::QAbstractOSDNotificationPrivate()
    : deleteLater(false),
      duration(5000),
      hovered(false)
{
}

QAbstractOSDNotificationPrivate::~QAbstractOSDNotificationPrivate()
{
}

void QAbstractOSDNotificationPrivate::init(QAbstractOSDNotification *q)
{
    q_ptr = q;

    q->setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);

    q->setAttribute(Qt::WA_TranslucentBackground);
    q->setAttribute(Qt::WA_NoSystemBackground);
    q->setAttribute(Qt::WA_X11NetWmWindowTypeNotification);
    q->setAttribute(Qt::WA_ShowWithoutActivating);

    durationTimer.setSingleShot(true);
    q->connect(&durationTimer, SIGNAL(timeout()), q, SLOT(_q_durationTimeout()));

    q->connect(q, SIGNAL(closed()), SIGNAL(finished()));
    q->connect(q, SIGNAL(timeout()), SIGNAL(finished()));
}

void QAbstractOSDNotificationPrivate::restartDurationTimer()
{
    if (duration > 0)
        durationTimer.start(duration);
}

void QAbstractOSDNotificationPrivate::_q_durationTimeout()
{
    Q_Q(QAbstractOSDNotification);
    q->hide();
    emit q->timeout();
}

#include "moc_qabstractosdnotification.cpp"
