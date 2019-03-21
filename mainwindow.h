#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QtCore>
#include <QtGui>
#include <QTableView>
#include "mysortfilterproxymodel.h"
#include "tablemodel.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

private slots:
        void updateActions(const QItemSelection &selection);
        void openFile();

public slots:
        void addEntrySlot();
        void editEntry();
        void removeEntry();
        void filterEntry();
        void filterClearEntry();

signals:
        void selectionChanged(const QItemSelection &selected);

private:
    Ui::MainWindow *ui;

    void setMenuBarGrey();
    void setUpModels();
    void addEntry(QString author, QString title, QString year);

    TableModel *table;
    QTableView *tableView;
    MySortFilterProxyModel *proxyModel;

};

#endif // MAINWINDOW_H
