#include <QFormLayout>
#include <QSpinBox>
#include <QGroupBox>
#include <QComboBox>

#include <QOSDNotificationManager>

#include "notificationmanagersettingswidget.h"

NotificationManagerSettingsWidget::NotificationManagerSettingsWidget(QWidget *parent) :
    QWidget(parent)
{
    // Margins

    horizontalMarginSpinBox = new QSpinBox;
    horizontalMarginSpinBox->setRange(0, INT_MAX);

    verticalMarginSpinBox = new QSpinBox;
    verticalMarginSpinBox->setRange(0, INT_MAX);

    spacingSpinBox = new QSpinBox;
    spacingSpinBox->setRange(0, INT_MAX);

    QFormLayout *marginsLayout = new QFormLayout;
    marginsLayout->addRow(tr("Horizontal"), horizontalMarginSpinBox);
    marginsLayout->addRow(tr("Vertical"), verticalMarginSpinBox);
    marginsLayout->addRow(tr("Spacing"), spacingSpinBox);

    QGroupBox *marginsGroupBox = new QGroupBox(tr("Margins && Spacing"));
    marginsGroupBox->setLayout(marginsLayout);

    // Size

    minimumNotificationWidthSpinBox = new QSpinBox;
    minimumNotificationWidthSpinBox->setRange(0, QWIDGETSIZE_MAX);

    minimumNotificationHeightSpinBox = new QSpinBox;
    minimumNotificationHeightSpinBox->setRange(0, QWIDGETSIZE_MAX);

    QFormLayout *minimumSizeLayout = new QFormLayout;
    minimumSizeLayout->addRow(tr("Width"), minimumNotificationWidthSpinBox);
    minimumSizeLayout->addRow(tr("Height"), minimumNotificationHeightSpinBox);

    QGroupBox *minimumSizeGroupBox = new QGroupBox(tr("Minimum"));
    minimumSizeGroupBox->setLayout(minimumSizeLayout);

    maximumNotificationWidthSpinBox = new QSpinBox;
    maximumNotificationWidthSpinBox->setRange(0, QWIDGETSIZE_MAX);

    maximumNotificationHeightSpinBox = new QSpinBox;
    maximumNotificationHeightSpinBox->setRange(0, QWIDGETSIZE_MAX);

    QFormLayout *maximumSizeLayout = new QFormLayout;
    maximumSizeLayout->addRow(tr("Width"), maximumNotificationWidthSpinBox);
    maximumSizeLayout->addRow(tr("Height"), maximumNotificationHeightSpinBox);

    QGroupBox *maximumSizeGroupBox = new QGroupBox(tr("Maximum"));
    maximumSizeGroupBox->setLayout(maximumSizeLayout);

    QHBoxLayout *sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(minimumSizeGroupBox);
    sizeLayout->addWidget(maximumSizeGroupBox);

    QGroupBox *sizeGroupBox = new QGroupBox(tr("Notification size"));
    sizeGroupBox->setLayout(sizeLayout);

    // Misc

    maxCountSpinBox = new QSpinBox;

    positionComboBox = new QComboBox;
    positionComboBox->addItems(QStringList() << tr("Top Left corner") << tr("Top Right corner") << tr("Bottom Left corner") << tr("Bottom Right corner"));

    QFormLayout *miscLayout = new QFormLayout;
    miscLayout->addRow(tr("Max count"), maxCountSpinBox);
    miscLayout->addRow(tr("Position"), positionComboBox);

    QGroupBox *miscGroupBox = new QGroupBox(tr("Misc"));
    miscGroupBox->setLayout(miscLayout);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(marginsGroupBox);
    layout->addWidget(sizeGroupBox);
    layout->addWidget(miscGroupBox);
    layout->addStretch();

    setLayout(layout);

    connect(horizontalMarginSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(horizontalMarginChanged(int)));
    connect(verticalMarginSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(verticalMarginChanged(int)));
    connect(spacingSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(spacingChanged(int)));
    connect(minimumNotificationWidthSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(minimumNotificationWidthChanged(int)));
    connect(minimumNotificationHeightSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(minimumNotificationHeightChanged(int)));
    connect(maximumNotificationWidthSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(maximumNotificationWidthChanged(int)));
    connect(maximumNotificationHeightSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(maximumNotificationHeightChanged(int)));
    connect(maxCountSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(maxCountChanged(int)));
    connect(positionComboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(positionChanged(int)));
}

void NotificationManagerSettingsWidget::setManager(QOSDNotificationManager *manager)
{
    setHorizontalMargin(manager->horizontalMargin());
    setVerticalMargin(manager->verticalMargin());
    setSpacing(manager->spacing());
    setMinimumNotificationWidth(manager->minimumNotificationWidth());
    setMinimumNotificationHeight(manager->minimumNotificationHeight());
    setMaximumNotificationWidth(manager->maximumNotificationWidth());
    setMaximumNotificationHeight(manager->maximumNotificationHeight());
    setMaxCount(manager->maxCount());
    setPosition(manager->position());
}

int NotificationManagerSettingsWidget::horizontalMargin() const
{
    return horizontalMarginSpinBox->value();
}

void NotificationManagerSettingsWidget::setHorizontalMargin(int margin)
{
    horizontalMarginSpinBox->setValue(margin);
}

int NotificationManagerSettingsWidget::verticalMargin() const
{
    return verticalMarginSpinBox->value();
}

void NotificationManagerSettingsWidget::setVerticalMargin(int margin)
{
    verticalMarginSpinBox->setValue(margin);
}

int NotificationManagerSettingsWidget::minimumNotificationWidth() const
{
    return minimumNotificationWidthSpinBox->value();
}

void NotificationManagerSettingsWidget::setMinimumNotificationWidth(int width)
{
    minimumNotificationWidthSpinBox->setValue(width);
}

int NotificationManagerSettingsWidget::minimumNotificationHeight() const
{
    return minimumNotificationHeightSpinBox->value();
}

void NotificationManagerSettingsWidget::setMinimumNotificationHeight(int height)
{
    minimumNotificationHeightSpinBox->setValue(height);
}

int NotificationManagerSettingsWidget::maximumNotificationWidth() const
{
    return maximumNotificationWidthSpinBox->value();
}

void NotificationManagerSettingsWidget::setMaximumNotificationWidth(int width)
{
    maximumNotificationWidthSpinBox->setValue(width);
}

int NotificationManagerSettingsWidget::maximumNotificationHeight() const
{
    return maximumNotificationHeightSpinBox->value();
}

void NotificationManagerSettingsWidget::setMaximumNotificationHeight(int height)
{
    maximumNotificationHeightSpinBox->setValue(height);
}

int NotificationManagerSettingsWidget::spacing() const
{
    return spacingSpinBox->value();
}

void NotificationManagerSettingsWidget::setSpacing(int spacing)
{
    spacingSpinBox->setValue(spacing);
}

int NotificationManagerSettingsWidget::maxCount() const
{
    return maxCountSpinBox->value();
}

void NotificationManagerSettingsWidget::setMaxCount(int maxCount)
{
    maxCountSpinBox->setValue(maxCount);
}

Qt::Corner NotificationManagerSettingsWidget::position() const
{
    return static_cast<Qt::Corner>(positionComboBox->currentIndex());
}

void NotificationManagerSettingsWidget::setPosition(Qt::Corner position)
{
    positionComboBox->setCurrentIndex(static_cast<int>(position));
}
