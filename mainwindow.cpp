#include "mainwindow.h"
#include "ui_mainwindow.h"
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


    table = new TableModel(this);
    connect(this,&MainWindow::sendDetails,this,&MainWindow::addEntry);

    proxyModel = new QSortFilterProxyModel(this);
   // readFromFile();
    readFromFile();
    proxyModel->setSourceModel(table);
    //proxyModel->setFilterKeyColumn(2);

    tableView = ui->tableBookView;
    tableView->setModel(proxyModel);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::selectionChanged);

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

       if (!indexes.isEmpty()) {
           removeAct->setEnabled(true);
           editAct->setEnabled(true);
       } else {
           removeAct->setEnabled(false);
           editAct->setEnabled(false);
       }
}

void MainWindow::openFile()
{
    this->readFromFile();
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

       connect(this, &MainWindow::selectionChanged,
           this, &MainWindow::updateActions);
}



void MainWindow::setMenuBarGrey()
{
    QPalette palette;
    palette.setColor(ui->menuLibrary->backgroundRole(),Qt::gray);
    ui->menuBar->setPalette(palette);
}

void MainWindow::setupTabs()
{


    proxyModel = new QSortFilterProxyModel(this);
   // readFromFile();
    proxyModel->setSourceModel(table);
    //proxyModel->setFilterKeyColumn(2);

    tableView = ui->tableBookView;
    tableView->setModel(proxyModel);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSortingEnabled(true);

    connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::selectionChanged);





}

void MainWindow::readFromFile()
{
    QString filename = QFileDialog::getOpenFileName (nullptr, "Open dat file",
                                                         QDir::currentPath(), "csv (*.csv)");
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << file.errorString();
        return;
    }

    QList<Book> books;
    QStringList bookData;

    while (!file.atEnd()) {
      QByteArray line = file.readLine();

      for(QString it : line.split(';')){
          bookData.push_back(it);
          if(bookData.size() == 3){
              Book bookdata;
              bookdata.author = bookData[0];
              bookdata.title = bookData[1];
              bookdata.year = bookData[2];
              books.push_back(bookdata);
              bookData.clear();
          }
      }
    }
    if (books.isEmpty()) {
            QMessageBox::information(this, tr("No contacts in file"),
                                     tr("The file you are attempting to open contains no contacts."));
        } else {
            for (const auto &book: books){
                QString test = book.author;
                addEntry(book.author, book.title,book.year);
            }
        }
}

void MainWindow::showAddEntryDialog()
{
    AddDialog aDialog;

        if (aDialog.exec()) {
            QString author = aDialog.authorText->toPlainText();
            QString title = aDialog.titleText->toPlainText();
            QString year = aDialog.yearText->toPlainText();

            addEntry(author, title,year);
        }
}

void MainWindow::addEntry(QString author, QString title, QString year)
{
  //  if(!table->getBooks().contains({author,title,year})){
        table->insertRows(0,1,QModelIndex());



        QModelIndex index = table->index(0,0,QModelIndex());
        table->setData(index,author, Qt::EditRole);
        index = table->index(0,1,QModelIndex());
        table->setData(index,title,Qt::EditRole);
        index = table->index(0,2, QModelIndex());
        table->setData(index,year, Qt::EditRole);

//    }else {
//    QMessageBox::information(this, tr("Duplicate title and author"),
//                             tr("The author  \"%1\" and title \"%2\" already exists.")
//                             .arg(author,title));
//}
}

void MainWindow::editEntry()
{
   QItemSelectionModel *selectionModel = tableView->selectionModel();

   QModelIndexList indexes = selectionModel->selectedRows();
   QString author, title, year;
   int row = -1;
   foreach (QModelIndex index, indexes) {
       row = proxyModel->mapToSource(index).row();

       QModelIndex authorIndex = table->index(row, 0, QModelIndex());
       QVariant varAuthor = table->data(authorIndex, Qt::DisplayRole);
       author = varAuthor.toString();

       QModelIndex titleIndex = table->index(row, 1, QModelIndex());
       QVariant varTitle = table->data(titleIndex, Qt::DisplayRole);
       title = varTitle.toString();

       QModelIndex yearIndex = table->index(row, 2, QModelIndex());
       QVariant varYear = table->data(yearIndex, Qt::DisplayRole);
       year = varYear.toString();

   }

       AddDialog aDialog;
       aDialog.setWindowTitle(tr("Edit a book"));

       aDialog.authorText->setText(author);
       aDialog.titleText->setText(title);
       aDialog.yearText->setText(year);

       if (aDialog.exec()) {
           QString newAuthor = aDialog.authorText->toPlainText();
           QString newTitle = aDialog.titleText->toPlainText();
           QString newYear = aDialog.yearText->toPlainText();

           if (newAuthor != author) {
               QModelIndex index = table->index(row, 0, QModelIndex());
               table->setData(index, newAuthor, Qt::EditRole);
           }
           if (newTitle != title) {
               QModelIndex index = table->index(row, 1, QModelIndex());
               table->setData(index, newTitle, Qt::EditRole);
           }
           if (newYear != year) {
               QModelIndex index = table->index(row, 2, QModelIndex());
               table->setData(index, newYear, Qt::EditRole);
           }
       }
}

void MainWindow::removeEntry()
{
    QItemSelectionModel *selectionModel = tableView->selectionModel();
    QModelIndexList indexes = selectionModel->selectedRows();

    foreach (QModelIndex index, indexes) {
       int row = proxyModel->mapToSource(index).row();
       table->removeRows(row,1,QModelIndex());
    }
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
