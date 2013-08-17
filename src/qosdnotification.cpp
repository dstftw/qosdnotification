#include <qmath.h>
#include <QPainter>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QBitmap>
#if QT_VERSION < 0x050000
#include <QX11Info>
#endif

#include "qosdnotification.h"
#include "qosdnotification_p.h"
#include "qosdnotificationclosebutton.h"

QOSDNotification::QOSDNotification(QWidget *parent) :
    QAbstractOSDNotification(*new QOSDNotificationPrivate, parent, 0)
{
    Q_D(QOSDNotification);
    d->init();
}

QOSDNotification::QOSDNotification(const QString &title, const QString &message, const QPixmap &pixmap, bool pixmapAutoScale, QWidget *parent) :
    QAbstractOSDNotification(*new QOSDNotificationPrivate, parent, 0)
{
    Q_D(QOSDNotification);
    d->init();
    d->setTitle(title);
    d->setBodyText(message);
    d->setPixmap(pixmap, pixmapAutoScale);
    adjustSize();
}

QOSDNotification::QOSDNotification(const QString &title, QWidget *bodyWidget, const QPixmap &pixmap, bool pixmapAutoScale, QWidget *parent) :
    QAbstractOSDNotification(*new QOSDNotificationPrivate, parent, 0)
{
    Q_D(QOSDNotification);
    d->init();
    d->setTitle(title);
    d->setBodyWidget(bodyWidget);
    d->setPixmap(pixmap, pixmapAutoScale);
    adjustSize();
}

QOSDNotification::~QOSDNotification()
{
    Q_D(QOSDNotification);
    d->maybeRemoveBodyWidget();
}

QString QOSDNotification::title() const
{
    return d_func()->titleLabel->text();
}

void QOSDNotification::setTitle(const QString &title)
{
    Q_D(QOSDNotification);
    d->setTitle(title);
    adjustSize();
}

QString QOSDNotification::bodyText() const
{
    return d_func()->bodyTextLabel->text();
}

void QOSDNotification::setBodyText(const QString &bodyText)
{
    Q_D(QOSDNotification);
    d->setBodyText(bodyText);
    adjustSize();
}

QWidget *QOSDNotification::bodyWidget() const
{
    return d_func()->bodyWidget;
}

void QOSDNotification::setBodyWidget(QWidget *bodyWidget)
{
    Q_D(QOSDNotification);
    d->setBodyWidget(bodyWidget);
    adjustSize();
}

QPixmap QOSDNotification::pixmap() const
{
    return d_func()->pixmap;
}

void QOSDNotification::setPixmap(const QPixmap &pixmap, bool autoScale)
{
    Q_D(QOSDNotification);
    d->setPixmap(pixmap, autoScale);
    adjustSize();
}

QBrush QOSDNotification::backgroundBrush() const
{
    return d_func()->backgroundBrush;
}

void QOSDNotification::setBackgroundBrush(const QBrush &brush)
{
    Q_D(QOSDNotification);
    if (d->backgroundBrush != brush) {
        d->backgroundBrush = brush;
        update();
    }
}

QBrush QOSDNotification::backgroundHoverBrush() const
{
    return d_func()->backgroundHoverBrush;
}

void QOSDNotification::setBackgroundHoverBrush(const QBrush &brush)
{
    Q_D(QOSDNotification);
    if (d->backgroundHoverBrush != brush) {
        d->backgroundHoverBrush = brush;
        update();
    }
}

QColor QOSDNotification::backgroundColor() const
{
    return d_func()->backgroundColor;
}

void QOSDNotification::setBackgroundColor(const QColor &color)
{
    Q_D(QOSDNotification);
    if (d->backgroundColor != color) {
        d->backgroundColor = color;
        update();
    }
}

QColor QOSDNotification::backgroundHoverColor() const
{
    return d_func()->backgroundHoverColor;
}

void QOSDNotification::setBackgroundHoverColor(const QColor &color)
{
    Q_D(QOSDNotification);
    if (d->backgroundHoverColor != color) {
        d->backgroundHoverColor = color;
        update();
    }
}

QPen QOSDNotification::borderPen() const
{
    return d_func()->borderPen;
}

void QOSDNotification::setBorderPen(const QPen &pen)
{
    Q_D(QOSDNotification);
    if (d->borderPen != pen) {
        d->borderPen = pen;
        update();
    }
}

QPen QOSDNotification::borderHoverPen() const
{
    return d_func()->borderHoverPen;
}

void QOSDNotification::setBorderHoverPen(const QPen &pen)
{
    Q_D(QOSDNotification);
    if (d->borderHoverPen != pen) {
        d->borderHoverPen = pen;
        update();
    }
}

QColor QOSDNotification::borderColor() const
{
    return d_func()->borderColor;
}

void QOSDNotification::setBorderColor(const QColor &color)
{
    Q_D(QOSDNotification);
    if (d->borderColor != color) {
        d->borderColor = color;
        update();
    }
}

QColor QOSDNotification::borderHoverColor() const
{
    return d_func()->borderHoverColor;
}

void QOSDNotification::setBorderHoverColor(const QColor &color)
{
    Q_D(QOSDNotification);
    if (d->borderHoverColor != color) {
        d->borderHoverColor = color;
        update();
    }
}

QColor QOSDNotification::titleColor() const
{
    return d_func()->titleColor;
}

void QOSDNotification::setTitleColor(const QColor &color)
{
    Q_D(QOSDNotification);
    if (d->titleColor != color) {
        d->titleColor = color;
        QPalette palette = d->titleLabel->palette().color(QPalette::WindowText);
        palette.setColor(QPalette::WindowText, color);
        d->titleLabel->setPalette(palette);
    }
}

QColor QOSDNotification::bodyTextColor() const
{
    return d_func()->bodyTextColor;
}

void QOSDNotification::setBodyTextColor(const QColor &color)
{
    Q_D(QOSDNotification);
    if (d->bodyTextColor != color) {
        d->bodyTextColor = color;
        QPalette palette = d->bodyTextLabel->palette().color(QPalette::WindowText);
        palette.setColor(QPalette::WindowText, color);
        d->bodyTextLabel->setPalette(palette);
    }
}

qreal QOSDNotification::borderWidth() const
{
    return d_func()->borderWidth;
}

void QOSDNotification::setBorderWidth(qreal width)
{
    Q_D(QOSDNotification);
    if (d->borderWidth != width && width >= 0) {
        d->borderWidth = width;
        d->updateRect();
        update();
    }
}

qreal QOSDNotification::borderRadius() const
{
    return d_func()->borderRadius;
}

void QOSDNotification::setBorderRadius(qreal radius)
{
    Q_D(QOSDNotification);
    if (d->borderRadius != radius && radius >= 0) {
        d->borderRadius = radius;
        d->updateMask();
        update();
    }
}

qreal QOSDNotification::opacity() const
{
    return d_func()->opacity;
}

void QOSDNotification::setOpacity(qreal opacity)
{
    Q_D(QOSDNotification);
    if (d->opacity != opacity) {
        d->opacity = opacity;
        d->closeButton->setOpacity(opacity);
        update();
        d->closeButton->update();
    }
}

qreal QOSDNotification::hoverOpacity() const
{
    return d_func()->hoverOpacity;
}

void QOSDNotification::setHoverOpacity(qreal opacity)
{
    Q_D(QOSDNotification);
    if (d->hoverOpacity != opacity) {
        d->hoverOpacity = opacity;
        d->closeButton->setHoverOpacity(opacity);
        update();
        d->closeButton->update();
    }
}

bool QOSDNotification::isCloseButtonVisible() const
{
    return d_func()->closeButtonVisible;
}

void QOSDNotification::setCloseButtonVisible(bool closeButtonVisible)
{
    Q_D(QOSDNotification);
    if (d->closeButtonVisible != closeButtonVisible) {
        d->closeButtonVisible = closeButtonVisible;
        update();
    }
}

QLabel *QOSDNotification::titleLabel() const
{
    return d_func()->titleLabel;
}

QLabel *QOSDNotification::bodyTextLabel() const
{
    return d_func()->bodyTextLabel;
}

QOSDNotificationCloseButton *QOSDNotification::closeButton() const
{
    return d_func()->closeButton;
}

void QOSDNotification::close()
{
    hide();
    emit closed();
}

void QOSDNotification::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    Q_D(QOSDNotification);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setCompositionMode(QPainter::CompositionMode_Clear);
    p.fillRect(rect(), Qt::transparent);
    p.setCompositionMode(QPainter::CompositionMode_SourceOver);
    p.setBrush(d->hovered
                ? d->backgroundHoverBrush != Qt::NoBrush ? d->backgroundHoverBrush : QBrush(d->backgroundHoverColor)
                : d->backgroundBrush != Qt::NoBrush ? d->backgroundBrush : QBrush(d->backgroundColor));
    p.setPen(d->hovered
                ? d->borderHoverPen != Qt::NoPen
                    ? d->borderHoverPen
                    : d->borderWidth > 0
                        ? QPen(d->borderHoverColor, d->borderWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin)
                        : Qt::NoPen
                : d->borderPen != Qt::NoPen
                    ? d->borderPen
                    : d->borderWidth > 0
                        ? QPen(d->borderColor, d->borderWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin)
                        : Qt::NoPen);
    p.setOpacity(d->hovered ? d->hoverOpacity : d->opacity);
    p.drawRoundedRect(d->rect, d->borderRadius, d->borderRadius);
}

void QOSDNotification::enterEvent(QEvent *event)
{
    Q_D(QOSDNotification);
    QAbstractOSDNotification::enterEvent(event);
    update();
    if (d->closeButtonVisible && !d->closeButton->isVisible())
        d->closeButton->show();
}

void QOSDNotification::leaveEvent(QEvent *event)
{
    Q_D(QOSDNotification);
    QAbstractOSDNotification::leaveEvent(event);
    update();
    if (d->closeButton->isVisible())
        d->closeButton->hide();
}

QOSDNotificationPrivate::QOSDNotificationPrivate() :
    titleLabel(0),
    bodyTextLabel(0),
    bodyWidget(0),
    pixmapLabel(0),
    closeButton(0),
    backgroundBrush(Qt::NoBrush),
    backgroundHoverBrush(Qt::NoBrush),
    backgroundColor(QColor("#131313")),
    backgroundHoverColor(backgroundColor),
    borderPen(Qt::NoPen),
    borderHoverPen(Qt::NoPen),
    borderColor(backgroundColor.darker(150)),
    borderHoverColor(borderColor),
    titleColor(Qt::white),
    bodyTextColor(QColor("#eaeaea")),
    borderWidth(2.0),
    borderRadius(10),
    opacity(0.8),
    hoverOpacity(0.9),
    closeButtonVisible(true)
{
}

QOSDNotificationPrivate::~QOSDNotificationPrivate()
{
}

void QOSDNotificationPrivate::init()
{
    Q_Q(QOSDNotification);

    pixmapLabel = new QLabel;
    pixmapLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    pixmapLabel->hide();

    closeButton = new QOSDNotificationCloseButton(q);
    closeButton->hide();

    q->connect(closeButton, SIGNAL(clicked()), q, SLOT(close()));

    q->connect(q, SIGNAL(shown()), SLOT(_q_setupCloseButtonPosition()));
    q->connect(q, SIGNAL(resized()), SLOT(_q_resized()));

    titleLabel = new QLabel;
    titleLabel->setWordWrap(true);
    {
        QPalette palette;
        palette.setColor(QPalette::WindowText, titleColor);
        titleLabel->setPalette(palette);
        QFont font = titleLabel->font();
        font.setBold(true);
        font.setPixelSize(12);
        titleLabel->setFont(font);
    }

    bodyTextLabel = new QLabel;
    bodyTextLabel->setWordWrap(true);
    {
        QPalette palette;
        palette.setColor(QPalette::WindowText, titleColor);
        bodyTextLabel->setPalette(palette);
        QFont font = bodyTextLabel->font();
        font.setPixelSize(11);
        bodyTextLabel->setFont(font);
    }

    bodyLayout = new QVBoxLayout;
    bodyLayout->addWidget(titleLabel);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(pixmapLabel, 0, Qt::AlignTop);
    mainLayout->addLayout(bodyLayout);

    q->setLayout(mainLayout);
}

void QOSDNotificationPrivate::setTitle(const QString &title)
{
    if (titleLabel->text() != title) {
//        QFontMetrics fm(titleLabel->font());
//        const QString elidedTitle = fm.elidedText(title, Qt::ElideRight, 400);
//        titleLabel->setText(elidedTitle);
        titleLabel->setText(title);
    }
}

void QOSDNotificationPrivate::setBodyText(const QString &bodyText)
{
    if (bodyTextLabel->text() != bodyText)
        bodyTextLabel->setText(bodyText);
    maybeRemoveBodyWidget();
    maybeAddWidget(bodyTextLabel);
}

void QOSDNotificationPrivate::setBodyWidget(QWidget *bodyWidget)
{
    maybeRemoveWidget(bodyTextLabel);
    if (this->bodyWidget != bodyWidget) {
        maybeRemoveBodyWidget();
        maybeAddWidget(this->bodyWidget = bodyWidget);
    }
}

void QOSDNotificationPrivate::setPixmap(const QPixmap &pixmap, bool autoScale)
{
    this->pixmap = pixmap;
    bool nullPixmap = pixmap.isNull();
    pixmapLabel->setVisible(!nullPixmap);
    pixmapLabel->setPixmap(!nullPixmap && autoScale ? pixmap.scaled(qMin(pixmap.width(), 48), qMin(pixmap.height(), 48), Qt::KeepAspectRatio, Qt::SmoothTransformation) : pixmap);
}

void QOSDNotificationPrivate::maybeAddWidget(QWidget *widget)
{
    if (widget) {
        if (bodyLayout->indexOf(widget) == -1)
            bodyLayout->addWidget(widget);
        if (!widget->isVisible())
            widget->show();
    }
}

void QOSDNotificationPrivate::maybeRemoveWidget(QWidget *widget)
{
    if (widget) {
        if (bodyLayout->indexOf(widget) != -1)
            bodyLayout->removeWidget(widget);
        if (widget->isVisible())
            widget->hide();
    }
}

void QOSDNotificationPrivate::maybeRemoveBodyWidget()
{
    if (bodyWidget) {
        maybeRemoveWidget(bodyWidget);
        if (bodyWidget->parent())
            bodyWidget->setParent(0);
    }
}

void QOSDNotificationPrivate::updateRect()
{
    Q_Q(QOSDNotification);

    int adjust = qFloor(borderWidth / 2);
    rect = q->rect().adjusted(adjust, adjust, -adjust, -adjust);

    updateMask();
}

void QOSDNotificationPrivate::updateMask()
{
#ifdef Q_OS_LINUX

#if QT_VERSION < 0x050000
    if (QX11Info::isCompositingManagerRunning())
        return;
#endif

    Q_Q(QOSDNotification);

    QBitmap mask(q->width(), q->height());
    mask.clear();

    QPainterPath path;
    path.addRoundedRect(rect, borderRadius, borderRadius);

    QPainter p(&mask);
    p.setBrush(QBrush(Qt::color1));
    p.setPen(borderWidth > 0 ? QPen(Qt::color1, borderWidth, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin) : Qt::NoPen);
    p.drawPath(path);

    q->setMask(mask);

#endif // Q_OS_LINUX
}

void QOSDNotificationPrivate::_q_resized()
{
    updateRect();
    _q_setupCloseButtonPosition();
}

void QOSDNotificationPrivate::_q_setupCloseButtonPosition()
{
    Q_Q(QOSDNotification);
    int x = q->width() - closeButton->width() - borderRadius;
    int y = borderRadius;
    closeButton->move(x, y);
    closeButton->raise();
}

#include "moc_qosdnotification.cpp"
