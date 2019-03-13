#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QDebug>
#include <QFileDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

   // QFile file("/home/robert/Desktop/sem6/EGUI/lab/lab1/project/dane.xls.csv");

    QString filename = QFileDialog::getOpenFileName (nullptr, "Open CSV file",
                                                         QDir::currentPath(), "CSV (*.csv)");

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << file.errorString();
        return 1;
    }

    QStringList wordlist;
    while (!file.atEnd()) {
      QByteArray line = file.readLine();

      for(auto it : line.split(','))
        wordlist.append(it);
    }

    //for(auto v : wordlist)
    qDebug() << wordlist[1].toLatin1().data();
    return a.exec();
}
