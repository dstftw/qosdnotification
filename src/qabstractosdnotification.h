#ifndef QABSTRACTOSDNOTIFICATION_H
#define QABSTRACTOSDNOTIFICATION_H

#include <QWidget>

#include "qosdnotification_global.h"

class QAbstractOSDNotificationPrivate;
class QOSDNOTIFICATION_EXPORT QAbstractOSDNotification : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool deleteLaterWhenFinished READ deleteLaterWhenFinished WRITE setDeleteLaterWhenFinished)
    Q_PROPERTY(bool isHovered READ isHovered)
    Q_PROPERTY(int duration READ duration WRITE setDuration)

public:
    virtual ~QAbstractOSDNotification();

    bool deleteLaterWhenFinished() const;
    void setDeleteLaterWhenFinished(bool deleteLater);

    bool isHovered() const;

    int duration() const;
    void setDuration(int duration);

public Q_SLOTS:
    void show();
    void hide();

Q_SIGNALS:
    void aboutToShow();
    void shown();
    void aboutToHide();
    void hidden();
    void hovered();
    void unhovered();
    void activated();
    void closed();
    void timeout();
    void finished();
    void resized();

protected:
    explicit QAbstractOSDNotification(QWidget *parent = 0);
    QAbstractOSDNotification(QAbstractOSDNotificationPrivate &dd, QWidget *parent, Qt::WindowFlags f);
    QScopedPointer<QAbstractOSDNotificationPrivate> d_ptr;

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    Q_DECLARE_PRIVATE(QAbstractOSDNotification)
    Q_DISABLE_COPY(QAbstractOSDNotification)
    Q_PRIVATE_SLOT(d_func(), void _q_durationTimeout())
};

#endif // QABSTRACTOSDNOTIFICATION_H
