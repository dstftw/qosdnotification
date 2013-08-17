#include <QAction>
#include <QIcon>
#include <QListWidget>
#include <QToolButton>
#include <QHBoxLayout>
#include <QGroupBox>

#include <QOSDNotificationManager>
#include <QOSDNotification>

#include "notificationmanager.h"
#include "notificationmanagersettingswidget.h"
#include "notificationsettingswidget.h"

NotificationManager::NotificationManager(QWidget *parent)
    : QWidget(parent),
      manager(new QOSDNotificationManager(this)),
      currentNotification(0),
      currentNotificationData(&newNotificationData)
{
    addNotificationAction = new QAction(QIcon::fromTheme("list-add"), tr("&Add"), this);
    addNotificationAction->setStatusTip(tr("Add notification"));
    connect(addNotificationAction, SIGNAL(triggered()), this, SLOT(addNotification()));

    removeNotificationAction = new QAction(QIcon::fromTheme("list-remove"), tr("&Remove"), this);
    removeNotificationAction->setStatusTip(tr("Remove notification"));
    connect(removeNotificationAction, SIGNAL(triggered()), this, SLOT(removeNotification()));

    clearNotificationsAction = new QAction(QIcon::fromTheme("edit-clear"), tr("&Clear"), this);
    clearNotificationsAction->setStatusTip(tr("Clear notifications"));
    connect(clearNotificationsAction, SIGNAL(triggered()), this, SLOT(clearNotifications()));

    notificationManagerSettingsWidget = new NotificationManagerSettingsWidget;
    notificationManagerSettingsWidget->setManager(manager);

    connect(notificationManagerSettingsWidget, SIGNAL(horizontalMarginChanged(int)), this, SLOT(horizontalMarginChanged(int)));
    connect(notificationManagerSettingsWidget, SIGNAL(verticalMarginChanged(int)), this, SLOT(verticalMarginChanged(int)));
    connect(notificationManagerSettingsWidget, SIGNAL(spacingChanged(int)), this, SLOT(spacingChanged(int)));
    connect(notificationManagerSettingsWidget, SIGNAL(minimumNotificationWidthChanged(int)), this, SLOT(minimumNotificationWidthChanged(int)));
    connect(notificationManagerSettingsWidget, SIGNAL(minimumNotificationHeightChanged(int)), this, SLOT(minimumNotificationHeightChanged(int)));
    connect(notificationManagerSettingsWidget, SIGNAL(maximumNotificationWidthChanged(int)), this, SLOT(maximumNotificationWidthChanged(int)));
    connect(notificationManagerSettingsWidget, SIGNAL(maximumNotificationHeightChanged(int)), this, SLOT(maximumNotificationHeightChanged(int)));
    connect(notificationManagerSettingsWidget, SIGNAL(maxCountChanged(int)), this, SLOT(maxCountChanged(int)));
    connect(notificationManagerSettingsWidget, SIGNAL(positionChanged(int)), this, SLOT(positionChanged(int)));
    connect(notificationManagerSettingsWidget, SIGNAL(defaultSpacingChanged(int)), this, SLOT(defaultSpacingChanged(int)));

    notificationsListWidget = new QListWidget;
    notificationDatas.append(currentNotificationData);
    notifications.append(0);
    notificationsListWidget->addItem(tr("<new notification>"));

    notificationSettingsWidget = new NotificationSettingsWidget;

    addNotificationButton = new QToolButton;
    addNotificationButton->setDefaultAction(addNotificationAction);
    addNotificationButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    removeNotificationButton = new QToolButton;
    removeNotificationButton->setDefaultAction(removeNotificationAction);
    removeNotificationButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    clearNotificationsButton = new QToolButton;
    clearNotificationsButton->setDefaultAction(clearNotificationsAction);
    clearNotificationsButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    connect(notificationSettingsWidget, SIGNAL(titleChanged(QString)), this, SLOT(titleChanged(QString)));
    connect(notificationSettingsWidget, SIGNAL(titleColorChanged(QColor)), this, SLOT(titleColorChanged(QColor)));
    connect(notificationSettingsWidget, SIGNAL(bodyTextChanged(QString)), this, SLOT(bodyTextChanged(QString)));
    connect(notificationSettingsWidget, SIGNAL(bodyTextColorChanged(QColor)), this, SLOT(bodyTextColorChanged(QColor)));
    connect(notificationSettingsWidget, SIGNAL(iconChanged(QPixmap)), this, SLOT(iconChanged(QPixmap)));
    connect(notificationSettingsWidget, SIGNAL(iconAutoScaleChanged(bool)), this, SLOT(iconAutoScaleChanged(bool)));
    connect(notificationSettingsWidget, SIGNAL(backgroundColorChanged(QColor)), this, SLOT(backgroundColorChanged(QColor)));
    connect(notificationSettingsWidget, SIGNAL(backgroundHoverColorChanged(QColor)), this, SLOT(backgroundHoverColorChanged(QColor)));
    connect(notificationSettingsWidget, SIGNAL(borderColorChanged(QColor)), this, SLOT(borderColorChanged(QColor)));
    connect(notificationSettingsWidget, SIGNAL(borderHoverColorChanged(QColor)), this, SLOT(borderHoverColorChanged(QColor)));
    connect(notificationSettingsWidget, SIGNAL(borderWidthChanged(qreal)), this, SLOT(borderWidthChanged(qreal)));
    connect(notificationSettingsWidget, SIGNAL(borderRadiusChanged(qreal)), this, SLOT(borderRadiusChanged(qreal)));
    connect(notificationSettingsWidget, SIGNAL(durationChanged(int)), this, SLOT(durationChanged(int)));
    connect(notificationSettingsWidget, SIGNAL(opacityChanged(qreal)), this, SLOT(opacityChanged(qreal)));
    connect(notificationSettingsWidget, SIGNAL(hoverOpacityChanged(qreal)), this, SLOT(hoverOpacityChanged(qreal)));
    connect(notificationSettingsWidget, SIGNAL(closeButtonVisibleChanged(bool)), this, SLOT(closeButtonVisibleChanged(bool)));
    connect(notificationsListWidget, SIGNAL(currentRowChanged(int)), this, SLOT(currentNotificationChanged(int)));

    connect(manager, SIGNAL(removed(QAbstractOSDNotification*)), this, SLOT(notificationRemoved(QAbstractOSDNotification*)));

    QHBoxLayout *managerLayout = new QHBoxLayout;
    managerLayout->setContentsMargins(0, 0, 0, 0);
    managerLayout->addWidget(notificationManagerSettingsWidget);

    QGroupBox *managerGroupBox = new QGroupBox(tr("Notification manager"));
    managerGroupBox->setLayout(managerLayout);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(addNotificationButton);
    buttonsLayout->addWidget(removeNotificationButton);
    buttonsLayout->addWidget(clearNotificationsButton);

    QHBoxLayout *notificationsLayout = new QHBoxLayout;
    notificationsLayout->addWidget(notificationsListWidget);
    notificationsLayout->addWidget(notificationSettingsWidget);
    notificationSettingsWidget->layout()->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *notificationLayout = new QVBoxLayout;
    notificationLayout->addLayout(notificationsLayout);
    notificationLayout->addLayout(buttonsLayout);

    QGroupBox *notificationGroupBox = new QGroupBox(tr("Notifications"));
    notificationGroupBox->setLayout(notificationLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(managerGroupBox);
    mainLayout->addWidget(notificationGroupBox);

    setLayout(mainLayout);

    setWindowTitle(tr("Notification manager"));

    loadSettingsForCurrentNotification();

    notificationsListWidget->setCurrentRow(0);
}

int NotificationManager::notificationCount() const
{
    return manager->count();
}

void NotificationManager::closeEvent(QCloseEvent *event)
{
    clearNotifications();
    QWidget::closeEvent(event);
}

void NotificationManager::horizontalMarginChanged(int value)
{
    manager->setHorizontalMargin(value);
}

void NotificationManager::verticalMarginChanged(int value)
{
    manager->setVerticalMargin(value);
}

void NotificationManager::spacingChanged(int value)
{
    manager->setSpacing(value);
}

void NotificationManager::minimumNotificationWidthChanged(int value)
{
    manager->setMinimumNotificationWidth(value);
}

void NotificationManager::minimumNotificationHeightChanged(int value)
{
    manager->setMinimumNotificationHeight(value);
}

void NotificationManager::maximumNotificationWidthChanged(int value)
{
    manager->setMaximumNotificationWidth(value);
}

void NotificationManager::maximumNotificationHeightChanged(int value)
{
    manager->setMaximumNotificationHeight(value);
}

void NotificationManager::maxCountChanged(int value)
{
    manager->setMaxCount(value);
}

void NotificationManager::positionChanged(int value)
{
    manager->setPosition(static_cast<Qt::Corner>(value));
}

void NotificationManager::defaultSpacingChanged(int value)
{
    manager->setDefaultDuration(value);
}

void NotificationManager::titleChanged(const QString &value)
{
    currentNotificationData->title = value;
    if (currentNotification) {
        currentNotification->setTitle(value);
        int index = notifications.indexOf(currentNotification);
        if (index != -1) {
            QListWidgetItem *item = notificationsListWidget->item(index);
            if (item)
                item->setText(value);
        }
    }
}

void NotificationManager::titleColorChanged(const QColor &value)
{
    currentNotificationData->titleColor = value;
    if (currentNotification)
        currentNotification->setTitleColor(value);
}

void NotificationManager::bodyTextChanged(const QString &value)
{
    currentNotificationData->bodyText = value;
    if (currentNotification)
        currentNotification->setBodyText(value);
}

void NotificationManager::bodyTextColorChanged(const QColor &value)
{
    currentNotificationData->bodyTextColor = value;
    if (currentNotification)
        currentNotification->setBodyTextColor(value);
}

void NotificationManager::iconChanged(const QPixmap &value)
{
    currentNotificationData->icon = value;
    if (currentNotification)
        currentNotification->setPixmap(value, notificationSettingsWidget->iconAutoScale());
}

void NotificationManager::iconAutoScaleChanged(bool value)
{
    currentNotificationData->iconAutoScale = value;
    if (currentNotification)
        currentNotification->setPixmap(notificationSettingsWidget->icon(), value);
}

void NotificationManager::backgroundColorChanged(const QColor &value)
{
    currentNotificationData->backgroundColor = value;
    if (currentNotification)
        currentNotification->setBackgroundColor(value);
}

void NotificationManager::backgroundHoverColorChanged(const QColor &value)
{
    currentNotificationData->backgroundHoverColor = value;
    if (currentNotification)
        currentNotification->setBackgroundHoverColor(value);
}

void NotificationManager::borderColorChanged(const QColor &value)
{
    currentNotificationData->borderColor = value;
    if (currentNotification)
        currentNotification->setBorderColor(value);
}

void NotificationManager::borderHoverColorChanged(const QColor &value)
{
    currentNotificationData->borderHoverColor = value;
    if (currentNotification)
        currentNotification->setBorderHoverColor(value);
}

void NotificationManager::borderWidthChanged(qreal value)
{
    currentNotificationData->borderWidth = value;
    if (currentNotification)
        currentNotification->setBorderWidth(value);
}

void NotificationManager::borderRadiusChanged(qreal value)
{
    currentNotificationData->borderRadius = value;
    if (currentNotification)
        currentNotification->setBorderRadius(value);
}

void NotificationManager::durationChanged(int value)
{
    currentNotificationData->duration = value;
    if (currentNotification)
        currentNotification->setDuration(value);
}

void NotificationManager::opacityChanged(qreal value)
{
    currentNotificationData->opacity = value;
    if (currentNotification)
        currentNotification->setOpacity(value);
}

void NotificationManager::hoverOpacityChanged(qreal value)
{
    currentNotificationData->hoverOpacity = value;
    if (currentNotification)
        currentNotification->setHoverOpacity(value);
}

void NotificationManager::closeButtonVisibleChanged(bool value)
{
    currentNotificationData->closeButtonVisible = value;
    if (currentNotification)
        currentNotification->setCloseButtonVisible(value);
}

void NotificationManager::currentNotificationChanged(int index)
{
    if (index == -1) {
        notificationsListWidget->setCurrentRow(0);
    } else {
        addNotificationButton->setEnabled(index == 0);
        removeNotificationButton->setEnabled(index != 0);
        clearNotificationsButton->setEnabled(notificationCount());
        currentNotificationData = notificationDatas.value(index);
        currentNotification = notifications.value(index);
        loadSettingsForCurrentNotification();
    }
}

void NotificationManager::addNotification()
{
    QOSDNotification *n = new QOSDNotification;
    notificationSettingsWidget->writeSettings(n);
    manager->add(n);
    notificationsListWidget->addItem(n->title());
    notificationDatas.append(new OSDNotificationData(*currentNotificationData));
    notifications.append(n);
    clearNotificationsButton->setEnabled(true);
}

void NotificationManager::removeNotification()
{
    if (currentNotification)
        manager->remove(currentNotification);
}

void NotificationManager::clearNotifications()
{
    foreach (QAbstractOSDNotification *notification, notifications)
        manager->remove(notification);
    clearNotificationsButton->setEnabled(false);
}

void NotificationManager::notificationRemoved(QAbstractOSDNotification *notification)
{
    QOSDNotification *n = qobject_cast<QOSDNotification *>(notification);
    int index = notifications.indexOf(n);
    if (index != -1) {
        delete notificationsListWidget->takeItem(index);
        delete notificationDatas.takeAt(index);
        notifications.removeAt(index);
        delete n;
    }
}

void NotificationManager::loadSettingsForCurrentNotification()
{
    notificationSettingsWidget->setNotificationData(currentNotificationData);
}
