#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QtCore>
#include <QtGui>
#include <booklistwidget.h>
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
        void readFromFile();
private:
    Ui::MainWindow *ui;
    void createMenus();
    BookListWidget *bookListWidget;
    QMenu *fileMenu;
    QMenu *toolMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *addAct;
    QAction *editAct;
    QAction *removeAct;
    void setMenuBarGrey();
    void setupTabs();




public slots:
    void showAddEntryDialog();
    void addEntry(QString author,QString title, QString year);
    void editEntry();
    void removeEntry();

signals:
    void selectionChanged(const QItemSelection &selected);
signals:
    void sendDetails(QString author,QString title, QString year);
private:
    TableModel *table;
    QTableView *tableView;
    QSortFilterProxyModel *proxyModel;
};

#endif // MAINWINDOW_H
