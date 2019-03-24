#include "mainwindow.h"
#include "ui_booklistwidget.h"
#include "adddialog.h"
#include "yearmodel.h"
#include "mysortfilterproxymodel.h"

#include "tablemodel.h"
#include <QPalette>
#include <QStandardItemModel>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QComboBox>
#include <QMessageBox>
#include <QModelIndex>
#include <QFileDialog>
#include <sstream>
#include <vector>
#include <algorithm>
#include <QtAlgorithms>
#include <QVector>
#include <iterator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
       ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setMenuBarGrey();
    setUpModels();
    openFile();

    ui->tableBookView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->editBookButton, &QAbstractButton::clicked,this, &MainWindow::editEntry);
    connect(ui->deleteBookButton, &QAbstractButton::clicked,this, &MainWindow::removeEntry);
    connect(ui->addBookButton, &QAbstractButton::clicked,this, &MainWindow::addEntrySlot);
    connect(ui->filterBooksButton, &QAbstractButton::clicked,this, &MainWindow::filterEntry);
    connect(ui->clearFilterDialogButton, &QAbstractButton::clicked,this, &MainWindow::filterClearEntry);


    connect(tableView->selectionModel(),
            &QItemSelectionModel::selectionChanged,
            this,
            &MainWindow::selectionChanged);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateActions(const QItemSelection &selection)
{
    QModelIndexList indexes = selection.indexes();
}

void MainWindow::openFile()
{
    QString filename = QFileDialog::getOpenFileName (nullptr, "Open dat file",
                                                         QDir::currentPath(), "dat (*.csv)");
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
            for (const auto &book: qAsConst(books))
                addEntry(book.author, book.title,book.year);
        }
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

            QString newAuthor = aDialog.authorText->text();
            QString newTitle = aDialog.titleText->text();
            QString newYear = aDialog.yearText->text();

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

    std::vector<int> reversedIndexes;

    foreach (QModelIndex index, indexes) {
       int row = proxyModel->mapToSource(index).row();
       reversedIndexes.push_back(row);
    }

    std::sort(reversedIndexes.begin(),reversedIndexes.end(),std::greater<int>());

    for(const auto& v : reversedIndexes)
        table->removeRows(v,1,QModelIndex());
}

void MainWindow::addEntrySlot()
{
    AddDialog aDialog;

    if(aDialog.exec()){
        QString author = aDialog.authorText->text();
        QString title = aDialog.titleText->text();
        QString year = aDialog.yearText->text();

        addEntry(author,title,year);
    }
}

void MainWindow::filterEntry()
{
    QString author = ui->authorLineEdit->text();
    QString title = ui->titleLineEdit->text();
    QString year = ui->yearComboBox->currentText();


    proxyModel->setFilter(author,title,year);


}

void MainWindow::filterClearEntry()
{
    ui->authorLineEdit->setText(QString());
    ui->titleLineEdit->setText(QString());
    int index = ui->yearComboBox->findText("");
    ui->yearComboBox->setCurrentIndex(index);
    proxyModel->setFilter(QString(),QString(),QString());

}

void MainWindow::setMenuBarGrey()
{
    QPalette palette;
    palette.setColor(ui->menuLibrary->backgroundRole(),Qt::gray);
    ui->menuBar->setPalette(palette);
}

void MainWindow::setUpModels()
{

    table = new TableModel(this);

    tableView = ui->tableBookView;

    proxyModel = new MySortFilterProxyModel(this);
    proxyModel->setSourceModel(table);
    proxyModel->setFilterKeyColumn(0);
    proxyModel->setFilterKeyColumn(1);
    proxyModel->setFilterKeyColumn(2);

    yearModel_ = new yearModel(*table,this);
    ui->yearComboBox->setModel(yearModel_);

    tableView->setModel(proxyModel);

    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableView->setSelectionMode(QAbstractItemView::MultiSelection);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(0, Qt::AscendingOrder);

}

void MainWindow::addEntry(QString author, QString title, QString year)
{
      if(!table->getBooks().contains({author,title,year})){
        table->insertRows(0,1,QModelIndex());

        QModelIndex index = table->index(0,0,QModelIndex());
        table->setData(index,author, Qt::EditRole);
        index = table->index(0,1,QModelIndex());
        table->setData(index,title,Qt::EditRole);
        index = table->index(0,2, QModelIndex());
        table->setData(index,year, Qt::EditRole);

      }else {
      QMessageBox::information(this, tr("Duplicate title and author"),
                               tr("The author  \"%1\" and title \"%2\" already exists.")
                               .arg(author,title));
      }
}

bool MainWindow::isNumber(const QString& year)
{
    return year.toInt() && year.size() && std::find_if(year.begin(),year.end(),[](QChar c){
        return c.isDigit();
    });
}






