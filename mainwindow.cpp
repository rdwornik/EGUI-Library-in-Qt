#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddialog.h"
#include <QPalette>
#include <QStandardItemModel>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QComboBox>
#include <adddialog.h>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
       ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMenuBarGrey();
    tableview = ui->tableBookView;

    bookListWidget = new BookListWidget;
    connect(this,&MainWindow::passRefernceToTableView,bookListWidget,&BookListWidget::setTableView);
    connect(ui->editBookButton, &QAbstractButton::clicked,bookListWidget, &BookListWidget::editEntry);
    connect(ui->deleteBookButton, &QAbstractButton::clicked,bookListWidget, &BookListWidget::removeEntry);

    connect(ui->addBookButton, &QAbstractButton::clicked,this, &MainWindow::addEntry);
    connect(this, &MainWindow::sendDetails,bookListWidget, &BookListWidget::addEntry);

    //nie updatetuje
    connect(ui->filterButton, &QAbstractButton::clicked,this, &MainWindow::filterEntry);
    connect(this, &MainWindow::sendFilter,bookListWidget, &BookListWidget::filterEntry);




//    connect(bookListWidget, &BookListWidget::selectionChanged,
//          this, &MainWindow::updateActions);

    this->emitQtableSignal();
    bookListWidget->setUp();
   // setCentralWidget(bookListWidget);
    this->openFile();
//    connect(bookListWidget, &BookListWidget::selectionChanged,
//        this, &MainWindow::updateActions);



   // createMenus();
    setWindowTitle(tr("Book List"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();

//       if (!indexes.isEmpty()) {
//           removeAct->setEnabled(true);
//           editAct->setEnabled(true);
//       } else {
//           removeAct->setEnabled(false);
//           editAct->setEnabled(false);
//       }
}

void MainWindow::openFile()
{
    bookListWidget->readFromFile();
}

void MainWindow::addEntry()
{
    AddDialog aDialog;

    if(aDialog.exec()){
        QString author = aDialog.authorText->toPlainText();
        QString title = aDialog.titleText->toPlainText();
        QString year = aDialog.yearText->toPlainText();

        emit sendDetails(author,title,year);
    }
}

void MainWindow::filterEntry()
{
    QString author = ui->authorLineEdit->text();
    QString title = ui->titleLineEdit->text();
    QString year = ui->comboBox->currentText();
    emit sendFilter(author,title,year);
}





void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

       openAct = new QAction(tr("&Open..."), this);
       fileMenu->addAction(openAct);
       connect(openAct, &QAction::triggered, this, &MainWindow::openFile);


//       editAct = new QAction(tr("&Edit Entry..."), this);
//       editAct->setEnabled(false);
//       //toolMenu->addAction(editAct);
//       connect(editAct, &QAction::triggered, this, &MainWindow::editEntry);

//       //toolMenu->addSeparator();

//       removeAct = new QAction(tr("&Remove Entry"), this);
//       removeAct->setEnabled(false);
//       //toolMenu->addAction(removeAct);
//       connect(removeAct, &QAction::triggered, this, &MainWindow::removeEntry);


}



void MainWindow::setMenuBarGrey()
{
    QPalette palette;
    palette.setColor(ui->menuLibrary->backgroundRole(),Qt::gray);
    ui->menuBar->setPalette(palette);
}

void MainWindow::emitQtableSignal()
{
    emit passRefernceToTableView(tableview);
}





//void MainWindow::on_addBookButton_clicked()
//{
//    int row = model->rowCount();
//    model->insertRows(row,1);

//    QModelIndex index = model->index(row);

//    ui->bookListView->setCurrentIndex(index);
//    ui->bookListView->edit(index);
//}

//void MainWindow::on_editBookButton_clicked()
//{

//}

//void MainWindow::on_deleteBookButton_clicked()
//{
//    model->removeRows(ui->bookListView->currentIndex().row(),1);

//}
