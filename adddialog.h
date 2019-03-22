#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QTextEdit>
#include<QGroupBox>
#include<QDialogButtonBox>
#include<QHBoxLayout>
class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = 0);
    QLineEdit *authorText;
    QLineEdit *titleText;
    QLineEdit *yearText;

private:
    QLabel *authorLabel;
    QLabel *titleLabel;
    QLabel *yearLabel;
    QGroupBox *formGroupBox;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QHBoxLayout *buttonLayout;
    QDialogButtonBox *buttonBox;

};
#endif // ADDDIALOG_H
