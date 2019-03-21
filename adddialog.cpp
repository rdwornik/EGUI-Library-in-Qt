#include "adddialog.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QHBoxLayout>
AddDialog::AddDialog(QWidget *parent)
    : QDialog (parent)
{
        authorLabel = new QLabel("Author");
        titleLabel = new QLabel("Title");
        yearLabel = new QLabel("Year");

        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");

        authorText = new QLineEdit;
        titleText = new QLineEdit;
        yearText = new QLineEdit;

        auto *gLayout = new QGridLayout;

        gLayout->setColumnStretch(1,3);



        gLayout->addWidget(authorLabel,0,0);
        gLayout->addWidget(authorText,0,1);

        gLayout->addWidget(titleLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
        gLayout->addWidget(titleText, 1, 1, Qt::AlignLeft);

        gLayout->addWidget(yearLabel, 2, 0, Qt::AlignLeft|Qt::AlignBottom);
        gLayout->addWidget(yearText, 2, 1, Qt::AlignLeft);


        QHBoxLayout *buttonLayout = new QHBoxLayout;
        buttonLayout->addWidget(okButton);
        buttonLayout->addWidget(cancelButton);

        gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->addLayout(gLayout);
        setLayout(mainLayout);

        connect(okButton, &QAbstractButton::clicked, this, &QDialog::accept);
        connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

        setWindowTitle(tr("Add a book"));
}
