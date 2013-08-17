#include <QLabel>
#include <QToolButton>
#include <QColorDialog>
#include <QHBoxLayout>
#include <QMouseEvent>

#include "colorwidget.h"

ColorWidget::ColorWidget(QWidget *parent) :
    QWidget(parent)
{
    m_colorLabel = new QLabel;
    m_colorLabel->setAutoFillBackground(true);

    m_selectButton = new QToolButton;
    m_selectButton->setText(tr("Select"));

    connect(m_selectButton, SIGNAL(clicked()), this, SLOT(selectButtonClicked()));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_colorLabel);
    layout->addWidget(m_selectButton);

    setLayout(layout);
}

QColor ColorWidget::color() const
{
    return m_color;
}

void ColorWidget::setColor(const QColor &color)
{
    if (m_color != color) {
        m_color = color;
        m_colorLabel->setText(color.name());
        m_colorLabel->setPalette(QPalette(color));
        emit colorChanged(color);
    }
}

void ColorWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        selectButtonClicked();
}

void ColorWidget::selectButtonClicked()
{
    const QColor color = QColorDialog::getColor(m_color, this);
    if (color.isValid())
        setColor(color);
}
