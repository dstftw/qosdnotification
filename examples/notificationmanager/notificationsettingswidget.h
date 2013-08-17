#ifndef NOTIFICATIONSETTINGSWIDGET_H
#define NOTIFICATIONSETTINGSWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QPlainTextEdit;
class QSpinBox;
class QDoubleSpinBox;
QT_END_NAMESPACE

class IconWidget;
class ColorWidget;

class QOSDNotification;

struct OSDNotificationData;

class NotificationSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationSettingsWidget(QWidget *parent = 0);

    void setNotificationData(const OSDNotificationData *notificationData);

    void writeSettings(QOSDNotification *notification);

    QString title() const;
    void setTitle(const QString &title);

    QColor titleColor() const;
    void setTitleColor(const QColor &color);

    QString bodyText() const;
    void setBodyText(const QString &bodyText);

    QColor bodyTextColor() const;
    void setBodyTextColor(const QColor &color);

    QPixmap icon() const;
    void setIcon(const QPixmap &icon);

    bool iconAutoScale() const;
    void setIconAutoScale(bool autoScale);

    QColor backgroundColor() const;
    void setBackgroundColor(const QColor &color);

    QColor backgroundHoverColor() const;
    void setBackgroundHoverColor(const QColor &color);

    QColor borderColor() const;
    void setBorderColor(const QColor &color);

    QColor borderHoverColor() const;
    void setBorderHoverColor(const QColor &color);

    qreal borderWidth() const;
    void setBorderWidth(qreal width);

    qreal borderRadius() const;
    void setBorderRadius(qreal radius);

    int duration() const;
    void setDuration(int duration);

    qreal opacity() const;
    void setOpacity(qreal opacity);

    qreal hoverOpacity() const;
    void setHoverOpacity(qreal opacity);

    bool isCloseButtonVisible() const;
    void setCloseButtonVisible(bool visible);

signals:
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

private slots:
    void titleChanged();
    void bodyTextChanged();

private:
    QSpinBox *durationSpinBox;
    QPlainTextEdit *titlePlainTextEdit;
    QPlainTextEdit *bodyTextPlainTextEdit;
    IconWidget *iconWidget;
    ColorWidget *backgroundColorWidget;
    ColorWidget *backgroundHoverColorWidget;
    ColorWidget *borderColorWidget;
    ColorWidget *borderHoverColorWidget;
    ColorWidget *titleColorWidget;
    ColorWidget *bodyTextColorWidget;
    QDoubleSpinBox *borderWidthSpinBox;
    QDoubleSpinBox *borderRadiusSpinBox;
    QDoubleSpinBox *opacitySpinBox;
    QDoubleSpinBox *hoverOpacitySpinBox;
    QCheckBox *closeButtonCheckBox;
};

#endif // NOTIFICATIONSETTINGSWIDGET_H
