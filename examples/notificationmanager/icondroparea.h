#ifndef ICONDROPAREA_H
#define ICONDROPAREA_H

#include <QLabel>

QT_BEGIN_NAMESPACE
class QMimeData;
QT_BEGIN_NAMESPACE

class IconDropArea : public QLabel
{
    Q_OBJECT
public:
    explicit IconDropArea(QWidget *parent = 0);

public slots:
    void clear();
    void setPixmap(const QPixmap &pixmap);
    
signals:
    void iconDropped(const QString &filePath);

protected:
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);

private:
    QString extractIconFilePath(const QMimeData *mimeData);
    QList<QByteArray> supportedImageFormats;
};

#endif // ICONDROPAREA_H
