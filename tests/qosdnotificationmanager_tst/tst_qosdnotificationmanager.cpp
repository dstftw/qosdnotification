#include <QtTest>
#include <QListWidget>
#include <QPointer>

#include <QOSDNotificationManager>
#include <QOSDNotification>
#include <QOSDNotificationCloseButton>

Q_DECLARE_METATYPE(QAbstractOSDNotification*)

class tst_QOSDNotificationManager : public QObject
{
    Q_OBJECT

public:
    tst_QOSDNotificationManager();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void consistency();
    void addRemoveBodyTextNotification_data();
    void addRemoveBodyTextNotification();
    void addRemoveBodyWidgetNotification_data();
    void addRemoveBodyWidgetNotification();
    void addRemoveCustomNotification_data();
    void addRemoveCustomNotification();
    void addNotificationsAndClear();
    void addNotificationsAndClose();
    void addNotificationsAndTimeout();

private:
    QOSDNotification *createLoremNotification();

    QString notificationTitle;
    QString loremIpsumText;
};

tst_QOSDNotificationManager::tst_QOSDNotificationManager()
{
}

QOSDNotification *tst_QOSDNotificationManager::createLoremNotification()
{
    return new QOSDNotification(notificationTitle, loremIpsumText);
}

void tst_QOSDNotificationManager::initTestCase()
{
    qRegisterMetaType<QAbstractOSDNotification*>();
    notificationTitle = "Notification title";
    loremIpsumText = "Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";
}

void tst_QOSDNotificationManager::cleanupTestCase()
{
}

void tst_QOSDNotificationManager::consistency()
{
    const Qt::Corner position = Qt::TopRightCorner;
    const int maxCount = 10;
    const int horizontalMargin = 10;
    const int verticalMargin = 10;
    const int spacing = 5;
    const int defaultDuration = 5000;
    const int minimumNotificationWidth = 290;
    const int minimumNotificationHeight = 0;
    const int maximumNotificationWidth = QWIDGETSIZE_MAX;
    const int maximumNotificationHeight = QWIDGETSIZE_MAX;

    QOSDNotificationManager manager;
    manager.setPosition(position);
    manager.setMaxCount(maxCount);
    manager.setHorizontalMargin(horizontalMargin);
    manager.setVerticalMargin(verticalMargin);
    manager.setSpacing(spacing);
    manager.setDefaultDuration(defaultDuration);
    manager.setMinimumNotificationWidth(minimumNotificationWidth);
    manager.setMinimumNotificationHeight(minimumNotificationHeight);
    manager.setMaximumNotificationWidth(maximumNotificationWidth);
    manager.setMaximumNotificationHeight(maximumNotificationHeight);

    QCOMPARE(manager.position(), position);
    QCOMPARE(manager.maxCount(), maxCount);
    QCOMPARE(manager.horizontalMargin(), horizontalMargin);
    QCOMPARE(manager.verticalMargin(), verticalMargin);
    QCOMPARE(manager.spacing(), spacing);
    QCOMPARE(manager.defaultDuration(), defaultDuration);
    QCOMPARE(manager.minimumNotificationWidth(), minimumNotificationWidth);
    QCOMPARE(manager.minimumNotificationHeight(), minimumNotificationHeight);
    QCOMPARE(manager.maximumNotificationWidth(), maximumNotificationWidth);
    QCOMPARE(manager.maximumNotificationHeight(), maximumNotificationHeight);

    QCOMPARE(manager.count(), 0);
}

void tst_QOSDNotificationManager::addRemoveBodyTextNotification_data()
{
    QTest::addColumn<QString>("title");
    QTest::addColumn<QString>("bodyText");
    QTest::addColumn<QPixmap>("pixmap");
    QTest::addColumn<bool>("deleteLater");

    QTest::newRow("bodyText notification w auto delete") << notificationTitle << loremIpsumText << QPixmap() << true;
    QTest::newRow("bodyText notification w/o auto delete") << notificationTitle << loremIpsumText << QPixmap() << false;
    QTest::newRow("bodyText notification w pixmap") << notificationTitle << loremIpsumText << QPixmap(":/qt-logo.png") << false;
}

void tst_QOSDNotificationManager::addRemoveBodyTextNotification()
{
    QOSDNotificationManager manager;

    QFETCH(QString, title);
    QFETCH(QString, bodyText);
    QFETCH(QPixmap, pixmap);
    QFETCH(bool, deleteLater);

    QPointer<QOSDNotification> notification = manager.add(title, bodyText, pixmap);
    if (!deleteLater)
        notification->setDeleteLaterWhenFinished(deleteLater);

    QCOMPARE(notification->title(), title);
    QCOMPARE(notification->bodyText(), bodyText);
    QVERIFY(!notification->bodyWidget());
    QCOMPARE(notification->pixmap(), pixmap);

    QCOMPARE(manager.count(), 1);

    QSignalSpy removeSpy(&manager, SIGNAL(removed(QAbstractOSDNotification*)));

    manager.remove(notification);

    QCOMPARE(manager.count(), 0);

    QCOMPARE(removeSpy.count(), 1);
    QList<QVariant> arguments = removeSpy.takeFirst();
    QCOMPARE(arguments.count(), 1);
    QVariant argument = arguments.at(0);
    QVERIFY(qvariant_cast<QAbstractOSDNotification*>(argument) == notification);

    // wait for deleteLater() on notification
    QTest::qWait(100);

    QCOMPARE(notification.isNull(), deleteLater);
    if (!deleteLater)
        delete notification;
}

void tst_QOSDNotificationManager::addRemoveBodyWidgetNotification_data()
{
    QTest::addColumn<QString>("title");
    QTest::addColumn<QWidget*>("bodyWidget");
    QTest::addColumn<QPixmap>("pixmap");
    QTest::addColumn<bool>("deleteLater");

    QListWidget *listWidget1 = new QListWidget();
    listWidget1->addItems(QStringList() << "Item1" << "Item2" << "Item3");
    QTest::newRow("bodyWidget notification w auto delete") << notificationTitle << (QWidget*)listWidget1 << QPixmap() << true;

    QListWidget *listWidget2 = new QListWidget();
    listWidget2->addItems(QStringList() << "Item1" << "Item2" << "Item3");
    QTest::newRow("bodyWidget notification w/o auto delete") << notificationTitle << (QWidget*)listWidget2 << QPixmap() << false;
}

void tst_QOSDNotificationManager::addRemoveBodyWidgetNotification()
{
    QOSDNotificationManager manager;

    QFETCH(QString, title);
    QFETCH(QWidget*, bodyWidget);
    QFETCH(QPixmap, pixmap);
    QFETCH(bool, deleteLater);

    QPointer<QWidget> bodyWidgetPtr(bodyWidget);

    QPointer<QOSDNotification> notification = manager.add(title, bodyWidget, pixmap);
    if (!deleteLater)
        notification->setDeleteLaterWhenFinished(deleteLater);

    QCOMPARE(notification->title(), title);
    QVERIFY(notification->bodyText().isEmpty());
    QCOMPARE(notification->bodyWidget(), bodyWidget);

    QCOMPARE(manager.count(), 1);

    QSignalSpy removeSpy(&manager, SIGNAL(removed(QAbstractOSDNotification*)));

    manager.remove(notification);

    QCOMPARE(manager.count(), 0);

    QCOMPARE(removeSpy.count(), 1);
    QList<QVariant> arguments = removeSpy.takeFirst();
    QCOMPARE(arguments.count(), 1);
    QVariant argument = arguments.at(0);
    QVERIFY(qvariant_cast<QAbstractOSDNotification*>(argument) == notification);

    // wait for deleteLater() on notification
    QTest::qWait(100);

    QCOMPARE(notification.isNull(), deleteLater);
    if (!deleteLater)
        delete notification;

    // cleanup bodyWidget
    QCOMPARE(bodyWidgetPtr.isNull(), false);
    delete bodyWidgetPtr;
}

void tst_QOSDNotificationManager::addRemoveCustomNotification_data()
{
    QTest::addColumn<QAbstractOSDNotification*>("customNotification");
    QTest::addColumn<bool>("deleteLater");

    QAbstractOSDNotification *notification1 = createLoremNotification();
    QTest::newRow("QOSDNotification w/o auto delete") << notification1 << false;

    QAbstractOSDNotification *notification2 = createLoremNotification();
    QTest::newRow("QOSDNotification w auto delete") << notification2 << true;
}

void tst_QOSDNotificationManager::addRemoveCustomNotification()
{
    QOSDNotificationManager manager;

    QFETCH(QAbstractOSDNotification*, customNotification);
    QFETCH(bool, deleteLater);

    QPointer<QAbstractOSDNotification> notification(customNotification);
    if (deleteLater)
        notification->setDeleteLaterWhenFinished(deleteLater);

    manager.add(customNotification);

    QCOMPARE(manager.count(), 1);

    QSignalSpy removeSpy(&manager, SIGNAL(removed(QAbstractOSDNotification*)));

    manager.remove(notification);

    QCOMPARE(manager.count(), 0);

    QCOMPARE(removeSpy.count(), 1);
    QList<QVariant> arguments = removeSpy.takeFirst();
    QCOMPARE(arguments.count(), 1);
    QVariant argument = arguments.at(0);
    QVERIFY(qvariant_cast<QAbstractOSDNotification*>(argument) == notification);

    // wait for deleteLater() on notification
    QTest::qWait(100);

    QCOMPARE(notification.isNull(), deleteLater);
    if (!deleteLater)
        delete notification;
}

void tst_QOSDNotificationManager::addNotificationsAndClear()
{
    QOSDNotificationManager manager;
    manager.setMaxCount(10);

    for (int i = 1; i <= 10; ++i) {
        manager.add(QString("%1 #%2").arg(notificationTitle).arg(QString::number(i)), loremIpsumText);
        QCOMPARE(manager.count(), i);
    }

    manager.clear();

    QCOMPARE(manager.count(), 0);
}

void tst_QOSDNotificationManager::addNotificationsAndClose()
{
    QOSDNotificationManager manager;

    QOSDNotification *notification = manager.add(notificationTitle, loremIpsumText);

    QOSDNotificationCloseButton *closeButton = notification->closeButton();
    QVERIFY(closeButton != 0);

    QSignalSpy finishedSpy(&manager, SIGNAL(finished(QAbstractOSDNotification*)));
    QSignalSpy removedSpy(&manager, SIGNAL(removed(QAbstractOSDNotification*)));

    QTest::mouseClick(closeButton, Qt::LeftButton);

    QCOMPARE(manager.count(), 0);
    QCOMPARE(finishedSpy.count(), 1);
    {
        QList<QVariant> arguments = finishedSpy.takeFirst();
        QCOMPARE(arguments.count(), 1);
        QVariant argument = arguments.at(0);
        QVERIFY(qvariant_cast<QAbstractOSDNotification*>(argument) == notification);
    }
    QCOMPARE(removedSpy.count(), 1);
    {
        QList<QVariant> arguments = removedSpy.takeFirst();
        QCOMPARE(arguments.count(), 1);
        QVariant argument = arguments.at(0);
        QVERIFY(qvariant_cast<QAbstractOSDNotification*>(argument) == notification);
    }
}

void tst_QOSDNotificationManager::addNotificationsAndTimeout()
{
    QOSDNotificationManager manager;

    QOSDNotification notification1(notificationTitle + " #1", loremIpsumText);
    notification1.setDuration(1000);
    manager.add(&notification1);

    QOSDNotification notification2(notificationTitle + " #2", loremIpsumText);
    notification2.setDuration(800);
    manager.add(&notification2);

    QOSDNotification notification3(notificationTitle + " #3", loremIpsumText);
    notification3.setDuration(600);
    manager.add(&notification3);

    QOSDNotification notification4(notificationTitle + " #4", loremIpsumText);
    notification4.setDuration(800);
    manager.add(&notification4);

    QOSDNotification notification5(notificationTitle + " #5", loremIpsumText);
    notification5.setDuration(1000);
    manager.add(&notification5);

    QSignalSpy finishedSpy(&manager, SIGNAL(finished(QAbstractOSDNotification*)));

    QTest::qWait(650);

    QCOMPARE(manager.count(), 4);
    QCOMPARE(finishedSpy.count(), 1);
    {
        QList<QVariant> arguments = finishedSpy.takeFirst();
        QCOMPARE(arguments.count(), 1);
        QVariant argument = arguments.at(0);
        QVERIFY(qvariant_cast<QAbstractOSDNotification*>(argument) == &notification3);
    }

    QTest::qWait(200);

    QCOMPARE(manager.count(), 2);
    QCOMPARE(finishedSpy.count(), 2);
    {
        for (int i = 0; i < 2; ++i) {
            QList<QVariant> arguments = finishedSpy.takeFirst();
            QCOMPARE(arguments.count(), 1);
            QVariant argument = arguments.at(0);
            QAbstractOSDNotification *notification = qvariant_cast<QAbstractOSDNotification*>(argument);
            QVERIFY(notification == &notification2 || notification == &notification4);
        }
    }

    QTest::qWait(200);

    QCOMPARE(manager.count(), 0);
    QCOMPARE(finishedSpy.count(), 2);
    {
        for (int i = 0; i < 2; ++i) {
            QList<QVariant> arguments = finishedSpy.takeFirst();
            QCOMPARE(arguments.count(), 1);
            QVariant argument = arguments.at(0);
            QAbstractOSDNotification *notification = qvariant_cast<QAbstractOSDNotification*>(argument);
            QVERIFY(notification == &notification1 || notification == &notification5);
        }
    }

}

#include "tst_qosdnotificationmanager.moc"
QTEST_MAIN(tst_QOSDNotificationManager)
