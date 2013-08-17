#ifndef QOSDNOTIFICATIONMANAGER_H
#define QOSDNOTIFICATIONMANAGER_H

#include <QObject>
#include <QPixmap>

#include "qosdnotification_global.h"

class QAbstractOSDNotification;
class QOSDNotification;

class QOSDNotificationManagerPrivate;
class QOSDNOTIFICATION_EXPORT QOSDNotificationManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(int maxCount READ maxCount WRITE setMaxCount)
    Q_PROPERTY(Qt::Corner position READ position WRITE setPosition)
    Q_PROPERTY(int horizontalMargin READ horizontalMargin WRITE setHorizontalMargin)
    Q_PROPERTY(int verticalMargin READ verticalMargin WRITE setVerticalMargin)
    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(int defaultDuration READ defaultDuration WRITE setDefaultDuration)
    Q_PROPERTY(QSize minimumNotificationSize READ minimumNotificationSize WRITE setMinimumNotificationSize)
    Q_PROPERTY(QSize maximumNotificationSize READ maximumNotificationSize WRITE setMaximumNotificationSize)
    Q_PROPERTY(int minimumNotificationWidth READ minimumNotificationWidth WRITE setMinimumNotificationWidth)
    Q_PROPERTY(int minimumNotificationHeight READ minimumNotificationHeight WRITE setMinimumNotificationHeight)
    Q_PROPERTY(int maximumNotificationWidth READ maximumNotificationWidth WRITE setMaximumNotificationWidth)
    Q_PROPERTY(int maximumNotificationHeight READ maximumNotificationHeight WRITE setMaximumNotificationHeight)

public:
    explicit QOSDNotificationManager(QObject *parent = 0);
    QOSDNotificationManager(const QWidget *widget, QObject *parent = 0);
    virtual ~QOSDNotificationManager();

    QOSDNotification *add(const QString &title, const QString &bodyText, const QPixmap &pixmap = QPixmap(), bool pixmapAutoScale = true);
    QOSDNotification *add(const QString &title, QWidget *bodyWidget, const QPixmap &pixmap = QPixmap(), bool pixmapAutoScale = true);

    void add(QAbstractOSDNotification *notification);
    void remove(QAbstractOSDNotification *notification);

    void clear();

    int count() const;

    int maxCount() const;
    void setMaxCount(int maxCount);

    Qt::Corner position() const;
    void setPosition(Qt::Corner position);

    int horizontalMargin() const;
    void setHorizontalMargin(int margin);

    int verticalMargin() const;
    void setVerticalMargin(int margin);

    int spacing() const;
    void setSpacing(int spacing);

    int defaultDuration() const;
    void setDefaultDuration(int defaultDuration);

    QSize minimumNotificationSize() const;
    void setMinimumNotificationSize(const QSize &size);

    QSize maximumNotificationSize() const;
    void setMaximumNotificationSize(const QSize &size);

    int minimumNotificationWidth() const;
    void setMinimumNotificationWidth(int width);

    int minimumNotificationHeight() const;
    void setMinimumNotificationHeight(int height);

    int maximumNotificationWidth() const;
    void setMaximumNotificationWidth(int width);

    int maximumNotificationHeight() const;
    void setMaximumNotificationHeight(int height);

Q_SIGNALS:
    void finished(QAbstractOSDNotification *notification);
    void removed(QAbstractOSDNotification *notification);

protected:
    QScopedPointer<QOSDNotificationManagerPrivate> d_ptr;

private:
    Q_DECLARE_PRIVATE(QOSDNotificationManager)
    Q_DISABLE_COPY(QOSDNotificationManager)
    Q_PRIVATE_SLOT(d_func(), void _q_notificationResized())
    Q_PRIVATE_SLOT(d_func(), void _q_notificationFinished())
};

#endif // QOSDNOTIFICATIONMANAGER_H
