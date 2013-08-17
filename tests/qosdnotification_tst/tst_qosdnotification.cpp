#include <QString>
#include <QtTest>
#include <QCoreApplication>

#include <QOSDNotification>
#include <QOSDNotificationCloseButton>

class tst_QOSDNotification : public QObject
{
    Q_OBJECT

public:
    tst_QOSDNotification();

private Q_SLOTS:
    void consistency();
    void showHide();
    void hoverUnhover();
    void activate();
    void close();
    void timeout();
    void resize();
};

tst_QOSDNotification::tst_QOSDNotification()
{
}

void tst_QOSDNotification::consistency()
{
    const bool deleteLaterWhenFinished(true);
    const int duration(10);
    const QLatin1String title("Notification title");
    const QLatin1String bodyText("Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.");
    const QColor backgroundColor(Qt::red);
    const QColor hoverBackgroundColor(Qt::green);
    const QColor borderColor(backgroundColor.lighter(150));
    const QColor hoverBorderColor(hoverBackgroundColor.lighter(150));
    const QColor titleColor(Qt::white);
    const QColor bodyTextColor(Qt::gray);
    const qreal borderWidth(3.0);
    const qreal borderRadius(10);
    const qreal opacity(0.8);
    const qreal hoverOpacity(0.6);
    const bool closeButtonVisible(true);

    QOSDNotification notification(title, bodyText);
    notification.setDeleteLaterWhenFinished(deleteLaterWhenFinished);
    notification.setDuration(duration);
    notification.setBackgroundColor(backgroundColor);
    notification.setBackgroundHoverColor(hoverBackgroundColor);
    notification.setBorderColor(borderColor);
    notification.setBorderHoverColor(hoverBorderColor);
    notification.setTitleColor(titleColor);
    notification.setBodyTextColor(bodyTextColor);
    notification.setBorderWidth(borderWidth);
    notification.setBorderRadius(borderRadius);
    notification.setOpacity(opacity);
    notification.setHoverOpacity(hoverOpacity);
    notification.setCloseButtonVisible(closeButtonVisible);

    QCOMPARE(notification.deleteLaterWhenFinished(), deleteLaterWhenFinished);
    QCOMPARE(notification.duration(), duration);
    QCOMPARE(notification.isHovered(), false);
    QCOMPARE(notification.title(), title);
    QCOMPARE(notification.bodyText(), bodyText);
    QVERIFY(notification.bodyWidget() == 0);
    QVERIFY(notification.pixmap().isNull());
    QCOMPARE(notification.backgroundColor(), backgroundColor);
    QCOMPARE(notification.backgroundHoverColor(), hoverBackgroundColor);
    QCOMPARE(notification.borderColor(), borderColor);
    QCOMPARE(notification.borderHoverColor(), hoverBorderColor);
    QCOMPARE(notification.titleColor(), titleColor);
    QCOMPARE(notification.bodyTextColor(), bodyTextColor);
    QCOMPARE(notification.borderWidth(), borderWidth);
    QCOMPARE(notification.borderRadius(), borderRadius);
    QCOMPARE(notification.opacity(), opacity);
    QCOMPARE(notification.hoverOpacity(), hoverOpacity);
    QCOMPARE(notification.isCloseButtonVisible(), true);
    QVERIFY(notification.titleLabel() != 0);
    QVERIFY(notification.bodyTextLabel() != 0);
    QVERIFY(notification.closeButton() != 0);
}

void tst_QOSDNotification::showHide()
{
    QOSDNotification notification;

    QSignalSpy aboutToShowSpy(&notification, SIGNAL(aboutToShow()));
    QSignalSpy shownSpy(&notification, SIGNAL(shown()));
    QSignalSpy aboutToHideSpy(&notification, SIGNAL(aboutToHide()));
    QSignalSpy hiddenSpy(&notification, SIGNAL(hidden()));

    notification.show();
    QCOMPARE(notification.isVisible(), true);

    QCOMPARE(aboutToShowSpy.count(), 1);
    QCOMPARE(shownSpy.count(), 1);
    QCOMPARE(aboutToHideSpy.count(), 0);
    QCOMPARE(hiddenSpy.count(), 0);

    aboutToShowSpy.clear();
    shownSpy.clear();

    notification.hide();
    QCOMPARE(notification.isVisible(), false);

    QCOMPARE(aboutToShowSpy.count(), 0);
    QCOMPARE(shownSpy.count(), 0);
    QCOMPARE(aboutToHideSpy.count(), 1);
    QCOMPARE(hiddenSpy.count(), 1);

    aboutToHideSpy.clear();
    hiddenSpy.clear();
}

void tst_QOSDNotification::hoverUnhover()
{
    QOSDNotification notification;

    QSignalSpy hoveredSpy(&notification, SIGNAL(hovered()));
    QSignalSpy unhoveredSpy(&notification, SIGNAL(unhovered()));

    notification.show();

    // hover
    QTest::mouseMove(&notification);
    QTest::qWait(100);

    QCOMPARE(notification.isHovered(), true);

    QCOMPARE(hoveredSpy.count(), 1);
    QCOMPARE(unhoveredSpy.count(), 0);

    hoveredSpy.clear();

    // unhover
    QTest::mouseMove(&notification, QPoint(notification.width(), notification.height()));
    QTest::qWait(100);

    QCOMPARE(notification.isHovered(), false);

    QCOMPARE(hoveredSpy.count(), 0);
    QCOMPARE(unhoveredSpy.count(), 1);

    unhoveredSpy.clear();
}

void tst_QOSDNotification::activate()
{
    QOSDNotification notification;

    QSignalSpy activatedSpy(&notification, SIGNAL(activated()));

    notification.show();

    QTest::mousePress(&notification, Qt::LeftButton);
    //QTest::qWait(100);

    QCOMPARE(activatedSpy.count(), 1);
}

void tst_QOSDNotification::close()
{
    QOSDNotification notification;

    QSignalSpy closedSpy(&notification, SIGNAL(closed()));
    QSignalSpy finishedSpy(&notification, SIGNAL(finished()));

    notification.show();

    QOSDNotificationCloseButton *closeButton = notification.closeButton();
    QVERIFY(closeButton != 0);

    QTest::mouseClick(closeButton, Qt::LeftButton);

    QCOMPARE(notification.isVisible(), false);

    QCOMPARE(closedSpy.count(), 1);
    QCOMPARE(finishedSpy.count(), 1);
}

void tst_QOSDNotification::timeout()
{
    const int duration = 1000;
    QOSDNotification notification;
    notification.setDuration(duration);

    QSignalSpy timeoutSpy(&notification, SIGNAL(timeout()));
    QSignalSpy finishedSpy(&notification, SIGNAL(finished()));

    notification.show();

    // unhover
    QTest::mouseMove(&notification, QPoint(notification.width(), notification.height()));

    // wait for timeout
    QTest::qWait(duration + 100);

    QCOMPARE(timeoutSpy.count(), 1);
    QCOMPARE(finishedSpy.count(), 1);
}

void tst_QOSDNotification::resize()
{
    QOSDNotification notification;

    notification.show();

    QSignalSpy resizedSpy(&notification, SIGNAL(resized()));

    notification.resize(notification.width() + 10, notification.height() + 10);
    QTest::qWait(100);

    QVERIFY(resizedSpy.count() >= 1);
}

#include "tst_qosdnotification.moc"
QTEST_MAIN(tst_QOSDNotification)
