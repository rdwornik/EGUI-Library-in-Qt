#include "adddialog.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QFormLayout>
AddDialog::AddDialog(QWidget *parent)
    : QDialog (parent)
{

        okButton = new QPushButton("OK");
        cancelButton = new QPushButton("Cancel");

        authorText = new QLineEdit;
        titleText = new QLineEdit;
        yearText = new QLineEdit;



        formGroupBox = new QGroupBox(tr("Data"));
        QFormLayout *layout = new QFormLayout;
        layout->addRow(new QLabel(tr("Author")), authorText);
        layout->addRow(new QLabel(tr("Title")), titleText);
        layout->addRow(new QLabel(tr("Year")), yearText);
        formGroupBox->setLayout(layout);


        QVBoxLayout *mainLayout = new QVBoxLayout;


        buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);


        connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));


        mainLayout->addWidget(formGroupBox);
        mainLayout->addWidget(buttonBox);

        setLayout(mainLayout);
        setWindowTitle(tr("Add a book"));







//         buttonLayout = new QHBoxLayout;
//                buttonLayout->addWidget(okButton);
//                buttonLayout->addWidget(cancelButton);

       // connect(buttonBox->button(QDialogButtonBox::Ok), &QDialogButtonBox::clicked, this, &QDialog::accept);
        //connect(cancelButton, &QAbstractButton::clicked, this, &QDialog::reject);

//        auto *gLayout = new QGridLayout;

//        gLayout->setColumnStretch(1,3);



//        gLayout->addWidget(authorLabel,0,0);
//        gLayout->addWidget(authorText,0,1);

//        gLayout->addWidget(titleLabel, 1, 0, Qt::AlignLeft|Qt::AlignTop);
//        gLayout->addWidget(titleText, 1, 1, Qt::AlignLeft);

//        gLayout->addWidget(yearLabel, 2, 0, Qt::AlignLeft|Qt::AlignBottom);
//        gLayout->addWidget(yearText, 2, 1, Qt::AlignLeft);


//        QHBoxLayout *buttonLayout = new QHBoxLayout;
//        buttonLayout->addWidget(okButton);
//        buttonLayout->addWidget(cancelButton);

//        gLayout->addLayout(buttonLayout, 2, 1, Qt::AlignRight);

//        QVBoxLayout *mainLayout = new QVBoxLayout;
//        mainLayout->addLayout(gLayout);
//        setLayout(mainLayout);



//        setWindowTitle(tr("Add a book"));
}
