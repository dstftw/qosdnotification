#ifndef QOSDNOTIFICATION_H
#define QOSDNOTIFICATION_H

#include "qabstractosdnotification.h"

#include "qosdnotification_global.h"

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class QOSDNotificationCloseButton;

class QOSDNotificationPrivate;
class QOSDNOTIFICATION_EXPORT QOSDNotification : public QAbstractOSDNotification
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString bodyText READ bodyText WRITE setBodyText)
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)
    Q_PROPERTY(QBrush backgroundBrush READ backgroundBrush WRITE setBackgroundBrush)
    Q_PROPERTY(QBrush backgroundHoverBrush READ backgroundHoverBrush WRITE setBackgroundHoverBrush)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor)
    Q_PROPERTY(QColor backgroundHoverColor READ backgroundHoverColor WRITE setBackgroundHoverColor)
    Q_PROPERTY(QPen borderPen READ borderPen WRITE setBorderPen)
    Q_PROPERTY(QPen borderHoverPen READ borderHoverPen WRITE setBorderHoverPen)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor)
    Q_PROPERTY(QColor borderHoverColor READ borderHoverColor WRITE setBorderHoverColor)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor)
    Q_PROPERTY(QColor bodyTextColor READ bodyTextColor WRITE setBodyTextColor)
    Q_PROPERTY(qreal borderWidth READ borderWidth WRITE setBorderWidth)
    Q_PROPERTY(qreal borderRadius READ borderRadius WRITE setBorderRadius)
    Q_PROPERTY(qreal opacity READ opacity WRITE setOpacity)
    Q_PROPERTY(qreal hoverOpacity READ hoverOpacity WRITE setHoverOpacity)
    Q_PROPERTY(bool isCloseButtonVisible READ isCloseButtonVisible WRITE setCloseButtonVisible)

public:
    explicit QOSDNotification(QWidget *parent = 0);
    QOSDNotification(const QString &title, const QString &bodyText, const QPixmap &pixmap = QPixmap(), bool pixmapAutoScale = true, QWidget *parent = 0);
    QOSDNotification(const QString &title, QWidget *bodyWidget, const QPixmap &pixmap = QPixmap(), bool pixmapAutoScale = true, QWidget *parent  = 0);
    ~QOSDNotification();

    QString title() const;
    void setTitle(const QString &title);

    QString bodyText() const;
    void setBodyText(const QString &bodyText);

    QWidget *bodyWidget() const;
    void setBodyWidget(QWidget *bodyWidget);

    QPixmap pixmap() const;
    void setPixmap(const QPixmap &pixmap, bool autoScale = true);

    QBrush backgroundBrush() const;
    void setBackgroundBrush(const QBrush &brush);

    QBrush backgroundHoverBrush() const;
    void setBackgroundHoverBrush(const QBrush &brush);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    QColor backgroundHoverColor() const;
    void setBackgroundHoverColor(const QColor &color);

    QPen borderPen() const;
    void setBorderPen(const QPen &pen);

    QPen borderHoverPen() const;
    void setBorderHoverPen(const QPen &pen);

    QColor borderColor() const;
    void setBorderColor(const QColor &color);

    QColor borderHoverColor() const;
    void setBorderHoverColor(const QColor &color);

    QColor titleColor() const;
    void setTitleColor(const QColor &color);

    QColor bodyTextColor() const;
    void setBodyTextColor(const QColor &color);

    qreal borderWidth() const;
    void setBorderWidth(qreal width);

    qreal borderRadius() const;
    void setBorderRadius(qreal radius);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    qreal hoverOpacity() const;
    void setHoverOpacity(qreal opacity);

    bool isCloseButtonVisible() const;
    void setCloseButtonVisible(bool closeButtonVisible);

    QLabel *titleLabel() const;
    QLabel *bodyTextLabel() const;
    QOSDNotificationCloseButton *closeButton() const;

public Q_SLOTS:
    void close();

protected:
    QOSDNotification(QOSDNotificationPrivate &dd, QWidget *parent, Qt::WindowFlags f);

    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

private:
    Q_DECLARE_PRIVATE(QOSDNotification)
    Q_DISABLE_COPY(QOSDNotification)
    Q_PRIVATE_SLOT(d_func(), void _q_resized())
    Q_PRIVATE_SLOT(d_func(), void _q_setupCloseButtonPosition())
};

#endif // QOSDNOTIFICATION_H
