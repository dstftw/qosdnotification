#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QPushButton;
QT_END_NAMESPACE

class CustomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWidget(QWidget *parent = 0);

signals:
    void done();
};

#endif // CUSTOMWIDGET_H
