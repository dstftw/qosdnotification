#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "customwidget.h"

CustomWidget::CustomWidget(QWidget *parent) :
    QWidget(parent)
{
    QLabel *label = new QLabel(tr("Text:"));
    QPalette palette = label->palette().color(QPalette::WindowText);
    palette.setColor(QPalette::WindowText, Qt::white);
    label->setPalette(palette);

    QLineEdit *lineEdit = new QLineEdit;

    QPushButton *okButton = new QPushButton;
    okButton->setText(tr("OK"));
    connect(okButton, SIGNAL(clicked()), this, SIGNAL(done()));

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(label);
    hboxLayout->addWidget(lineEdit);

    QHBoxLayout *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(okButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(hboxLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}
