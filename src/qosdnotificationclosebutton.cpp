#include <QPainter>

#include "qosdnotificationclosebutton.h"
#include "qosdnotificationclosebutton_p.h"

QOSDNotificationCloseButton::QOSDNotificationCloseButton(QWidget *parent) :
    QWidget(parent),
    d_ptr(new QOSDNotificationCloseButtonPrivate)
{
    resize(10, 10);
}

QOSDNotificationCloseButton::~QOSDNotificationCloseButton()
{
}

QColor QOSDNotificationCloseButton::color() const
{
    return d_func()->color;
}

void QOSDNotificationCloseButton::setColor(const QColor &color)
{
    Q_D(QOSDNotificationCloseButton);
    if (d->color != color)
        d->color = color;
}

QColor QOSDNotificationCloseButton::hoverColor() const
{
    return d_func()->hoverColor;
}

void QOSDNotificationCloseButton::setHoverColor(const QColor &color)
{
    Q_D(QOSDNotificationCloseButton);
    if (d->hoverColor != color)
        d->hoverColor = color;
}

qreal QOSDNotificationCloseButton::opacity() const
{
    return d_func()->opacity;
}

void QOSDNotificationCloseButton::setOpacity(qreal opacity)
{
    Q_D(QOSDNotificationCloseButton);
    if (d->opacity != opacity)
        d->opacity = opacity;
}

qreal QOSDNotificationCloseButton::hoverOpacity() const
{
    return d_func()->hoverOpacity;
}

void QOSDNotificationCloseButton::setHoverOpacity(qreal hoverOpacity)
{
    Q_D(QOSDNotificationCloseButton);
    if (d->hoverOpacity != hoverOpacity)
        d->hoverOpacity = hoverOpacity;
}

void QOSDNotificationCloseButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    Q_D(QOSDNotificationCloseButton);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(d->hovered ? d->hoverColor : d->color, 3));
    p.setOpacity(d->hovered ? d->hoverOpacity : d->opacity);
    p.drawLine(0, 0, width(), height());
    p.drawLine(0, height(), width(), 0);
}

void QOSDNotificationCloseButton::enterEvent(QEvent *event)
{
    QWidget::enterEvent(event);
    d_func()->hovered = true;
    update();
}

void QOSDNotificationCloseButton::leaveEvent(QEvent *event)
{
    QWidget::leaveEvent(event);
    d_func()->hovered = false;
    update();
}

void QOSDNotificationCloseButton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit pressed();
}

void QOSDNotificationCloseButton::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit released();
    emit clicked();
}

QOSDNotificationCloseButtonPrivate::QOSDNotificationCloseButtonPrivate() :
    color(Qt::white),
    hoverColor(QColor("#eaeaea")),
    opacity(1.0),
    hoverOpacity(1.0),
    hovered(false)
{
}

QOSDNotificationCloseButtonPrivate::~QOSDNotificationCloseButtonPrivate()
{
}
