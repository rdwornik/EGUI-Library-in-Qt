#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include<QDialog>
#include<QLabel>
#include<QLineEdit>
#include<QTextEdit>
#include<QGroupBox>
#include<QDialogButtonBox>
#include<QHBoxLayout>
#include <QErrorMessage>

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    AddDialog(QWidget *parent = 0);
    QLineEdit *authorText;
    QLineEdit *titleText;
    QLineEdit *yearText;

public slots:
    void done(int r) override;

private:
    QErrorMessage *errorMessage;
    QLabel *authorLabel;
    QLabel *titleLabel;
    QLabel *yearLabel;
    QGroupBox *formGroupBox;
    QPushButton *okButton;
    QPushButton *cancelButton;
    QHBoxLayout *buttonLayout;
    QDialogButtonBox *buttonBox;
    bool isNumber();
    bool isEmpty();
    bool checkSemi();

};
#endif // ADDDIALOG_H
