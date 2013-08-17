#ifndef NOTIFICATIONMANAGERSETTINGSWIDGET_H
#define NOTIFICATIONMANAGERSETTINGSWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSpinBox;
class QComboBox;
QT_END_NAMESPACE

class QOSDNotificationManager;

class NotificationManagerSettingsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NotificationManagerSettingsWidget(QWidget *parent = 0);

    void setManager(QOSDNotificationManager *manager);

    int horizontalMargin() const;
    void setHorizontalMargin(int margin);

    int verticalMargin() const;
    void setVerticalMargin(int margin);

    int spacing() const;
    void setSpacing(int spacing);

    int minimumNotificationWidth() const;
    void setMinimumNotificationWidth(int width);

    int minimumNotificationHeight() const;
    void setMinimumNotificationHeight(int height);

    int maximumNotificationWidth() const;
    void setMaximumNotificationWidth(int width);

    int maximumNotificationHeight() const;
    void setMaximumNotificationHeight(int height);

    int maxCount() const;
    void setMaxCount(int maxCount);

    Qt::Corner position() const;
    void setPosition(Qt::Corner position);

signals:
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
    
private:
    QSpinBox *horizontalMarginSpinBox;
    QSpinBox *verticalMarginSpinBox;
    QSpinBox *spacingSpinBox;
    QSpinBox *minimumNotificationWidthSpinBox;
    QSpinBox *minimumNotificationHeightSpinBox;
    QSpinBox *maximumNotificationWidthSpinBox;
    QSpinBox *maximumNotificationHeightSpinBox;
    QSpinBox *maxCountSpinBox;
    QComboBox *positionComboBox;
};

#endif // NOTIFICATIONMANAGERSETTINGSWIDGET_H
