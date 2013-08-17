#ifndef PIXMAPWIDGET_H
#define PIXMAPWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QToolButton;
QT_END_NAMESPACE

class IconDropArea;

class IconWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IconWidget(QWidget *parent = 0);

    QPixmap pixmap() const;
    void setPixmap(const QPixmap &pixmap);
    void setPixmap(const QString &path);

    bool pixmapAutoScale() const;
    void setPixmapAutoScale(bool autoScale);

signals:
    void pixmapChanged(const QPixmap &m_pixmap);
    void pixmapAutoScaleChanged(bool value);
    
private slots:
    void iconDropped(const QString &filePath);
    void clear();
    void browse();

private:
    QString m_lastPath;
    QPixmap m_pixmap;

    QAction *m_clearAction;
    QAction *m_browseAction;

    IconDropArea *m_iconDropArea;
    QCheckBox *m_autoScaleCheckBox;
    QToolButton *m_clearButton;
    QToolButton *m_browseButton;
};

#endif // PIXMAPWIDGET_H
