#include <QImageReader>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>

#include "icondroparea.h"

IconDropArea::IconDropArea(QWidget *parent) :
    QLabel(parent)
{
    setMinimumSize(200, 200);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    setAlignment(Qt::AlignCenter);
    setAcceptDrops(true);
    setAutoFillBackground(true);
    clear();
    supportedImageFormats = QImageReader::supportedImageFormats();
}

void IconDropArea::dragEnterEvent(QDragEnterEvent *event)
{
    if (extractIconFilePath(event->mimeData()).isEmpty()) {
        event->ignore();
    } else {
        setBackgroundRole(QPalette::Highlight);
        event->acceptProposedAction();
    }
}

void IconDropArea::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void IconDropArea::dropEvent(QDropEvent *event)
{
    QString filePath = extractIconFilePath(event->mimeData());
    if (!filePath.isEmpty())
        emit iconDropped(filePath);
    setBackgroundRole(QPalette::Dark);
    event->acceptProposedAction();
}
void IconDropArea::dragLeaveEvent(QDragLeaveEvent *event)
{
    setBackgroundRole(QPalette::Dark);
    event->accept();
}

QString IconDropArea::extractIconFilePath(const QMimeData *mimeData)
{
    if (mimeData->hasUrls()) {
        QList<QUrl> urls = mimeData->urls();
        foreach (const QUrl &url, urls) {
            if (!url.isLocalFile())
                continue;
            const QString filePath = url.toLocalFile();
            if (filePath.isEmpty() || !QFile::exists(filePath))
                continue;
            foreach (const QByteArray &format, supportedImageFormats) {
                if (filePath.endsWith(QLatin1String(".") + format))
                    return filePath;
            }
        }
    }
    return QString();
}

void IconDropArea::clear()
{
    setText(tr("<drop here>"));
    setBackgroundRole(QPalette::Dark);
}

void IconDropArea::setPixmap(const QPixmap &pixmap)
{
    if (pixmap.isNull())
        clear();
    else
        QLabel::setPixmap(pixmap);
}
