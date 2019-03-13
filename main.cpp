#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QFile file("/home/robert/Desktop/sem6/EGUI/lab/lab1/project/dane.xls.csv");
    if(!file.open(QIODevice::ReadOnly)){
        qDebug() << file.errorString();
        return 1;
    }

    QStringList wordlist;
    while (!file.atEnd()) {
      QByteArray line = file.readLine();
      for(auto it = line.begin(); it != line.end(); it++)
        wordlist.append(it);
    }

    qDebug() << wordlist[2];
    return a.exec();
}
