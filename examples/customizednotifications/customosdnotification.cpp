#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "customosdnotification.h"

CustomOSDNotification::CustomOSDNotification(QWidget *parent) :
    QAbstractOSDNotification(parent)
{
    init();
}

CustomOSDNotification::CustomOSDNotification(const QString &title, const QString &message, const QPixmap &pixmap, QWidget *parent) :
    QAbstractOSDNotification(parent)
{
    init();
    setTitle(title);
    setMessage(message);
    setPixmap(pixmap);
}

QString CustomOSDNotification::title() const
{
    return titleLabel->text();
}

void CustomOSDNotification::setTitle(const QString &title)
{
    titleLabel->setText(title);
}

QString CustomOSDNotification::message() const
{
    return messageLabel->text();
}

void CustomOSDNotification::setMessage(const QString &message)
{
    messageLabel->setText(message);
}

const QPixmap *CustomOSDNotification::pixmap() const
{
    return iconLabel->pixmap();
}

void CustomOSDNotification::setPixmap(const QPixmap &pixmap)
{
    iconLabel->setVisible(!pixmap.isNull());
    iconLabel->setPixmap(pixmap);
}

void CustomOSDNotification::init()
{
    iconLabel = new QLabel;
    iconLabel->hide();

    titleLabel = new QLabel;
    titleLabel->setWordWrap(true);
    titleLabel->setStyleSheet("QLabel { color: #ffffff; font-weight: bold; font-size: 14px; }");

    messageLabel = new QLabel;
    messageLabel->setWordWrap(true);
    messageLabel->setStyleSheet("QLabel { color: #ffffff; font-style: italic; font-size: 12px; }");

    QVBoxLayout *textLayout = new QVBoxLayout;
    textLayout->addWidget(titleLabel);
    textLayout->addWidget(messageLabel);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(iconLabel, 0, Qt::AlignTop);
    mainLayout->addLayout(textLayout);

    QWidget *mainWidget = new QWidget;
    mainWidget->setStyleSheet(".QWidget {"
                                    "background-color: rgba(0, 0, 0, 85%);"
                                    "border-style: solid;"
                                    "border-width: 2px;"
                                    "border-radius: 10px;"
                                    "border-color: green;"
                                 "}"
                                 ".QWidget:hover {"
                                    "background-color: rgba(0, 0, 0, 75%);"
                                    "border-style: solid;"
                                    "border-width: 2px;"
                                    "border-radius: 10px;"
                                    "border-color: green;"
                                 "}");
    mainWidget->setLayout(mainLayout);

    QHBoxLayout *containerLayout = new QHBoxLayout;
    containerLayout->setContentsMargins(0, 0, 0, 0);
    containerLayout->addWidget(mainWidget);

    setLayout(containerLayout);
}
