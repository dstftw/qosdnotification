#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QToolButton;
QT_END_NAMESPACE

class ColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorWidget(QWidget *parent = 0);

    QColor color() const;
    void setColor(const QColor &color);

signals:
    void colorChanged(const QColor &color);

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void selectButtonClicked();

private:
    QColor m_color;
    QLabel *m_colorLabel;
    QToolButton *m_selectButton;
};

#endif // COLORWIDGET_H
