#include <QAction>
#include <QCheckBox>
#include <QToolButton>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QImageReader>

#include "iconwidget.h"
#include "icondroparea.h"

IconWidget::IconWidget(QWidget *parent) :
    QWidget(parent)
{
    m_clearAction = new QAction(QIcon::fromTheme("edit-clear"), tr("&Clear"), this);
    m_clearAction->setStatusTip(tr("Clear icon"));
    connect(m_clearAction, SIGNAL(triggered()), this, SLOT(clear()));

    m_browseAction = new QAction(QIcon::fromTheme("system-search"), tr("&Browse"), this);
    m_browseAction->setStatusTip(tr("Browse to icon"));
    connect(m_browseAction, SIGNAL(triggered()), this, SLOT(browse()));

    m_iconDropArea = new IconDropArea;
    connect(m_iconDropArea, SIGNAL(iconDropped(QString)), this, SLOT(iconDropped(QString)));

    m_autoScaleCheckBox = new QCheckBox(tr("Auto scale"));
    m_autoScaleCheckBox->setChecked(true);
    connect(m_autoScaleCheckBox, SIGNAL(toggled(bool)), this, SIGNAL(pixmapAutoScaleChanged(bool)));

    m_clearButton = new QToolButton;
    m_clearButton->setDefaultAction(m_clearAction);
    m_clearButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    m_browseButton = new QToolButton;
    m_browseButton->setDefaultAction(m_browseAction);
    m_browseButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_autoScaleCheckBox);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(m_clearButton);
    buttonsLayout->addWidget(m_browseButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(m_iconDropArea);
    layout->addLayout(buttonsLayout);

    setLayout(layout);
}

QPixmap IconWidget::pixmap() const
{
    return m_pixmap;
}

void IconWidget::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;
    bool nullPixmap = pixmap.isNull();
    m_clearAction->setEnabled(!nullPixmap);
//    m_iconDropArea->setPixmap(m_autoScaleCheckBox->isChecked() && !nullPixmap ? pixmap.scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation) : pixmap);
    m_iconDropArea->setPixmap(pixmap);
    emit pixmapChanged(pixmap);
}

void IconWidget::setPixmap(const QString &path)
{
    setPixmap(QPixmap(path));
}

bool IconWidget::pixmapAutoScale() const
{
    return m_autoScaleCheckBox->isChecked();
}

void IconWidget::setPixmapAutoScale(bool autoScale)
{
    m_autoScaleCheckBox->setChecked(autoScale);
}

void IconWidget::iconDropped(const QString &filePath)
{
    setPixmap(filePath);
}

void IconWidget::clear()
{
    setPixmap(QPixmap());
}

void IconWidget::browse()
{
    QList<QByteArray> supportedImageFormats = QImageReader::supportedImageFormats();
    QStringList formats;
    foreach (QByteArray format, supportedImageFormats)
        formats.append(QLatin1String("*.") + format);
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select icon"), m_lastPath.isEmpty() ? QDir::homePath() : m_lastPath, tr("Images (%1)").arg(formats.join(QChar(' '))));
    if (filePath.isEmpty())
        return;
    m_lastPath = filePath;
    setPixmap(filePath);
}
