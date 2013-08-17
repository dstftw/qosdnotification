#include <QFormLayout>
#include <QPlainTextEdit>
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QCheckBox>

#include <QOSDNotification>

#include "notificationsettingswidget.h"
#include "notificationmanager.h"
#include "iconwidget.h"
#include "colorwidget.h"

NotificationSettingsWidget::NotificationSettingsWidget(QWidget *parent) :
    QWidget(parent)
{
    // Title

    titlePlainTextEdit = new QPlainTextEdit(tr("Notification's' title"));
    titleColorWidget = new ColorWidget;

    QFormLayout *titleLayout = new QFormLayout;
    titleLayout->addRow(tr("Text"), titlePlainTextEdit);
    titleLayout->addRow(tr("Color"), titleColorWidget);

    QGroupBox *titleGroupBox = new QGroupBox(tr("Title"));
    titleGroupBox->setLayout(titleLayout);

    // Body

    bodyTextPlainTextEdit = new QPlainTextEdit(tr("Notification's body text"));
    bodyTextColorWidget = new ColorWidget;

    QFormLayout *bodyTextLayout = new QFormLayout;
    bodyTextLayout->addRow(tr("Text"), bodyTextPlainTextEdit);
    bodyTextLayout->addRow(tr("Color"), bodyTextColorWidget);

    QGroupBox *bodyTextGroupBox = new QGroupBox(tr("Body"));
    bodyTextGroupBox->setLayout(bodyTextLayout);

    // Icon

    iconWidget = new IconWidget;

    QHBoxLayout *pixmapLayout = new QHBoxLayout;
    pixmapLayout->addWidget(iconWidget);

    QGroupBox *pixmapGroupBox = new QGroupBox(tr("Icon"));
    pixmapGroupBox->setLayout(pixmapLayout);

    // Background

    backgroundColorWidget = new ColorWidget;
    backgroundHoverColorWidget = new ColorWidget;

    QFormLayout *backgroundLayout = new QFormLayout;
    backgroundLayout->addRow(tr("Color"), backgroundColorWidget);
    backgroundLayout->addRow(tr("Color (hovered)"), backgroundHoverColorWidget);

    QGroupBox *backgroundGroupBox = new QGroupBox(tr("Background"));
    backgroundGroupBox->setLayout(backgroundLayout);

    // Border

    borderColorWidget = new ColorWidget;
    borderHoverColorWidget = new ColorWidget;
    borderWidthSpinBox = new QDoubleSpinBox;
    borderWidthSpinBox->setRange(0, LONG_MAX);
    borderRadiusSpinBox = new QDoubleSpinBox;
    borderRadiusSpinBox->setRange(0, LONG_MAX);

    QFormLayout *borderLayout = new QFormLayout;
    borderLayout->addRow(tr("Color"), borderColorWidget);
    borderLayout->addRow(tr("Color (hovered)"), borderHoverColorWidget);
    borderLayout->addRow(tr("Width"), borderWidthSpinBox);
    borderLayout->addRow(tr("Radius"), borderRadiusSpinBox);

    QGroupBox *borderGroupBox = new QGroupBox(tr("Border"));
    borderGroupBox->setLayout(borderLayout);

    // Misc

    durationSpinBox = new QSpinBox;
    durationSpinBox->setRange(0, INT_MAX);
    durationSpinBox->setSingleStep(1000);
    opacitySpinBox = new QDoubleSpinBox;
    opacitySpinBox->setRange(0, 1);
    opacitySpinBox->setSingleStep(0.01);
    hoverOpacitySpinBox = new QDoubleSpinBox;
    hoverOpacitySpinBox->setRange(0, 1);
    hoverOpacitySpinBox->setSingleStep(0.01);
    closeButtonCheckBox = new QCheckBox(tr("Close button visible"));

    QFormLayout *miscLayout = new QFormLayout;
    miscLayout->addRow(tr("Duration (ms)"), durationSpinBox);
    miscLayout->addRow(tr("Opacity"), opacitySpinBox);
    miscLayout->addRow(tr("Opacity (hovered)"), hoverOpacitySpinBox);
    miscLayout->addRow(closeButtonCheckBox);

    QGroupBox *miscGroupBox = new QGroupBox(tr("Misc"));
    miscGroupBox->setLayout(miscLayout);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(titleGroupBox, 0, 0, 1, 1);
    layout->addWidget(bodyTextGroupBox, 1, 0, 1, 1);
    layout->addWidget(pixmapGroupBox, 0, 1, 2, 1);
    layout->addWidget(backgroundGroupBox, 2, 0, 1, 1);
    layout->addWidget(borderGroupBox, 2, 1, 1, 1);
    layout->addWidget(miscGroupBox, 3, 0, 1, 2);

    setLayout(layout);

    connect(titlePlainTextEdit, SIGNAL(textChanged()), this, SLOT(titleChanged()));
    connect(titleColorWidget, SIGNAL(colorChanged(QColor)), this, SIGNAL(titleColorChanged(QColor)));
    connect(bodyTextPlainTextEdit, SIGNAL(textChanged()), this, SLOT(bodyTextChanged()));
    connect(bodyTextColorWidget, SIGNAL(colorChanged(QColor)), this, SIGNAL(bodyTextColorChanged(QColor)));
    connect(iconWidget, SIGNAL(pixmapChanged(QPixmap)), this, SIGNAL(iconChanged(QPixmap)));
    connect(iconWidget, SIGNAL(pixmapAutoScaleChanged(bool)), this, SIGNAL(iconAutoScaleChanged(bool)));
    connect(backgroundColorWidget, SIGNAL(colorChanged(QColor)), this, SIGNAL(backgroundColorChanged(QColor)));
    connect(backgroundHoverColorWidget, SIGNAL(colorChanged(QColor)), this, SIGNAL(backgroundHoverColorChanged(QColor)));
    connect(borderColorWidget, SIGNAL(colorChanged(QColor)), this, SIGNAL(borderColorChanged(QColor)));
    connect(borderHoverColorWidget, SIGNAL(colorChanged(QColor)), this, SIGNAL(borderHoverColorChanged(QColor)));
    connect(borderWidthSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(borderWidthChanged(qreal)));
    connect(borderRadiusSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(borderRadiusChanged(qreal)));
    connect(durationSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(durationChanged(int)));
    connect(opacitySpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(opacityChanged(qreal)));
    connect(hoverOpacitySpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(hoverOpacityChanged(qreal)));
    connect(closeButtonCheckBox, SIGNAL(toggled(bool)), this, SIGNAL(closeButtonVisibleChanged(bool)));

}

void NotificationSettingsWidget::titleChanged()
{
    emit titleChanged(titlePlainTextEdit->toPlainText());
}

void NotificationSettingsWidget::bodyTextChanged()
{
    emit bodyTextChanged(bodyTextPlainTextEdit->toPlainText());
}

void NotificationSettingsWidget::setNotificationData(const OSDNotificationData *notificationData)
{
    setTitle(notificationData->title);
    setTitleColor(notificationData->titleColor);
    setBodyText(notificationData->bodyText);
    setBodyTextColor(notificationData->bodyTextColor);
    setIcon(notificationData->icon);
    setIconAutoScale(notificationData->iconAutoScale);
    setBackgroundColor(notificationData->backgroundColor);
    setBackgroundHoverColor(notificationData->backgroundHoverColor);
    setBorderColor(notificationData->borderColor);
    setBorderHoverColor(notificationData->borderHoverColor);
    setBorderWidth(notificationData->borderWidth);
    setBorderRadius(notificationData->borderRadius);
    setDuration(notificationData->duration);
    setOpacity(notificationData->opacity);
    setHoverOpacity(notificationData->hoverOpacity);
    setCloseButtonVisible(notificationData->closeButtonVisible);
}

void NotificationSettingsWidget::writeSettings(QOSDNotification *notification)
{
    notification->setDuration(duration());
    notification->setTitle(title());
    notification->setBodyText(bodyText());
    notification->setPixmap(icon(), iconAutoScale());
    notification->setBackgroundColor(backgroundColor());
    notification->setBackgroundHoverColor(backgroundHoverColor());
    notification->setBorderColor(borderColor());
    notification->setBorderHoverColor(borderHoverColor());
    notification->setTitleColor(titleColor());
    notification->setBodyTextColor(bodyTextColor());
    notification->setBorderWidth(borderWidth());
    notification->setBorderRadius(borderRadius());
    notification->setOpacity(opacity());
    notification->setHoverOpacity(hoverOpacity());
    notification->setCloseButtonVisible(isCloseButtonVisible());
}

int NotificationSettingsWidget::duration() const
{
    return durationSpinBox->value();
}

void NotificationSettingsWidget::setDuration(int duration)
{
    durationSpinBox->setValue(duration);
}

QString NotificationSettingsWidget::title() const
{
    return titlePlainTextEdit->toPlainText();
}

void NotificationSettingsWidget::setTitle(const QString &title)
{
    titlePlainTextEdit->setPlainText(title);
}

QString NotificationSettingsWidget::bodyText() const
{
    return bodyTextPlainTextEdit->toPlainText();
}

void NotificationSettingsWidget::setBodyText(const QString &bodyText)
{
    bodyTextPlainTextEdit->setPlainText(bodyText);
}

QPixmap NotificationSettingsWidget::icon() const
{
    return iconWidget->pixmap();
}

void NotificationSettingsWidget::setIcon(const QPixmap &pixmap)
{
    iconWidget->setPixmap(pixmap);
}

bool NotificationSettingsWidget::iconAutoScale() const
{
    return iconWidget->pixmapAutoScale();
}

void NotificationSettingsWidget::setIconAutoScale(bool autoScale)
{
    iconWidget->setPixmapAutoScale(autoScale);
}

QColor NotificationSettingsWidget::backgroundColor() const
{
    return backgroundColorWidget->color();
}

void NotificationSettingsWidget::setBackgroundColor(const QColor &color)
{
    backgroundColorWidget->setColor(color);
}

QColor NotificationSettingsWidget::backgroundHoverColor() const
{
    return backgroundHoverColorWidget->color();
}

void NotificationSettingsWidget::setBackgroundHoverColor(const QColor &color)
{
    backgroundHoverColorWidget->setColor(color);
}

QColor NotificationSettingsWidget::borderColor() const
{
    return borderColorWidget->color();
}

void NotificationSettingsWidget::setBorderColor(const QColor &color)
{
    borderColorWidget->setColor(color);
}

QColor NotificationSettingsWidget::borderHoverColor() const
{
    return borderHoverColorWidget->color();
}

void NotificationSettingsWidget::setBorderHoverColor(const QColor &color)
{
    borderHoverColorWidget->setColor(color);
}

QColor NotificationSettingsWidget::titleColor() const
{
    return titleColorWidget->color();
}

void NotificationSettingsWidget::setTitleColor(const QColor &color)
{
    titleColorWidget->setColor(color);
}

QColor NotificationSettingsWidget::bodyTextColor() const
{
    return bodyTextColorWidget->color();
}

void NotificationSettingsWidget::setBodyTextColor(const QColor &color)
{
    bodyTextColorWidget->setColor(color);
}

qreal NotificationSettingsWidget::borderWidth() const
{
    return borderWidthSpinBox->value();
}

void NotificationSettingsWidget::setBorderWidth(qreal width)
{
    borderWidthSpinBox->setValue(width);
}

qreal NotificationSettingsWidget::borderRadius() const
{
    return borderRadiusSpinBox->value();
}

void NotificationSettingsWidget::setBorderRadius(qreal radius)
{
    borderRadiusSpinBox->setValue(radius);
}

qreal NotificationSettingsWidget::opacity() const
{
    return opacitySpinBox->value();
}

void NotificationSettingsWidget::setOpacity(qreal opacity)
{
    opacitySpinBox->setValue(opacity);
}

qreal NotificationSettingsWidget::hoverOpacity() const
{
    return hoverOpacitySpinBox->value();
}

void NotificationSettingsWidget::setHoverOpacity(qreal opacity)
{
    hoverOpacitySpinBox->setValue(opacity);
}

bool NotificationSettingsWidget::isCloseButtonVisible() const
{
    return closeButtonCheckBox->isChecked();
}

void NotificationSettingsWidget::setCloseButtonVisible(bool visible)
{
    closeButtonCheckBox->setChecked(visible);
}
