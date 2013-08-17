#ifndef QOSDNOTIFICATIONCLOSEBUTTON_H
#define QOSDNOTIFICATIONCLOSEBUTTON_H

#include <QWidget>

#include "qosdnotification_global.h"

class QOSDNotificationCloseButtonPrivate;
class QOSDNOTIFICATION_EXPORT QOSDNotificationCloseButton : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor)
    Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal hoverOpacity READ hoverOpacity WRITE setHoverOpacity)

public:
    explicit QOSDNotificationCloseButton(QWidget *parent = 0);
    virtual ~QOSDNotificationCloseButton();

    QColor color() const;
    void setColor(const QColor &color);

    QColor hoverColor() const;
    void setHoverColor(const QColor &color);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    qreal hoverOpacity() const;
    void setHoverOpacity(qreal hoverOpacity);

Q_SIGNALS:
    void pressed();
    void released();
    void clicked();

protected:
    QScopedPointer<QOSDNotificationCloseButtonPrivate> d_ptr;

    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:
    Q_DECLARE_PRIVATE(QOSDNotificationCloseButton)
    Q_DISABLE_COPY(QOSDNotificationCloseButton)
};

#endif // QOSDNOTIFICATIONCLOSEBUTTON_H
