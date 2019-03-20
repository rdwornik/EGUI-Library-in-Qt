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
    QTableView *tableview;

private slots:
        void updateActions(const QItemSelection &selection);
        void openFile();

public slots:
        void addEntry();
        void filterEntry();
signals:
        void sendDetails(QString author, QString title, QString year);
        void sendFilter(QString author, QString title, QString year);
        void passRefernceToTableView(QTableView*& tableView);

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
    void emitQtableSignal();
};

#endif // MAINWINDOW_H
