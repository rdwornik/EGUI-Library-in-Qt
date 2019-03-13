#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QStandardItemModel>
#include <QTextStream>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(ui->menuLibrary->backgroundRole(),Qt::gray);
    ui->menuBar->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}


