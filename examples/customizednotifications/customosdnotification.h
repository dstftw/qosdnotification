#ifndef CUSTOMOSDNOTIFICATION_H
#define CUSTOMOSDNOTIFICATION_H

#include <QAbstractOSDNotification>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class CustomOSDNotification : public QAbstractOSDNotification
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle)
    Q_PROPERTY(QString message READ message WRITE setMessage)
    Q_PROPERTY(QPixmap pixmap READ pixmap WRITE setPixmap)

public:
    explicit CustomOSDNotification(QWidget *parent = 0);
    CustomOSDNotification(const QString &title, const QString &message, const QPixmap &pixmap = QPixmap(), QWidget *parent = 0);

    QString title() const;
    void setTitle(const QString &title);

    QString message() const;
    void setMessage(const QString &message);

    const QPixmap *pixmap() const;
    void setPixmap(const QPixmap &pixmap);

private:
    void init();

    QLabel *titleLabel;
    QLabel *messageLabel;
    QLabel *iconLabel;
};

#endif // CUSTOMOSDNOTIFICATION_H
